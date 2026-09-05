/*****************************************************************************/
/*                                 INCLUDES                                  */
/*****************************************************************************/
#include <main.h>
#include <APlib.h>
#include <DEE_Emulation_16-bit.h>
#include <Communication.h>
#include <../usb_framework/inc/usb_device_cdc.h>

/*****************************************************************************/
/*                             GLOBAL VARIABLES                              */
/*****************************************************************************/
static char UsbReadBuffer[CDC_DATA_OUT_EP_SIZE];
static char UsbWriteBuffer[CDC_DATA_IN_EP_SIZE];
extern ap_ConfigurationData_t *conf_data_ptr;
extern ap_summaryData_t ap_Summary;
extern unsigned int ap_VbattSense;
extern int ap_SendDataReady;
extern char ap_SendBuffer[];
/** \brief Flag if data should be sent out during configuration of Arecorder. */
extern unsigned int ap_SendDataDuringConfigure;

/*****************************************************************************/
/*                                 DEFINES                                   */
/*****************************************************************************/
#define COMM_MINIMUM_COMMAND_SIZE 4

/*****************************************************************************/
/*                                FUNCTIONS                                  */
/*****************************************************************************/

/******************************************************************************
 * \brief Function initializes timer1 for normal work.
 *
 * \input None.
 *
 * \output None.
 * ****************************************************************************/

