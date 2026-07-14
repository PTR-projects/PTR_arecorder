/*****************************************************************************/
/*                                 INCLUDES                                  */
/*****************************************************************************/
#include <main.h>
#include <FSIO.h>
#include <SD-SPI.h>
#include <DEE_Emulation_16-bit.h>
#include <APlib.h>
#include <Sensors.h>
#include <Communication.h>

#include <usb/system_config.h>
#include <usb/app_led_usb_status.h>

#include <../usb_framework/inc/usb.h>
#include <../usb_framework/inc/usb_device.h>
#include <../usb_framework/inc/usb_device_cdc.h>

#include <math.h>

#ifdef PRESSURE_CAN_BE_NEGATIVE
#warning **********========== YOU ARE BUILDING WITH ASSUMPTION THAT PRESSURE CAN BE NEGATIVE =========***********
#endif
/*****************************************************************************/
/*                             GLOBAL VARIABLES                              */
/*****************************************************************************/

/************************* Configuration variables ***************************/
volatile ap_ConfigurationData_t *conf_data_ptr;

/**************************** General variables ******************************/
/** \brief 1/100 of second. */
unsigned int ap_Timer = 0;
/** \brief Seconds. */
unsigned int ap_Seconds = 0;
/** \brief I2C timeout. */
int ap_TimeoutI2C = 0;
/** \brief Buffers for writing data to SD card. */
static char ap_Buffer[NUMBER_OF_BUFFERS][SIZE_OF_SD_BUFFER];
/** \brief Error buffer. */
char ap_BufferError[BUFFER_ERROR_SIZE];
/** \brief UART buffer. */
char ap_SendBuffer[SEND_BUFFER_SIZE];
/** \brief Flag if data should be sent out during configuration of Arecorder. */
unsigned int ap_SendDataDuringConfigure = 0;
/** \brief Flag if data are ready to be send. */
int ap_SendDataReady = 0;
/** \brief Buffer to write data. */
static int ap_BufferCurrent = 0;
/** \brief Buffer to read data. */
static int ap_BufferOutput = 0;
/** \brief Flag if testing fuses should be turned off. */
static unsigned int ap_TestFusesOff = 0;
/** \brief Flag if flight parameters should be calculated from raw data. */
static int ap_DataValid = 1;
/** \brief Summaty data collected during flight. */
ap_summaryData_t ap_Summary = {
    .PressureGround = 0.0f,
    .AltitudeMax    = 0.0f,
    .VAxisMax       = 0.0f
};

/************************* Accelerometer variables ***************************/
/** \brief Acceleration data read from accelerometers. */
static apAcceleration_t ap_Acc;
/** \brief Temporary variable for high-g accelerometer. */
int ap_Hacc_temp;

/***************************** Other variables *******************************/
/** \brief Measured battery voltage. */
unsigned int ap_VbattSense;
/** \brief Voltage at fuse 1 sensor. */
unsigned int ap_FuseSense1;
/** \brief Voltage at fuse 2 sensor. */
unsigned int ap_FuseSense2;
/** \brief Voltage at fuse 3 sensor. */
unsigned int ap_FuseSense3;
/** \brief Voltage at temperature 1 sensor. */
unsigned int ap_TempSense;
/** \brief Current Arecorder state. */
ap_ArecorderState_t ap_ArecorderState = AWAITING_FOR_ARECORDER_READY;
/** \brief Flag if data should be written to SD card. */
static unsigned int ap_WriteToSD = 0;
/** \brief Flag if writing data to SD card should start. */
static unsigned int ap_WriteData = 0;
/** \brief Handler to file to write flight data. */
FSFILE *ap_FpMeas;
/** \brief Handler to file to write summary data. */
//FSFILE *ap_FpFlightSummary;

int ap_WriteInitData = 0;

/*****************************************************************************/
/*                            FUSE CONFIGURATION                             */
/*****************************************************************************/
//#pragma config JTAGEN = OFF, FWDTEN = OFF, GCP = ON
//#pragma config FNOSC = PRIPLL, PLL96MHZ = ON, PLLDIV = DIV4, OSCIOFNC = ON, POSCMOD = HS
//#pragma config SOSCSEL = EC, WPDIS = WPEN, WPCFG = WPCFGDIS, WPFP = WPFP0, WPEND = WPSTARTMEM

#pragma config JTAGEN = OFF, FWDTEN = OFF
#pragma config FNOSC = PRIPLL, PLL96MHZ = ON, PLLDIV = DIV4, OSCIOFNC = ON, POSCMOD = HS
#pragma config SOSCSEL = EC
#pragma config ICS = PGx3

/*****************************************************************************/
/*                                FUNCTIONS                                  */
/*****************************************************************************/
int main( void )
{
    /* \brief Search record holder. */
    SearchRec rec;
    /* \brief Attributes for searching files. */
    unsigned char attributes;
    /* \brief Temporary return value from function. */
    float rv;
    /* \brief Configuration selection flag. */
    int confSelect;
    /** \brief Return value. */
    int rvSync;
    /** \brief Reinitialize SD card when detected loss of connection to SD
     * card. */
    int reinitializeSDCard = 0;
    unsigned int eventCardLoss_Sec = 0;
    unsigned int eventCardLoss_dSec = 0;

    /* Select clock frequency 32 MHz from USB PLL. */
    _CPDIV = 0;
    io_init();
    uart_init();
    spi_init();
    i2c2_init();
    adc_init();

    timer2_init();
    timer3_init();
    /* Enable Timer2. */
    T2CONbits.TON = 1;

#ifdef SERVO_CONTROL
    unsigned int time_counter = 0;
    unsigned int time_delay = 0;
    //ServoSet(3000, 1520);
    
#define SERVO_ON_TIME 10000
    while(1)
    {
        time_delay++;
        if(time_delay > 100)
        {
            time_delay = 0;
            time_counter++;
            if( (time_counter == 16000) || (time_counter == 48000) )
            {
                ServoSet(3000, 1500);
                while(time_delay++< SERVO_ON_TIME );
                ServoStop();
            }
            else if(time_counter == 32000)
            {
                ServoSet(3000, 2200);
                while(time_delay++< SERVO_ON_TIME );
                ServoStop();
            }
            else if(time_counter > 64000)
            {
                time_counter = 0;
                ServoSet(3000, 800);
                while(time_delay++< SERVO_ON_TIME );
                ServoStop();
            }
        }
    }
#endif

    /* Read configuration selection. */
    if( CONF_SEL1 == 0 )
    {
        confSelect = 2;
    }
    else
    {
        confSelect = 0;
    }
    if( CONF_SEL2 == 0 )
    {
        confSelect++;
    }
    
    /* A_1_g  default 1359 units/g. */
    /* Ha_1_g default 262 units/g. */
    ap_ConfigurationData_t conf_data = {
        .A_1_g = 1359,
        .H_1_g = 262,
        .conf_select = confSelect };
    
    /* Buzzer beeps number of chosen configuration (+1 for counting from 1). */
    info( conf_data.conf_select + 1 );
    asm("nop");
    
	conf_data.conf_select 					= confSelect;
    conf_data.A_0_g                         = 0;    // Default 0.
    conf_data.H_0_g                         = 0;    // Default 0.
    conf_data.Y_0_g                         = 0;    // Default 0.
    conf_data.Z_0_g                         = 0;    // Default 0.
    conf_data.TemperatureOffset1            = 0;    // Default 0    - correction of temperature.
    conf_data.MainParachuteTriggerAltitude  = 200;  // Default 200  - 200 m.
    conf_data.SecondEngineDelayTrigger      = 0;    // Default 0    - delay before triggering second engine.
    conf_data.LaunchpadHeight               = 1;    // Default 1    - launchpad height is 1 m.
    conf_data.DrogueParaFailTreshold        = 50;   // Default 30   - treshold is 30 m/s.
    conf_data.SerialNumber                  = 10000;// Seria 0 - Arek, seria 10000 - PTR, seria 90000 - Special
    memset(conf_data.OwnerPhone, 0, OWNER_PHONE_LENGTH*2+1);
    memset(conf_data.OwnerName,  0, OWNER_NAME_LENGTH*2+1);
    
    conf_data_ptr = &conf_data;
    
    /*****SENSORS INITALIZATION AND CONFIGURATION*****/
    /* Configuration of low-g accelerometer. */
    acc24g_config();
    delay_ms( 10 );

    /* Configuration of high-g accelerometer. */
    conf_data.HaccPresent = acc80g_config();

    
//    if( ( conf_data.HaccPresent == 19969 ) || ( conf_data.HaccPresent == 24064 ) || (conf_data.HaccPresent == 0x5E1B) )
//    {
//        conf_data.HaccPresent = 1;
//    }
//    else
//    {
//        conf_data.HaccPresent = 0;
//    }
//    
//    while(1){
//        read_acc80();
//    }
    
    /* Pressure sensor configuration. */
    init_pressure();
    delay_ms( 10 );

    /* Read from emulated EEPROM initialization. */
    DataEEInit();
    dataEEFlags.val = 0;
    /* Read configuration data from EEPROM. */
    nvm_ConfDataReadAll( &conf_data );

    /* First pressure measurement. Next read will read this measurement, because of time needed for measurement. */
    read_pressure();
    delay_ms( 1 );
    /* Second pressure measurement, so it is able now to read proper pressure. */
    rv = read_pressure();
    if( rv > 1 )
    {
        ap_Summary.PressureGround = rv;
        ap_Summary.HeightAMSL = p2altitude( ap_Summary.PressureGround );
    }
    else
    {
        error( ERR_SENSOR_FAILURE );
    }
    
    /************* TEST FUSES *************/
    IGN_TEST = 1;
    delay_ms( 10 );
    _ASAM = 1;
    delay_ms( 10 );
    _ASAM = 1;
    delay_ms( 10 );
    
    if( ap_VbattSense < 100 ) // 99 div = 1 V
    {
        T3CONbits.TON = 1;
        ap_TestFusesOff = 1;
        
        uart_t( "CONFIGURATION MODE ENABLED\n" );
        
        USBDeviceInit();
        USBDeviceAttach();
        
        while(1)
        {
            if( USBGetDeviceState() < CONFIGURED_STATE ) continue;
            if( USBIsDeviceSuspended() == true ) continue;

            if( USBUSARTIsTxTrfReady() == true )
            {
                apCommHandler();
                
                if( ap_SendDataReady )
                {
                    putsUSBUSART( ap_SendBuffer);
                    ap_SendDataReady = 0;
                }
            }
            CDCTxService();
        }//end while
    }

    uart_t( "FLIGHT MODE ENABLED\n" );
    /*if(Vbatt_sense<376)
    {  // 99 div = 1 V
        ap_sprintf_safe( SendBuffer, SEND_BUFFER_SIZE, "battery %d\n", Vbatt_sense );
        uart_t( SendBuffer );
        error( ERR_LOW_BATTERY );
    }*/
    
    delay_ms( 10 );
    _ASAM = 0;
    
    /* Wait for SD card to power-up. */
    delay_ms( 1000 );
    
    /********* INITIALIZE SD CARD **********/
    while( !FSInit() )
    {
        uart_t( "FSInit...FAIL\n" );
        led_on();
    }
    uart_t( "FSInit...DONE\n" );
    
    attributes = ATTR_DIRECTORY | ATTR_ARCHIVE | ATTR_READ_ONLY | ATTR_HIDDEN;

    /* Find if there are saved measurement files. */
    if( FindFirst ( "MEAS*.csv", attributes, &rec ) == -1 )
    {
        /* If no files were found, create new first files. */
        rec.filename[0] = 'M';
        rec.filename[1] = 'E';
        rec.filename[2] = 'A';
        rec.filename[3] = 'S';
        rec.filename[4] = '0';
        rec.filename[5] = '1';
        rec.filename[6] = '.';
        rec.filename[7] = 'c';
        rec.filename[8] = 's';
        rec.filename[9] = 'v';
        rec.filename[10] = NULL;
    }
    else
    {
        /* Search through all files until end number (max "MEAS99.csv"). */
        while( !FindNext ( &rec ) );
        
        if( rec.filename[5] == '9' )
        {
            if( rec.filename[4] == '9' )
            {
                error( ERR_FILE_NUMBER_OVERFLOW );
            }
            rec.filename[5] = '0';
            rec.filename[4] = rec.filename[4] + 1;
        }
        else
        {
            rec.filename[5] = rec.filename[5] + 1;
        }
    }
    
    do
    {
        ap_FpMeas = FSfopen( rec.filename, "a" );
        DEBUG( "opening new next meas file to write\n" );
        delay_ms( 10 );
    }
    while( ap_FpMeas == NULL );
    
    /*
    // Create a file
    rec.filename[0] = 'S';
    rec.filename[1] = 'U';
    rec.filename[2] = 'M';
    rec.filename[3] = 'M';
    do
    {
        ap_FpFlightSummary = FSfopen( rec.filename, "a" );
        DEBUG( "opening new next summ file to write\n" );
        delay_ms( 10 );
    }
    while( ap_FpFlightSummary == NULL );
    */
    
    /*******CONTINUE TESTING FUSES********/
    ap_sprintf_safe( ap_SendBuffer, SEND_BUFFER_SIZE, "1 %d, 2 %d, 3 %d, Batt %.1f V\n",
        ap_FuseSense1, ap_FuseSense2, ap_FuseSense3, ( float )( ap_VbattSense )/99 ); // 99 div = 1 V
    uart_t( ap_SendBuffer );
    
    if( ap_FuseSense1 > FUSE_SENSE_THRESHOLD )
    {
        beep( SHORT_BEEP );
    }
    else
    {
        beep( LONG_BEEP );
    }
    delay_ms( 200 );
    
    if( ap_FuseSense2 > FUSE_SENSE_THRESHOLD )
    {
        beep( SHORT_BEEP );
    }
    else
    {
        beep( LONG_BEEP );
    }
    delay_ms(200);
    
    if( ap_FuseSense3 > FUSE_SENSE_THRESHOLD )
    {
        beep( SHORT_BEEP );
    }
    else
    {
        beep( LONG_BEEP );
    }
    delay_ms( 1000 );
    
    /******WRITE CONFIGURATION DATA*******/
    ap_sprintf_safe( ap_SendBuffer, SEND_BUFFER_SIZE, "a 1 g: %d\nHa 1 g: %d\n", conf_data.A_1_g, conf_data.H_1_g );
    uart_t( ap_SendBuffer );
    
    /* First part of header must be written here. */
    write_header_line( "Hardware version,%d.%d\r\n", MAJOR_HARDWARE, MINOR_HARDWARE );
    write_header_line( "Software version,%s %s\r\n", __DATE__, __TIME__ );
    write_header( ap_FpMeas, &conf_data );

    /* Read acceleration, the data will be now measured and read later. */
    ap_Hacc_temp = read_acc80();
    if( ap_Hacc_temp != HACC_READ_ERROR )
    {
        ap_Acc.ha = ap_Hacc_temp;
    }
    
    if( conf_data.HaccPresent )
    {
        ap_sprintf_safe( ap_SendBuffer, SEND_BUFFER_SIZE, "High g accelerometer is present\n" );
    }
    else
    {
        ap_sprintf_safe( ap_SendBuffer, SEND_BUFFER_SIZE, "High g accelerometer is NOT present\n" );
    }
    uart_t( ap_SendBuffer );
    ap_sprintf_safe( ap_SendBuffer, SEND_BUFFER_SIZE, "All OK\n" );
    uart_t( ap_SendBuffer );

    beep( LONG_BEEP );
    timer_init();

    /* Beep to signalize that SD card is OK and Arecorder is writing data. */
    
    ap_ArecorderState = AWAITING_FOR_LAUNCH;
    /* Debug start of saving data. */
    //ap_WriteData = 1;

    T4CONbits.TCKPS = 1;
    while( 1 )
    {
        /* If there is at least one buffer to write. */
        if( ap_BufferCurrent > ap_BufferOutput )
        {
            if( ap_BufferCurrent >= ( ap_BufferOutput + NUMBER_OF_BUFFERS ) )
            {
                ap_BufferOutput = ap_BufferOutput +
                    ( ( ( ap_BufferCurrent - ap_BufferOutput )/NUMBER_OF_BUFFERS_WRITTEN ) -
                      ( NUMBER_OF_BUFFER_SETS - 1 ) )*NUMBER_OF_BUFFERS_WRITTEN ;
            }
            if( ap_WriteToSD )
            {
                FSfwrite( ap_Buffer[ap_BufferOutput % NUMBER_OF_BUFFERS], 1,
                  strlen( ap_Buffer[ap_BufferOutput % NUMBER_OF_BUFFERS] ), ap_FpMeas );
            }
            ap_BufferOutput++;
            /* If currently written buffer number is greater than total number of buffers. */
            if( ap_BufferOutput >= NUMBER_OF_BUFFERS )
            {
                ap_BufferOutput  = ap_BufferOutput  - NUMBER_OF_BUFFERS;
                ap_BufferCurrent = ap_BufferCurrent - NUMBER_OF_BUFFERS;
            }
        }
        
        
        if( ap_BufferOutput % NUMBER_OF_BUFFERS_WRITTEN == 0 )
        {
            if( ap_WriteToSD )
            {
#if( 0 )
                TMR4 = 0;
                T4CONbits.TON = 1;
#endif
                rvSync = FSfsync( ap_FpMeas );
                if( rvSync != 0 )
                {
                    ap_BufferOutput = ap_BufferOutput - NUMBER_OF_BUFFERS_WRITTEN;
                    if( ap_BufferOutput < 0 )
                    {
                        ap_BufferOutput = ap_BufferOutput + NUMBER_OF_BUFFERS;
                        ap_BufferCurrent = ap_BufferCurrent + NUMBER_OF_BUFFERS;
                    }
                    eventCardLoss_Sec = ap_Seconds;
                    eventCardLoss_dSec = ap_Timer;
                    reinitializeSDCard = 1;
                    DEBUG( "SD disconnected!\n" );
                }
#if( 0 )
                T4CONbits.TON = 0;
                if( ( ap_BufferCurrent - ap_BufferOutput ) > 20 )
                {
                    ap_sprintf_safe( ap_SendBuffer, SEND_BUFFER_SIZE, "%u,%u %u %u %u %u\n",
                         ap_Seconds, ap_Timer, ( TMR4 >> 11 ), ap_BufferCurrent, ap_BufferOutput, ap_BufferCurrent - ap_BufferOutput );
                    DEBUG( ap_SendBuffer );
                }
#endif
                if( ap_WriteInitData == 1 )
                {
                    //FSfsync( ap_FpFlightSummary );
                    ap_WriteInitData = 2;
                }
            } // TODO: Move turning on writing data outside of if(BufferOutput...).
            else if( ap_WriteData == 1 ) // beginning condition
            {
                // begin writing NUMBER_OF_BUFFERS_WRITTEN current buffer
                ap_BufferCurrent = ap_BufferCurrent + NUMBER_OF_BUFFERS;
                ap_BufferOutput = ap_BufferCurrent - NUMBER_OF_BUFFERS_WRITTEN*OMIT_BUFFER_MULTIPLIER;
                ap_WriteToSD = 1;
            }
        }
        
        while( reinitializeSDCard )
        {
FSInit:
            while( !FSInit() );
            
            rec.filename[0] = 'M';
            rec.filename[1] = 'E';
            rec.filename[2] = 'A';
            rec.filename[3] = 'S';
            
            ap_FpMeas = FSfopen( rec.filename, "a" );
            if( ap_FpMeas == NULL ) goto FSInit;
            
            rec.filename[0] = 'S';
            rec.filename[1] = 'U';
            rec.filename[2] = 'M';
            rec.filename[3] = 'M';
            
            //ap_FpFlightSummary = FSfopen( rec.filename, "a" );
            //if( ap_FpFlightSummary == NULL ) goto FSInit;
            
            ap_sprintf_safe( ap_SendBuffer, SIZE_OF_SD_BUFFER,
                            "Card connection loss from,%u.%02d,to,%u.%02d\r\n",
                            eventCardLoss_Sec, eventCardLoss_dSec, ap_Seconds,
                            ap_Timer);
            DEBUG( ap_SendBuffer );
            
            FSfwrite( ap_SendBuffer, 1, strlen(ap_SendBuffer), ap_FpMeas );
            
            rv = FSfsync( ap_FpMeas );
            if( rv != 0 )
            {
                eventCardLoss_Sec = ap_Seconds;
                eventCardLoss_dSec = ap_Timer;
                reinitializeSDCard = 1;
            }
            else
            {
                reinitializeSDCard = 0;
            }
        }
    }
}