void apCommHandler( void )
{
    uint8_t numBytesRead;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int EERead;
    unsigned int EEaddress = 0;
    int EEvalue = 0;
    char EEstring[31] = "";
    int negative = 0;
    
    numBytesRead = getsUSBUSART( UsbReadBuffer, (uint8_t)sizeof(UsbReadBuffer) );
    /*if( numBytesRead>0 )
    {
        ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "received data[%d]: ",
                                  numBytesRead);
        uart_t( UsbWriteBuffer );
        UsbReadBuffer[numBytesRead] = 0;
        uart_t( UsbReadBuffer );
        
    }*/
    if( numBytesRead < (uint8_t)COMM_MINIMUM_COMMAND_SIZE ) return;
    
    // ATF - Fire fuses.
    // ATI - Version of Arecorder.
    // ATP1 - Print all configuration bits and variables (part 1).
    // ATP2 - Print all configuration bits and variables (part 2).
    // ATPRINT - Print all configuration bits and variables (human readable).
    // ATS1 ATS0 - Send data while configuring.
    // ATW(address,value) - Write configuration bits.
    // ATZ - Back to default settings.

    // ATE - Error (just sending).
        
    if( ( UsbReadBuffer[0] == 'A' ) && ( UsbReadBuffer[1] == 'T' ) )
    {
        switch( UsbReadBuffer[2] )
        {
        case 'F':           // ATF - Fire fuses.
            /* ATFP1 - Fire fuse parachute 1.
               ATFP2 - Fire fuse parachute 2. */
            if( UsbReadBuffer[3] == 'P' )
            {
                if( UsbReadBuffer[4] == '1' )
                {
                    //uart_t( "Fire PARA1 fuse.\n" );
                    OUT1 = 1;
                    delay_ms( 10 );
                    OUT1 = 0;
                    //uart_t( "End firing.\n" );
                }
                else if( UsbReadBuffer[4] == '2' )
                {
                    //uart_t( "Fire PARA2 fuse.\n" );
                    OUT2 = 1;
                    delay_ms( 10 );
                    OUT2 = 0;
                    //uart_t( "End firing.\n" );
                }
            }
            /* ATFS2 - Fire fuse second stage. */
            else if( ( UsbReadBuffer[3] == 'S' ) &&
                     ( UsbReadBuffer[4] == '2' ) )
            {
                //uart_t( "Fire stage2 fuse.\n" );
                OUT3 = 1;
                delay_ms( 10 );
                OUT3 = 0;
                //uart_t( "End firing.\n" );
            }
            /* ATFALL - Fire all fuses. */
            else if( ( UsbReadBuffer[3] == 'A' ) &&
                     ( UsbReadBuffer[4] == 'L' ) &&
                     ( UsbReadBuffer[5] == 'L' ) )
            {
                //uart_t( "fire OUT1\n" );
                OUT1 = 1;
                delay_ms( 10 );
                OUT1 = 0;
                delay_ms( 90 );
                //uart_t( "fire OUT2\n" );
                OUT2 = 1;
                delay_ms( 10 );
                OUT2 = 0;
                delay_ms( 90 );
                //uart_t( "fire OUT3\n" );
                OUT3 = 1;
                delay_ms( 10 );
                OUT3 = 0;
                //uart_t( "end firing\n" );
            }
            break;
        case 'I':           // ATI - Version of Arecorder.
            (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "I,Arecorder,hv.,%d.%d,sv.%d.%d,%s %s\n",
                              MAJOR_HARDWARE, MINOR_HARDWARE, MAJOR_SOFTWARE, MINOR_SOFTWARE, __DATE__, __TIME__ );
            putsUSBUSART( UsbWriteBuffer );
            break;
        case 'P':           // ATA - Print all configuration bits and variables.
            nvm_ConfDataReadAll( conf_data_ptr );
            if( UsbReadBuffer[3] == 'R' )       //TODO nie działa prawidłowo
            {
                /* Human readable. */
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "A_0_g\t\t%d\n", conf_data_ptr->A_0_g );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "Y_0_g\t\t%d\n", conf_data_ptr->Y_0_g );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "Z_0_g\t\t%d\n", conf_data_ptr->Z_0_g );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "Ha_0_g\t\t%d\n", conf_data_ptr->H_0_g );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "A_1_g\t\t%d\n", conf_data_ptr->A_1_g );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "Ha_1_g\t\t%d\n", conf_data_ptr->H_1_g );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "TemperatureOffset1\t%d\n", conf_data_ptr->TemperatureOffset1 );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "MainParachuteTriggerHeight %d\n", conf_data_ptr->MainParachuteTriggerAltitude );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "SecondEngineDelayTrigger\t%d\n", conf_data_ptr->SecondEngineDelayTrigger );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "LaunchpadHeight\t%d\n", conf_data_ptr->LaunchpadHeight );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "Drogue parachute failure detection\t\t%d\n", conf_data_ptr->DrogueParaFailTreshold );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "SerialNumber\t%d\n", conf_data_ptr->SerialNumber );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "OwnerPhone\t\t%s\n", conf_data_ptr->OwnerPhone );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "OwnerName\t\t%s\n", conf_data_ptr->OwnerName );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "HaccPresent\t%d\n", conf_data_ptr->HaccPresent );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "PressureGround\t%d\n", ap_Summary.PressureGround );
                putsUSBUSART( UsbWriteBuffer );
                delay_ms( 10 );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "Battery\t\t%.1f V\n", ( float )( ap_VbattSense )/99 );  // 99 div = 1 V
                putsUSBUSART( UsbWriteBuffer );
            }
            else
            {
                /* Machine readable. */
                if( UsbReadBuffer[3] == '1' )
                {
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE,
                                         //0 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 20 21 22
                                        //A0 Y0 Z0 H0 A1 H1 T1 P1 P2 P3 P4 T1 T2 T3 T4 H1 H2 H3 H4
                                      "P1,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                          conf_data_ptr->A_0_g,
                          conf_data_ptr->Y_0_g,
                          conf_data_ptr->Z_0_g,
                          conf_data_ptr->H_0_g,
                          conf_data_ptr->A_1_g,
                          conf_data_ptr->H_1_g,
                          conf_data_ptr->TemperatureOffset1,
                          nvm_ConfDataGet( MAIN_PARA_H1 ),
                          nvm_ConfDataGet( MAIN_PARA_H2 ),
                          nvm_ConfDataGet( MAIN_PARA_H3 ),
                          nvm_ConfDataGet( MAIN_PARA_H4 ),
                          nvm_ConfDataGet( SECOND_ENGINE_DELAY_TRIGGER1 ),
                          nvm_ConfDataGet( SECOND_ENGINE_DELAY_TRIGGER2 ),
                          nvm_ConfDataGet( SECOND_ENGINE_DELAY_TRIGGER3 ),
                          nvm_ConfDataGet( SECOND_ENGINE_DELAY_TRIGGER4 ),
                          nvm_ConfDataGet( LAUNCHPAD_HEIGHT1 ),
                          nvm_ConfDataGet( LAUNCHPAD_HEIGHT2 ),
                          nvm_ConfDataGet( LAUNCHPAD_HEIGHT3 ),
                          nvm_ConfDataGet( LAUNCHPAD_HEIGHT4 ) );
                putsUSBUSART( UsbWriteBuffer );
                }
                else if( UsbReadBuffer[3] == '2' )
                {
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "P2,%d,%d,%d,%d,%d,%s,%s\n",
                    nvm_ConfDataGet( DROGUE_PARACHUTE_FAILURE_TRESHOLD1 ),
                    nvm_ConfDataGet( DROGUE_PARACHUTE_FAILURE_TRESHOLD2 ),
                    nvm_ConfDataGet( DROGUE_PARACHUTE_FAILURE_TRESHOLD3 ),
                    nvm_ConfDataGet( DROGUE_PARACHUTE_FAILURE_TRESHOLD4 ),
                    conf_data_ptr->SerialNumber,
                    conf_data_ptr->OwnerPhone,
                    conf_data_ptr->OwnerName );
                putsUSBUSART( UsbWriteBuffer );
                }
            }
            break;
        case 'S':           // ATS - Send data while configuring.
            /* ATS1 - Send data.
               ATS0 - Don't send data. */
            if( UsbReadBuffer[3] == '1' )
            {
                ap_SendDataDuringConfigure = 1;
            }
            else if( UsbReadBuffer[3] == '0' )
            {
                ap_SendDataDuringConfigure = 0;
            }
            break;
        case 'W':           // ATW(address,value) - Write configuration bits.
            i = 4;
            EEaddress = (unsigned int)(UsbReadBuffer[i++] - '0');
            /* If no comma is detected, that means address is two-digit. */
            if( UsbReadBuffer[i] != ',' )
            {
                EEaddress = EEaddress*10 + (int)(UsbReadBuffer[i++] - '0');
            }
            EEvalue = 0;
            if( EEaddress == OWNER_PHONE )
            {
                /* Read data from read buffer and prepare them to write. */
                while( UsbReadBuffer[++i] != ')' )
                {
                    EEstring[j++] = UsbReadBuffer[i];
                    if( j >= OWNER_PHONE_LENGTH*2 ) 
                    {
                        break;
                    }
                }
                EEstring[j] = '\0';

                /* Write data to program memory. */
                for( j = 0; j < OWNER_PHONE_LENGTH; j++ )
                {
                    DataEEWrite(((unsigned int)EEstring[2*j] << 8) + (unsigned int)EEstring[2*j+1], OWNER_PHONE + j);
                }

                /* Read data from program memory to confirm that they are not corrupted. */
                for( i = 0; i < OWNER_PHONE_LENGTH; i++ )
                {
                    EERead = DataEERead( OWNER_PHONE + i );
                    if( GetaddrNotFound() == 0 )
                    {
                        if( GetPageExpiredPage() )
                        {
                            (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "ATE%d\n", WAR_PAGE_EXPIRED );
                            putsUSBUSART( UsbWriteBuffer );
                            warning( WAR_PAGE_EXPIRED );
                        }
                        if( GetPageCorruptStatus() )
                        {
                            (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "ATE%d\n", ERR_WRITE );
                            putsUSBUSART( UsbWriteBuffer );
                            error( ERR_WRITE );
                        }
                        if( GetPageWriteError() )
                        {
                            (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "ATE%d\n", ERR_WRITE );
                            putsUSBUSART( UsbWriteBuffer );
                            error( ERR_WRITE );
                        }
                        conf_data_ptr->OwnerPhone[2*i + 0] = (char)(( EERead & 0xFF00 ) >> 8);
                        if( conf_data_ptr->OwnerPhone[2*i + 0] == '\0' )
                        {
                            break;
                        }
                        conf_data_ptr->OwnerPhone[2*i + 1] = (char)(EERead & 0x00FF);
                        if( conf_data_ptr->OwnerPhone[2*i + 1] == '\0' )
                        {
                            break;
                        }
                    }
                    else
                    {
                        SetaddrNotFound( 0 );
                    }
                    conf_data_ptr->OwnerPhone[OWNER_PHONE_LENGTH*2] = '\0';
                }
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "ATW(%d,%s)\n", EEaddress, conf_data_ptr->OwnerPhone );
                putsUSBUSART( UsbWriteBuffer );
            }
            else if( EEaddress == OWNER_NAME )
            {
                /* Prepare EEPROM buffer */
                memset(EEstring, 0, 31);
                /* Read data from read buffer and prepare them to write. */
                while( UsbReadBuffer[++i] != ')' )
                {
                    EEstring[j++] = UsbReadBuffer[i];
                    if( j >= OWNER_NAME_LENGTH*2 )
                    {
                        break;
                    }
                }
                EEstring[j] = '\0';

                /* Write data to program memory. */
                for( j = 0; j < OWNER_NAME_LENGTH; j++ )
                {
                    DataEEWrite(((unsigned int)EEstring[2*j] << 8) + (unsigned int)EEstring[2*j+1], OWNER_NAME + j);
                }

                /* Read data from program memory to confirm that they are not corrupted. */
                for( i = 0; i < OWNER_NAME_LENGTH; i++ )
                {
                    EERead = DataEERead( OWNER_NAME + i );
                    if( GetaddrNotFound() == 0 )
                    {
                        if( GetPageExpiredPage() )
                        {
                            (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "ATE%d\n", WAR_PAGE_EXPIRED );
                            putsUSBUSART( UsbWriteBuffer );
                            warning( WAR_PAGE_EXPIRED );
                        }
                        if( GetPageCorruptStatus() )
                        {
                            (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "ATE%d\n", ERR_WRITE );
                            putsUSBUSART( UsbWriteBuffer );
                            error( ERR_WRITE );
                        }
                        if(GetPageWriteError())
                        {
                            (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "ATE%d\n", ERR_WRITE );
                            putsUSBUSART( UsbWriteBuffer );
                            error( ERR_WRITE );
                        }
                        conf_data_ptr->OwnerName[2*i + 0] = (char)((EERead & 0xFF00) >> 8);
                        if( conf_data_ptr->OwnerName[2*i + 0] == '\0' )
                        {
                            break;
                        }
                        conf_data_ptr->OwnerName[2*i + 1] = (char)EERead & 0x00FF;
                        if( conf_data_ptr->OwnerName[2*i + 1] == '\0' )
                        {
                            break;
                        }
                    }
                    else
                    {
                        SetaddrNotFound(0);
                    }
                    conf_data_ptr->OwnerName[OWNER_NAME_LENGTH*2] = '\0';
                }
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "ATW(%d,%s)\n", EEaddress, conf_data_ptr->OwnerName );
                //(void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "Owner name: %s)\n", conf_data_ptr->OwnerName );
                putsUSBUSART( UsbWriteBuffer );
            }
            else if( EEaddress <= EE_LARGEST_ADDRESS )
            {
                j = 0;
                /* i is set to comma, so it has to be incremented before read.
                 * Test if number is negative. */
                if( UsbReadBuffer[++i] == '-' )
                {
                    negative = 1;
                    i++;
                }
                /* Max 3 digit numbers unless it is serial number. */
                if( EEaddress == SERIAL_NUMBER )
                {
                    while( j <= 4 )
                    {
                        if( UsbReadBuffer[i+j] <= '9' && UsbReadBuffer[i+j] >= '0' )
                        {
                            EEvalue = EEvalue*10;
                            EEvalue = EEvalue + (int)(UsbReadBuffer[i+j] - '0');
                        }
                        else break;
                        j++;
                    }
                }
                /* It is not serial number. */
                else
                {
                    while( j <= 3 )
                    {
                        if( UsbReadBuffer[i+j] <= '9' && UsbReadBuffer[i+j] >= '0' )
                        {
                            EEvalue = EEvalue*10;
                            EEvalue = EEvalue + (int)(UsbReadBuffer[i+j] - '0');
                        }
                        else break;
                        j++;
                    }
                }
                if( negative )
                {
                    EEvalue = -EEvalue;
                }

                /* Write data to program memory. */
                DataEEWrite( (unsigned int)EEvalue, EEaddress );

                /* Read data from program memory to confirm that they are not corrupted. */
                EERead = DataEERead( EEaddress );
                if( GetaddrNotFound() == 0 )
                {
                        if( GetPageExpiredPage() )
                        {
                            (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "ATE%d\n", WAR_PAGE_EXPIRED );
                            putsUSBUSART( UsbWriteBuffer );
                            warning( WAR_PAGE_EXPIRED );
                        }
                        if( GetPageCorruptStatus() )
                        {
                            (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "ATE%d\n", ERR_WRITE );
                            putsUSBUSART( UsbWriteBuffer );
                            error( ERR_WRITE );
                        }
                        if( GetPageWriteError() )
                        {
                            (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "ATE%d\n", ERR_WRITE );
                            putsUSBUSART( UsbWriteBuffer );
                            error( ERR_WRITE );
                        }
                }
                else
                {
                    SetaddrNotFound(0);
                }
                nvm_UpdateConfData( EEaddress, conf_data_ptr );
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "ATW(%d,%d)\n", EEaddress, EERead );
                putsUSBUSART( UsbWriteBuffer );
            }
            else
            {
                (void)ap_sprintf_safe( UsbWriteBuffer, CDC_DATA_IN_EP_SIZE, "ATE%d\n", ERR_INVALID_ADDRESS );
                putsUSBUSART( UsbWriteBuffer );
            }
            break;
        } /* switch( Buffer1Read[2] ) */
    } /* if( ( Buffer1Read[0] == 'A' ) && ( Buffer1Read[1] == 'T' ) ) */
}