/* Interrupt every 10 ms. */
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt( void )
{
/**************************** General variables ******************************/
    /* Temporary return value from function. */
    static float rv;
    /* Flag if initial readings from sensors are done. */
    static unsigned int InitDone = 0;
    /* Time from rocket start. */
    static unsigned int Timer2 = 0;
    /* Buffer for events time writing. */
    static ap_Event_t Event;

/**************************** Pressure variables *****************************/
    static ap_KalmanData_t P = {.derivativePost = 0, .errorCovPost = 1};

    static float PressureLast = 0;  // previous value of PressurePost [Pa]
    static float AltitudeFromPressureRaw = 0;       // altitude calculated from pressure [m]
    static float AltitudeFromPressureRawOld = 0;    // previously calculated altitude from pressure [m]
    static float VelocityFromPressure = 0;      // rocket velocity calculated from pressure [m/s]
    static unsigned int ParachuteFailureSenseCnt = 0;   // variable counting algorhitm ticks
    

/************************* Accelerometer variables ***************************/
    static float Y_acc = 0;     // acceleration used to calculate rocket agngle [g/85]
    static float Z_acc = 0;     // acceleration used to calculate rocket agngle [g/85]
    static float aVertical;     // vertical rocket acceleration [m/s^2]
    static float aHorizontal;   // horizontal rocket acceleration [m/s^2]
    static float AccTemp;
    static float vAxis = 0;     // acceleration in rocket axis [m/s]
    static float VaxisMin;      // minimum rocket velocity in flight after engine burnout [m/s]
    static float vVertical = 0; // vertical rocket velocity [m/s]
    static float vHorizontal = 0; // horizontal rocket velocity [m/s]
    //float Droga = 0;
    static float Altitude = 0;  // rocket altitude [m]
    static float h_max_predict = 0;

/***************************** Other variables *******************************/
    static float RocketAngleDeg;    // rocket angle to the ground [degrees]
    static float RocketAngleRad;    // rocket angle to the ground [rad]

    static unsigned int Stan_i = 0;
    static unsigned int Stan_ii = 0;
    static ap_Fuse_t Trigger_fuse = FUSE_IDLE;

    if( InitDone != 1 )
    {
        /* Set minimum pressure as pressure at ground. */
        ap_Summary.PressureMinimum = ap_Summary.PressureGround;
        P.post = ap_Summary.PressureGround;
        P.postLast = P.post;
        
        InitDone = 1;
    }
    
    //TMR4 = 0;
    //T4CONbits.TON = 1;
    // Timera1 interrupts every 10 ms, so Timer*10 = time in [ms]
    ap_Timer++;
    IFS0bits.T1IF = 0;
    if( ap_Timer >= 100 )
    {
        /* 100 Timer1 ticks is 1 second. */
        ap_Seconds++;
        ap_Timer = 0;
    }
    if( ap_ArecorderState > AWAITING_FOR_LAUNCH )
    {
        Timer2++;
    }
    /* For first 10 seconds flash fuse diodes with 10 Hz frequency. */
    if( ap_Seconds < 10 )
    {
        if(ap_Timer%10 == 0)
        {
            IGN_TEST = 1;
        }
        else if(ap_Timer%10 == 5)
        {
            IGN_TEST = 0;
        }
    }
    
    read_acc24( &ap_Acc );
    ap_Hacc_temp = read_acc80();
    if( ap_Hacc_temp != HACC_READ_ERROR )
    {
        ap_Acc.ha = ap_Hacc_temp;
    }

    /* Acceleration with gravity. */
    AccTemp = ( ap_Acc.x - conf_data_ptr->A_0_g ) / conf_data_ptr->A_1_g;
    
    /* Axis [m/s] = ((x_acc - 0g)/1g)*g_const */
    /* If acceleration is greater than 20 g, use data from high-g accelerometer,
     * else use data from low-g accelerometer. */
    if( ( ( AccTemp > 20 ) || ( AccTemp < -20 ) ) && conf_data_ptr->HaccPresent )
    {
        ap_Acc.a_axis = ( float )( ap_Acc.ha - conf_data_ptr->H_0_g ) / conf_data_ptr->H_1_g * G_CONST;
    }
    else
    {
        ap_Acc.a_axis = ( float )( ap_Acc.x - conf_data_ptr->A_0_g ) / conf_data_ptr->A_1_g * G_CONST;
    }
    
    rv = read_pressure();
    if( rv > 1 )
    {
        P.raw = rv;
    }
    kalman_filter( &P );

    /**************** Calculating altitude from acceleration. ****************/
    if( ap_ArecorderState <= AWAITING_FOR_LAUNCH )
    {
        /* If rocket is not launching, calculate angle, at which rocket is leaning to the ground. */
        if( Stan_i == 0 )
        {
            /* Low pass filter to reduce acceleration noise. */
            Y_acc = Y_acc*0.98f + ap_Acc.y*0.02f;
            Z_acc = Z_acc*0.98f + ap_Acc.z*0.02f;
            
            /* Angle = acos( sqrt( y_acc^2 + z_acc^2 ) ) */
            RocketAngleRad = acosf( sqrtf( powf( ( ( Y_acc - conf_data_ptr->Y_0_g ) / conf_data_ptr->A_1_g ), 2 ) +
                                           powf( ( ( Z_acc - conf_data_ptr->Z_0_g ) / conf_data_ptr->A_1_g ), 2 ) ) );
        }
    }
    /* Angle = acos( Vpoziom / Vaxis ) */
    else
    {
        if( ap_DataValid )
        {
            RocketAngleRad = acosf( vHorizontal/vAxis );
        }
    }
    
    /* Angle [degrees] = angle [radians] *180/pi */
    RocketAngleDeg = RocketAngleRad*180/M_PI;
    
    /* Calculate if rocket didn't launch yet. */
    if( ap_ArecorderState >= AWAITING_FOR_LAUNCH )
    {
        /* aVertical [m/s] = aAxis*sin( angle ) - g_const */
        aVertical = ap_Acc.a_axis*sinf( RocketAngleRad ) - G_CONST;
        /* aHorizontal [m/s] = aAxis*cos( angle ) */
        aHorizontal = ap_Acc.a_axis*cosf( RocketAngleRad );
        
        /* Velocity. */
        vVertical = aVertical/100 + vVertical;
        vHorizontal = aHorizontal/100 + vHorizontal;
        vAxis = sqrtf( vVertical*vVertical + vHorizontal*vHorizontal );
        
        /* Altitude. */
        Altitude = vVertical/100 + Altitude;
    }
    /* If at any time altitude is less than zero, it means acceleration and velocity are calculated when rocket is
     * descending ornegative altitude is caused by accelerometer noise, when rocket has not yet launched. In that case
     * zero both velocity and altitude. */
    if( ( Altitude < 0 ) && ( ( ap_ArecorderState < FIRST_ENGINE_ACTIVE ) ||
                              ( ap_ArecorderState >= AWAITING_FOR_SECOND_PARACHUTE ) ) )
    {
        if( ap_ArecorderState >= AWAITING_FOR_SECOND_PARACHUTE )
        {
            ap_DataValid = 0;
        }
        vAxis = 0;
        vVertical = 0;
        vHorizontal = 0;
        Altitude = 0;
    }
    /************ End of calculating altitude from acceleration. *************/

    /* Begin calculating minimum pressure after first engine burnout. */
    if( ( P.post < ap_Summary.PressureMinimum ) &&
        ( ap_ArecorderState > FIRST_ENGINE_ACTIVE ) )
    {
        ap_Summary.PressureMinimum = P.post;
    }

    if( ap_ArecorderState <= AWAITING_FOR_PEAK_ALTITUDE )
    {
        if( Altitude > ap_Summary.AltitudeMax )
        {
            ap_Summary.AltitudeMax = Altitude;
        }
        
        if( vAxis > ap_Summary.VAxisMax )
        {
            ap_Summary.VAxisMax = vAxis;
        }
    }

    /* Calculate altitude from pressure only between rocket start and landing, when rocket is above ground. */
    if( ap_WriteData )
    {
        /* Save old altitude for velocity calculation. */
        AltitudeFromPressureRawOld = AltitudeFromPressureRaw;
        /* Calculate new altitude with moving weighted average. */
        AltitudeFromPressureRaw = AltitudeFromPressureRawOld*DROGUE_PARA_FAIL_AVERAGE_WEIGHT +
                ( p2altitude( P.raw ) - ap_Summary.HeightAMSL )*( 1 - DROGUE_PARA_FAIL_AVERAGE_WEIGHT );
        /* Calculate descend velocity. */
        VelocityFromPressure = ( AltitudeFromPressureRaw - AltitudeFromPressureRawOld )*100;
    }

    /*************************************************************************/
    /* ap_ArecorderState - detecting when to perform different actions on
     * rocket.                                                               */
    /*************************************************************************/
    switch( ap_ArecorderState )
    {
    /********************* AWAITING_FOR_ARECORDER_READY **********************/
    /* Arecorder is initializing, rocket is on the ground.                   */
    /*************************************************************************/
    case AWAITING_FOR_ARECORDER_READY:      // 0
        break;
    /************************** AWAITING_FOR_LAUNCH **************************/
    /* Arecorder is initialized, awaiting for rocket launch.                 */
    /*************************************************************************/
    case AWAITING_FOR_LAUNCH:           // 1
        if( ( ap_Acc.a_axis > 1.2f*G_CONST ) || ( h_max_predict > 1 ) )
        {
            ap_WriteInitData = 1;
            /* If calculated altitude is higher than 1 m it is assumed rocket
             * could launch. Confirmation required. */
            if( h_max_predict > 1 )
            {
                ap_WriteData = 1;
            }
            buzzer_on();
            Stan_i++;
            h_max_predict = vVertical*vVertical/( 2*G_CONST ) + Altitude;
            /* If rocket altitude is higher than launchpad, it is confirmed that
             * rocket launched. */
            if( Altitude > conf_data_ptr->LaunchpadHeight )
            {
                ap_WriteData = 1;
                ap_ArecorderState = FIRST_ENGINE_ACTIVE;
                /* Time from launch including correction from difference between
                 * assumed and confirmed launch. */
                Timer2 = Stan_i;
                Stan_i = 0;
                /* Save rocket angle at launch. */
                ap_Summary.RocketAngleStart = RocketAngleDeg;
                ap_Summary.LaunchpadVelocity = vAxis;
                buzzer_off();
                //writeInitialSummary( &ap_Summary );
                ap_WriteInitData = 1;
            }
        }
        else
        {
            /* Cooldown of assumed launch. */
            if( Stan_i > 0 )
            {
                Stan_i--;
            }
            else
            {
                /* Update ground pressure. */
                ap_Summary.PressureGround = P.post;
                ap_Summary.HeightAMSL = p2altitude( ap_Summary.PressureGround );
                buzzer_off();
                /* Minimum pressure follows ground pressure when rocket is
                 * awaiting for launch. */
                ap_Summary.PressureMinimum = P.post;
                h_max_predict = 0;
                
                Stan_i = 0;
                vAxis = 0;
                vVertical = 0;
                vHorizontal = 0;
                Altitude = 0;
            }
        }
        /* If assumed launch is detected, write time of rocket launch. Time is being updated at the beginning of each
         * assumed launch. */
        if(Stan_i == 1)
        {
            Event.launch.Sec = ap_Seconds;
            Event.launch.dSec = ap_Timer;
        }
        break;
    /************************** FIRST_ENGINE_ACTIVE **************************/
    /* Rocket has launched, wait for first engine burnout.                   */
    /*************************************************************************/
    case FIRST_ENGINE_ACTIVE:           // 2
        /* If current velocity is lower than maximum for more than 100 ms, then first engine has burnout. */
        if( vAxis < ap_Summary.VAxisMax )
        {
            Stan_i++;
            if( Stan_i > 10 )
            {
                /* The initial value of VaxisMin is equal to current velocity to ensure the minimum velocity will be
                 * properly detected. */
                VaxisMin = vAxis;
                ap_ArecorderState = WAITING_FOR_SECOND_ENGINE_TIME_TRIGGER;
                Stan_i = 0;
            }
        }
        else
        {
            Stan_i = 0;
        }
        if(Stan_i == 1)
        {
            Event.burnout1.Sec = ap_Seconds;
            Event.burnout1.dSec = ap_Timer;
            ap_Summary.Engine1Burnout_VAxis = vAxis;
            ap_Summary.Engine1Burnout_Altitude = Altitude;
            ap_Summary.Engine1Burnout_Pressure = P.post;
            ap_Summary.Engine1Burnout_RocketAngle = RocketAngleDeg;
        }
        break;
    /***************** WAITING_FOR_SECOND_ENGINE_TIME_TRIGGER ****************/
    /* First engine burnout, wait programmed time before firing
     * second engine.                                                        */
    /*************************************************************************/
    case WAITING_FOR_SECOND_ENGINE_TIME_TRIGGER:    // 3
        Stan_i++;
        if( Stan_i > conf_data_ptr->SecondEngineDelayTrigger )
        {
            Trigger_fuse = FUSE_STG2;
            ap_ArecorderState = AWAITING_FOR_SECOND_ENGINE_START;
            Stan_i = 0;
        }
        break;
    /******************** AWAITING_FOR_SECOND_ENGINE_START *******************/
    /* Second engine fired, wait for second engine start.                    */
    /*************************************************************************/
    case AWAITING_FOR_SECOND_ENGINE_START:      // 4
        /* If rocket thrust equals rocket weight it means second engine is working. */
        if( ap_Acc.a_axis > 1*G_CONST )
        {
            buzzer_on();
            if( Stan_i == 1 )
            {
                Event.stg2Active.Sec = ap_Seconds;
                Event.stg2Active.dSec = ap_Timer;
                /* If there is no second engine, then set second engine burnout also at this time. If there is second
                 * engine, these values will be overwritten. */
                Event.burnout2.Sec = ap_Seconds;
                Event.burnout2.dSec = ap_Timer;
            }
            Stan_i++;
            /* If acceleration lasts long enough, it is confirmed that second engine is working. */
            if( Stan_i >= 50 )
            {
                ap_ArecorderState = SECOND_ENGINE_ACTIVE;
                Stan_i = 0;
                buzzer_off();
            }
        }
        else
        {
            Stan_i = 0;
            buzzer_off();
        }
        
        /* If pressure is increasing - rocket is descending. */
        if( P.derivativePost > 0 )
        {
            buzzer_on();
            if( Stan_ii == 1 )
            {
                Event.apogee.Sec = ap_Seconds;
                Event.apogee.dSec = ap_Timer;
            }
            Stan_ii++;
            if( VaxisMin > vAxis )
            {
                VaxisMin = vAxis;
                Event.minV.Sec = ap_Seconds;
                Event.minV.dSec = ap_Timer;
            }
            /* Rocket descends at least for PEAK_ALTITUDE_SENSE_DELAY. */
            if( Stan_ii >= PEAK_ALTITUDE_SENSE_DELAY )
            {
                /* If rocket is below SAFETY_TRIGGER_HEIGHT, fire parachute immediately,
                 * else wait for minimum velocity. */
                if( ( p2altitude( P.post ) - ap_Summary.HeightAMSL ) > SAFETY_TRIGGER_HEIGHT )
                {
                    if( vAxis > ( VaxisMin + 2 ) )
                    {
                        /* Fire parachute if velocity begins increasing. */
                        Trigger_fuse = FUSE_PARA1;
                        ap_ArecorderState = AWAITING_FOR_SECOND_PARACHUTE;
                        buzzer_off();
                        Stan_ii = 0;
                    }
                }
                else
                {
                    Trigger_fuse = FUSE_PARA1;
                    ap_ArecorderState = AWAITING_FOR_SECOND_PARACHUTE;
                    buzzer_off();
                    Stan_ii = 0;
                }
            }
        }
        else
        {
            Stan_ii = 0;
            buzzer_off();
        }
        break;
    /************************** SECOND_ENGINE_ACTIVE *************************/
    /* Second engine is active, wait for second engine burnout.              */
    /*************************************************************************/
    case SECOND_ENGINE_ACTIVE:          // 5
        if( vAxis < ap_Summary.VAxisMax )
        {
            Event.burnout2.Sec = ap_Seconds;
            Event.burnout2.dSec = ap_Timer;
            ap_Summary.Engine2Burnout_VAxis = vAxis;
            ap_Summary.Engine2Burnout_Altitude = Altitude;
            ap_Summary.Engine2Burnout_Pressure = P.post;
            ap_Summary.Engine2Burnout_RocketAngle = RocketAngleDeg;
            ap_ArecorderState = AWAITING_FOR_PEAK_ALTITUDE;
        }
        break;
    /*********************** AWAITING_FOR_PEAK_ALTITUDE **********************/
    /* Second engine burnout, wait for peak altitude.                        */
    /*************************************************************************/
    case AWAITING_FOR_PEAK_ALTITUDE:    // 6
        if( P.derivativePost > 0 )
        {
            buzzer_on();
            if( Stan_ii == 0 )
            {
                Event.apogee.Sec = ap_Seconds;
                Event.apogee.dSec = ap_Timer;
            }
            Stan_i++;
            if( VaxisMin > vAxis )
            {
                VaxisMin = vAxis;
                Event.minV.Sec = ap_Seconds;
                Event.minV.dSec = ap_Timer;
            }
            /* Rocket descends at least for PEAK_ALTITUDE_SENSE_DELAY. */
            if( Stan_i >= PEAK_ALTITUDE_SENSE_DELAY )
            {
                /* If rocket is below SAFETY_TRIGGER_HEIGHT, fire parachute immediately,
                 * else wait for minimum velocity. */
                if( ( p2altitude( P.post ) - ap_Summary.HeightAMSL ) > SAFETY_TRIGGER_HEIGHT )
                {
                    if( vAxis > ( VaxisMin + 2 ) )
                    {
                        /* Fire parachute if velocity begins increasing. */
                        Trigger_fuse = FUSE_PARA1;
                        ap_ArecorderState = AWAITING_FOR_SECOND_PARACHUTE;
                        buzzer_off();
                        Stan_i = 0;
                        Stan_ii = 0;
                    }
                }
                else
                {
                    Trigger_fuse = FUSE_PARA1;
                    ap_ArecorderState = AWAITING_FOR_SECOND_PARACHUTE;
                    buzzer_off();
                    Stan_ii = 0;
                    Stan_i = 0;
                }
            }
        }
        else
        {
            Stan_i = 0;
            buzzer_off();
        }
        break;
    /********************* AWAITING_FOR_SECOND_PARACHUTE *********************/
    /* First parachute is fired, check if first parachute is deployed and wait for second parachute firing. */
    /*************************************************************************/
    case AWAITING_FOR_SECOND_PARACHUTE:     // 7
        if( ( p2altitude( P.post ) - ap_Summary.HeightAMSL ) < conf_data_ptr->MainParachuteTriggerAltitude )
        {
            buzzer_on();
            Stan_i++;
            if( Stan_i >= DROGUE_PARACHUTE_COUNTER )
            {
                Trigger_fuse = FUSE_PARA2;
                ap_ArecorderState = AWAITING_FOR_LANDING;
                buzzer_off();
                Stan_i = 0;
                Stan_ii = 0;
            } 
        }
        else
        {
            Stan_i = 0;
            buzzer_off();
        }
        
        /* Zero means algorithm is disabled. */
        if( conf_data_ptr->DrogueParaFailTreshold != 0)
        {
            /* Add 3s deadtime before failure detection*/
            if(Stan_ii < 300)
            {
                Stan_ii++;
            }
            
            /* Mind that rocket is descending and velocity is negative. */
            else if( VelocityFromPressure < - (float)(conf_data_ptr->DrogueParaFailTreshold))
            {
                ParachuteFailureSenseCnt++;
                if( ParachuteFailureSenseCnt > PARACHUTE_FAILURE_SENSE_COUNTER )
                {
                    Trigger_fuse = FUSE_PARA2;
                    ap_ArecorderState = AWAITING_FOR_LANDING;
                    buzzer_off();
                    Stan_i = 0;
                    Stan_ii = 0;
                }
            }
            else
            {
                if( ParachuteFailureSenseCnt > 0 )
                {
                    ParachuteFailureSenseCnt--;
                }
            }
        }
        break;
    /************************* AWAITING_FOR_LANDING **************************/
    /* Second parachute fired, wait for landing.                             */
    /*************************************************************************/
    case AWAITING_FOR_LANDING:          // 8
        if( ap_Timer%100 == 0 )
        {
            /* If in next four seconds pressure difference will be less than 30 Pa, rocket landed. */
            if( ( P.post - PressureLast ) < 30.0f )
            {
                Stan_i++;
                if( Stan_i > 3 )
                {
                    ap_ArecorderState = ROCKET_HAS_LANDED;
                    Stan_i = 0;
                    Event.land.Sec = ap_Seconds;
                    Event.land.dSec = ap_Timer;
                }
            }
            else
            {
                Stan_i = 0;
            }
            PressureLast = P.post;
        }
        break;
    /*************************** ROCKET_HAS_LANDED ***************************/
    /* Rocket has landed. After one minute stop writing data.                */
    /*************************************************************************/
    case ROCKET_HAS_LANDED:         // 9
        if( ap_Timer == 0 ) buzzer_on();
        if( ap_Timer == 20 ) buzzer_off();
        Stan_i++;
        if( Stan_i > 6000 )
        {
            ap_ArecorderState = STOP_WRITING_DATA;
            Stan_i = 0;
        }
        break;
    /*************************** STOP_WRITING_DATA ***************************/
    /* Stop writing data. Write summary data.                                */
    /*************************************************************************/
    case STOP_WRITING_DATA:         // 10
        ap_WriteData = 0;
        ap_WriteToSD = 0;
        Stan_i++;
        /* Wait 10 seconds to be sure all remaining data has been written. */
        if( Stan_i > 100 )
        {
            writeInitialSummary( &ap_Summary );
            writeSummary( &ap_Summary, &Event );
            ap_ArecorderState = ACTIVATE_BUZZER;
        }    
        break;
    /**************************** ACTIVATE_BUZZER ****************************/
    /* All data written. Start buzzer.                                       */
    /*************************************************************************/
    case ACTIVATE_BUZZER:           // 11
        if( ap_Timer == 0 )
        {
            buzzer_on();
        }
        if( ap_Timer == 20 )
        {
            buzzer_off();
        }
        break;
    /******************************** DEFAULT ********************************/
    /* Error condition, should never happen. In case it does, go to detecting second parachute deployment and write
     * error message.                                                        */
    /*************************************************************************/
    default:
        ap_sprintf_safe( ap_SendBuffer, SEND_BUFFER_SIZE, "[ERROR] Stan = %d, time %d.%02d\r\n", ap_ArecorderState,
                        ap_Seconds, ap_Timer );
        //FSfwrite( ap_SendBuffer, 1, strlen( ap_SendBuffer ), ap_FpFlightSummary );
        //FSfsync( ap_FpFlightSummary );
        Trigger_fuse = FUSE_PARA1;
        ap_ArecorderState = AWAITING_FOR_SECOND_PARACHUTE;
        break;
    }
    /************************** END OF STATE SWITCH **************************/
    if( Trigger_fuse )
    {
        switch( Trigger_fuse )
        {
        case FUSE_IDLE:
            break;
        case FUSE_PARA1:
            OUT1 = 1;
            Trigger_fuse = FUSE_TURN_OFF;
            Event.para1.Sec = ap_Seconds;
            Event.para1.dSec = ap_Timer;
            break;
        case FUSE_PARA2:
            OUT2 = 1;
            Trigger_fuse = FUSE_TURN_OFF;
            Event.para2.Sec = ap_Seconds;
            Event.para2.dSec = ap_Timer;
            break;
        case FUSE_STG2:
            OUT3 = 1;
            Trigger_fuse = FUSE_TURN_OFF;
            Event.stg2Fire.Sec = ap_Seconds;
            Event.stg2Fire.dSec = ap_Timer;
            break;
        case FUSE_TURN_OFF:
            OUT1 = 0;
            OUT2 = 0;
            OUT3 = 0;
            Trigger_fuse = FUSE_IDLE;
            break;
        default:    
            ap_sprintf_safe( ap_SendBuffer, SEND_BUFFER_SIZE, "[ERROR] Trigger_fuse = %d, time %d.%d\r\n",
                             Trigger_fuse, ap_Seconds, ap_Timer );
            //FSfwrite( ap_SendBuffer, 1, strlen( ap_SendBuffer ), ap_FpFlightSummary );
            //FSfsync( ap_FpFlightSummary );
            Trigger_fuse = FUSE_IDLE;
            break;
        }
    }
    
    //T4CONbits.TON = 0;
    ap_sprintf_safe( ap_Buffer[ap_BufferCurrent%NUMBER_OF_BUFFERS], SIZE_OF_SD_BUFFER,
    /*                 4+2  | 5+ 5+ 5+ 5| 6 + 6 | 5  | 5  | 7  | 7  | 1| 5  | 1 | 3 + commas(14) = 86 */
    /*                time  | x  y  z ha|   p   | t  | v  |alp | al |st| vp |pf     */
                    "%u.%02d,%d,%d,%d,%d,%ld,%ld,%.1f,%.1f,%.1f,%.1f,%d,%.1f,%d\r\n",
                    ap_Seconds, ap_Timer, ap_Acc.x, ap_Acc.y, ap_Acc.z, ap_Acc.ha,
                    ( long )P.raw,                  // long
                    ( long )P.post,                 // long
                    temp_calculate( ap_TempSense, conf_data_ptr->TemperatureOffset1 ), // float
                    vAxis,                          // float
                    AltitudeFromPressureRaw,        // float
                    Altitude,                       // float
                    ap_ArecorderState,              // int
                    VelocityFromPressure,           // float
                    ParachuteFailureSenseCnt        // int
    );
    
    if( ap_BufferCurrent%20 == 0 )
    {
        //DEBUG( ap_Buffer[ap_BufferCurrent%NUMBER_OF_BUFFERS] );
        //ap_sprintf_safe( ap_SendBuffer, SEND_BUFFER_SIZE, "temp %d, %f\r\n", ap_TempSense, temp_calculate( ap_TempSense, 0 ) );
        //DEBUG( ap_SendBuffer );
        led_toggle();
    }
    ap_BufferCurrent++;
    
    
    _ASAM = 1;
}

/* Interrupt every 10 ms. */
void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt( void )
{
    if( ap_TimeoutI2C > 0 )
    {
        ap_TimeoutI2C--;
    }
    IFS0bits.T2IF = 0;
}

/* Interrupt every 100 ms. */
void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt( void )
{
    /* Averaged acceleration in Y axis, used to calculate rocket angle [g/85]. */
    static float Y_acc = 0;
    /* Averaged acceleration in Z axis, used to calculate rocket angle [g/85]. */
    static float Z_acc = 0;
    /* Rocket angle [degrees]. */
    static float RocketAngleDeg;
    /* Rocket angle [rad]. */
    static float RocketAngleRad;
    /* Fuse presence flag. */
    unsigned int fusePresent[3];
    /* Pressure measured from pressure sensor. */
    static float pressure;
    /* Temporary variable for return values. */
    static float rv;
    
    read_acc24( &ap_Acc );
    
    ap_Hacc_temp = read_acc80();
    if( ap_Hacc_temp != HACC_READ_ERROR )
    {
        ap_Acc.ha = ap_Hacc_temp;
    }
    
    rv = read_pressure();
    if( rv > 1 )
    {
        pressure = rv;
    }

    /* Low pass filter to reduce acceleration noise. */
    Y_acc = Y_acc*0.7f + ap_Acc.y*0.3f;
    Z_acc = Z_acc*0.7f + ap_Acc.z*0.3f;
    /* Angle = acos( sqrt( y_acc^2 + z_acc^2 ) ) */
    RocketAngleRad = acosf( sqrtf( powf( ( Y_acc-conf_data_ptr->Y_0_g )/conf_data_ptr->A_1_g, 2 ) +
        + powf( ( Z_acc-conf_data_ptr->Z_0_g )/conf_data_ptr->A_1_g, 2 ) ) );
    /* Angle [degrees] = angle [rad] *180/pi */
    RocketAngleDeg = RocketAngleRad*180/M_PI;
    /* Test if RocketAngleDeg is equal NaN. */
    if( RocketAngleDeg == RocketAngleDeg )
    {
        ;
    }
    else
    {
        RocketAngleDeg = 0;
    }
    /* Test if fuses are connected. */
    if( ap_FuseSense1 > FUSE_SENSE_THRESHOLD )
    {
        fusePresent[0] = 1;
    }
    else
    {
        fusePresent[0] = 0;
    }
    if( ap_FuseSense2 > FUSE_SENSE_THRESHOLD )
    {
        fusePresent[1] = 1;
    }
    else
    {
        fusePresent[1] = 0;
    }
    if( ap_FuseSense3 > FUSE_SENSE_THRESHOLD )
    {
        fusePresent[2] = 1;
    }
    else
    {
        fusePresent[2] = 0;
    }
        
    if( ap_SendDataDuringConfigure )
    {
        /*ap_sprintf_safe( ap_SendBuffer, SEND_BUFFER_SIZE, "M,%d,%d,%d,%d,%ld,%.1f,%.0f,%d,%d,%d,%0.1f\n",
            ap_Acc.x, ap_Acc.y, ap_Acc.z, ap_Acc.ha, ( long )pressure,
            temp_calculate( ap_TempSense, conf_data_ptr->TemperatureOffset1 ), //float
            RocketAngleDeg,
            fusePresent[0],
            fusePresent[1],
            fusePresent[2],
            ( float )( ap_VbattSense )/99 // 99 div = 1 V
        );
        uart_t( ap_SendBuffer );*/
        ap_sprintf_safe( ap_SendBuffer, SEND_BUFFER_SIZE, "M,%d,%d,%d,%d,%ld,%.1f,%.0f,%d,%d,%d,%0.1f\n",
            ap_Acc.x, ap_Acc.y, ap_Acc.z, ap_Acc.ha, ( long )pressure,
            temp_calculate( ap_TempSense, conf_data_ptr->TemperatureOffset1 ), //float
            RocketAngleDeg,
            fusePresent[0],
            fusePresent[1],
            fusePresent[2],
            ( float )( ap_VbattSense )/99 // 99 div = 1 V
        );
        ap_SendDataReady = 1;
    }
    /* Begin testing fuses. */
    IGN_TEST = 1;
    delay_ms( 1 );
    _ASAM = 1;
    IFS0bits.T3IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt( void )
{
    _ASAM = 0;
    ap_FuseSense2 = ADC1BUF0;    // AN0  - OUT 2 SENSE
    ap_FuseSense1 = ADC1BUF1;    // AN1  - OUT 1 SENSE
    ap_TempSense  = ADC1BUF2;    // AN2  - TEMP1
    ap_VbattSense = ADC1BUF3;    // AN3  - VBATT
    ap_FuseSense3 = ADC1BUF4;    // AN6  - OUT 3 SENSE
    /* End of fuse testing. */
    if( ap_TestFusesOff )
    {
        delay_ms( 3 );
        IGN_TEST = 0;
    }
    IFS0bits.AD1IF = 0;
}

bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size)
{
    switch( (int) event )
    {
        case EVENT_TRANSFER:
            break;

        case EVENT_SOF:
            /* We are using the SOF as a timer to time the LED indicator.  Call
             * the LED update function here. */
            APP_LEDUpdateUSBStatus();
            break;

        case EVENT_SUSPEND:
            APP_LEDUpdateUSBStatus();
            break;

        case EVENT_RESUME:
            APP_LEDUpdateUSBStatus();
            break;

        case EVENT_CONFIGURED:
            CDCInitEP();

            line_coding.bCharFormat = 0;
            line_coding.bDataBits = 8;
            line_coding.bParityType = 0;
            line_coding.dwDTERate = 9600;
            break;

        case EVENT_SET_DESCRIPTOR:
            break;

        case EVENT_EP0_REQUEST:
            /* We have received a non-standard USB request.  The HID driver
             * needs to check to see if the request was for it. */
            USBCheckCDCRequest();
            break;

        case EVENT_BUS_ERROR:
            break;

        case EVENT_TRANSFER_TERMINATED:
            break;

        default:
            break;
    }
    return true;
}

void __attribute__((interrupt,auto_psv)) _USB1Interrupt()
{
    USBDeviceTasks();
}

void __attribute__((interrupt, no_auto_psv)) _OscillatorFail(void)
{
    //check( ap_FpFlightSummary != NULL, "Oscillator fail-SUMM open err, %d.%ds\n", ap_Seconds, ap_Timer );
    //log_sd_err( "Oscillator fail, %d.%ds\r\n", ap_Seconds, ap_Timer );
error:
	INTCON1bits.OSCFAIL = 0;
	software_reset();
}

void __attribute__((interrupt, no_auto_psv)) _AddressError(void)
{
    //check( ap_FpFlightSummary != NULL, "Address Err-SUMM open err, %d.%ds\n", ap_Seconds, ap_Timer );
    //log_sd_err( "Address Err, %d.%ds\r\n", ap_Seconds, ap_Timer );
error:
	INTCON1bits.ADDRERR = 0;
	software_reset();
}

void __attribute__((interrupt, no_auto_psv)) _StackError(void)
{
    //check( ap_FpFlightSummary != NULL, "Stack Error-SUMM open err, %d.%ds\n", ap_Seconds, ap_Timer );
    //log_sd_err( "Stack Err, %d.%ds\r\n", ap_Seconds, ap_Timer );
error:
	INTCON1bits.STKERR = 0;
	software_reset();
}

void __attribute__((interrupt, no_auto_psv)) _MathError(void)
{
    //check( ap_FpFlightSummary != NULL, "Math Error - SUMM file not opened, time %d.%d\n", ap_Seconds, ap_Timer );
    //log_sd_err( "[ERROR] Math Error, time %d.%d\r\n", ap_Seconds, ap_Timer );
error:
	INTCON1bits.MATHERR = 0;
	software_reset();
}
