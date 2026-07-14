#ifndef MAIN_H
#define MAIN_H

/*Must add option "-mlarge-arrays" to C compiler command line. */

/*****************************************************************************/
/*                                 DEFINES                                   */
/*****************************************************************************/
//#define PRESSURE_CAN_BE_NEGATIVE
//#define SERVO_CONTROL
/** \desc Major hardware version. */
#define MAJOR_HARDWARE                      2
/** \desc Minor hardware version. */
#define MINOR_HARDWARE                      2

#define MAJOR_SOFTWARE                      1
#define MINOR_SOFTWARE                      2

/** \desc Microcontroler frequency. */
#define F_OSC                               32000000
/** \desc Peripheral frequency */
#define FCY                                 F_OSC/2

/** \brief Total number of buffers */
#define NUMBER_OF_BUFFERS                   260
/** \brief Number of buffers written in one batch. */
#define NUMBER_OF_BUFFERS_WRITTEN           20
/** \brief Number of buffer sets. */
#define NUMBER_OF_BUFFER_SETS               NUMBER_OF_BUFFERS/NUMBER_OF_BUFFERS_WRITTEN
/** \brief Multiplier for determing number of buffers less than total number
 * of buffers written at the start of data writing. */
#define OMIT_BUFFER_MULTIPLIER              5
/** \brief Length of one buffer. */
#define SIZE_OF_SD_BUFFER                   100
/** \desc Size of uart transmit buffer. */
#define SEND_BUFFER_SIZE                    100
/** \desc Size of error buffer. */
#define BUFFER_ERROR_SIZE                   100

/** \desc Size of UART1 read buffer. */
#define UART1_READ_BUFFER_SIZE              50

/** \desc Pi, 10 places after decimal. */
#define M_PI                                3.1415926536f
/** \desc Gravitational acceleration. */
#define G_CONST                             9.81f
/** \desc Mach speed. */
#define V_MACH                              330
/** \desc Average pressure at sea level. */
#define P_SEA_LEVEL                         101325
/** \desc Coefficient for calculating altitude from pressure */
#define PRESSURE_COEFF_1                    44330.77f
/** \desc Coefficient for calculating altitude from pressure */
#define PRESSURE_COEFF_2                    0.1902632f

// Kalman filter coefficients
/** \desc Kalman filter coefficient used when rocket ascending. */
#define KALMAN_Q1                           0.4f
/** \desc Kalman filter coefficient used when rocket is descending. */
#define KALMAN_Q2                           0.1f
/** \desc Kalman filter constant coefficient. */
#define KALMAN_R                            207

/** \desc Delay for sensing if rocket starts descending [x10 ms]. */
#define PEAK_ALTITUDE_SENSE_DELAY           100
/** \desc Delay for sensing if rocket starts descending [x10 ms]. */
#define DROGUE_PARA_FAIL_AVERAGE_WEIGHT     0.97f

/* Main parachute trigger counter. */
#define DROGUE_PARACHUTE_COUNTER            10
/* Drogue parachute failure trigger counter. */
#define PARACHUTE_FAILURE_SENSE_COUNTER     100

/** \desc Threshold above which fuse is detected. */
#define FUSE_SENSE_THRESHOLD                450
/** \desc Threshold below which velocity safety is turned off - Arecorder fires fuse when rocket starts descending,
 * it does not wait until rocket velocity starts decreasing. */
#define SAFETY_TRIGGER_HEIGHT               200

/** \desc Function to do debug. */
#define DEBUG                               uart_t
/** \desc Time of short beep [ms]. */
#define SHORT_BEEP                          100
/** \desc Time of long beep [ms]. */
#define LONG_BEEP                           500

//list of error codes
/** \desc The battery is low. */
#define ERR_LOW_BATTERY                     1
/** \desc Number of files in has reached maximum. */
#define ERR_FILE_NUMBER_OVERFLOW            2
/** \desc Write to internal program data error. */
#define ERR_WRITE                           3
/** \desc Invalid address sent to save data into internal program data. */
#define ERR_SENSOR_FAILURE                  5
/** \desc Invalid address sent to save data into internal program data. */
#define ERR_INVALID_ADDRESS                 6

/** \desc Page in internal program data has reach maximum number of writes. */
#define WAR_PAGE_EXPIRED                    4

/** \desc Length of owner phone number field (in words). */
#define OWNER_PHONE_LENGTH                  10
/** \desc Length of owner name field (in words). */
#define OWNER_NAME_LENGTH                   15


#define A_0_G_CALIBRATION                   1
#define Y_0_G_CALIBRATION                   2
#define Z_0_G_CALIBRATION                   3
#define HA_0_G_CALIBRATION                  4
#define A_1_G_CALIBRATION                   5
#define HA_1_G_CALIBRATION                  6
#define TEMP1_OFFSET                        7
#define MAIN_PARA_H1                        8
#define MAIN_PARA_H2                        9
#define MAIN_PARA_H3                        10
#define MAIN_PARA_H4                        11
#define SECOND_ENGINE_DELAY_TRIGGER1        12
#define SECOND_ENGINE_DELAY_TRIGGER2        13
#define SECOND_ENGINE_DELAY_TRIGGER3        14
#define SECOND_ENGINE_DELAY_TRIGGER4        15
#define LAUNCHPAD_HEIGHT1                   16
#define LAUNCHPAD_HEIGHT2                   17
#define LAUNCHPAD_HEIGHT3                   18
#define LAUNCHPAD_HEIGHT4                   19
#define DROGUE_PARACHUTE_FAILURE_TRESHOLD1  20
#define DROGUE_PARACHUTE_FAILURE_TRESHOLD2  21
#define DROGUE_PARACHUTE_FAILURE_TRESHOLD3  22
#define DROGUE_PARACHUTE_FAILURE_TRESHOLD4  23
#define SERIAL_NUMBER                       28
#define EE_LARGEST_ADDRESS                  SERIAL_NUMBER
#define OWNER_PHONE                         29 // 10 words = 20 characters
#define OWNER_NAME                          OWNER_PHONE + OWNER_PHONE_LENGTH // 15 words = 30 characters

#define MAIN_PARA_H1_DEFAULT                200
#define MAIN_PARA_H2_DEFAULT                150
#define MAIN_PARA_H3_DEFAULT                100
#define MAIN_PARA_H4_DEFAULT                50
#define SECOND_ENGINE_DELAY_TRIGGER_DEFAULT 0
#define LAUNCHPAD_HEIGHT_DEFAULT            1
#define DROGUE_PARA_FAIL_TRESHOLD_DEFAULT   50
/*****************************************************************************/
/*                                 TYPEDEFS                                  */
/*****************************************************************************/
/** \desc State of the Arecorder. */
typedef enum
{
    /** \desc Arecorder is initializing. */
    AWAITING_FOR_ARECORDER_READY,
    /** \desc Arecorder is ready and waiting for launch. */
    AWAITING_FOR_LAUNCH,
    /** \desc First engine fired and active. */
    FIRST_ENGINE_ACTIVE,
    /** \desc First engine burnout, waiting for second engine to fire. */
    WAITING_FOR_SECOND_ENGINE_TIME_TRIGGER,
    /** \desc Second engine fired, waiting for second engine to start. */
    AWAITING_FOR_SECOND_ENGINE_START,
    /** \desc Second engine fired and active. */
    SECOND_ENGINE_ACTIVE,
    /** \desc Second engine burnout, rocket ascending to peak altitude. */
    AWAITING_FOR_PEAK_ALTITUDE,
    /** \desc First parachute deployed, rocket descending. */
    AWAITING_FOR_SECOND_PARACHUTE,
    /** \desc Second parachute deployed, rocket descending, waiting for landing. */
    AWAITING_FOR_LANDING,
    /** \desc Rocket landed, wait 60 seconds before stopping writing data. */
    ROCKET_HAS_LANDED,
    /** \desc Writing adta stopped, wait for buffer to clear and write summary data. */
    STOP_WRITING_DATA,
    /** \desc Buzzer active. */
    ACTIVATE_BUZZER
} ap_ArecorderState_t;

/** \desc Enum describint states of fuse handling. */
typedef enum
{
    /** \desc Nothing to do with fuse. */
    FUSE_IDLE,
    /** \desc Fire fuse to deploy first parachute. */
    FUSE_PARA1,
    /** \desc Fire fuse to deploy second parachute. */
    FUSE_PARA2,
    /** \desc Fire fuse to fire second engine. */
    FUSE_STG2,
    /** \desc Stop firing fuse. */
    FUSE_TURN_OFF
} ap_Fuse_t;

/** \desc Structure to hold configuration data. */
typedef struct
{
    /** \desc Number of log-g accelerometer divs per one g. */
    int A_1_g;
    /** \desc Number of high-g accelerometer divs per one g. */
    int H_1_g;
    /** \desc Number of configuration selected from one of four programmed. */
    unsigned int conf_select;
    /** \desc Low-g accelerometer zero g indication (rocket axis). */
    int A_0_g;
    /** \desc High-g accelerometer zero g indication (rocket axis). */
    int H_0_g;
    /** \desc Low-g accelerometer zero g indication (Y axis). */
    int Y_0_g;
    /** \desc Low-g accelerometer zero g indication (Z axis). */
    int Z_0_g;
    /** \desc Flag set when high-g accelerometer is present. */
    unsigned int HaccPresent;
    /** \desc Temperature correction offset. */
    int TemperatureOffset1;
    /** \desc Altitude at which main parachute should be triggered. */
    unsigned int MainParachuteTriggerAltitude;
    /** \desc Delay between first engine burnout and second engine firing. */
    unsigned int SecondEngineDelayTrigger;
    /** \desc Height of launchpad. */
    unsigned int LaunchpadHeight;
    /** \desc Drogue parachute failure detection algorithm rocket descend treshold. */
    unsigned int DrogueParaFailTreshold;
    /** \desc Unique Arecorder serial number. */
    unsigned int SerialNumber;
    /** \desc Owners phone number. */
    char OwnerPhone[OWNER_PHONE_LENGTH*2+1];
    /** \desc Owners name. */
    char OwnerName[OWNER_NAME_LENGTH*2+1];
} ap_ConfigurationData_t;

/** \desc Structure holding information about Kalman filter calculations. */
typedef struct
{
    /** \desc Raw pressure data read from pressure sensor [Pa]. */
    float raw;
    /** \desc Pressure after current prediction [Pa]. */
    float priori;
    /** \desc Pressure after current Kalman calculations [Pa]. */
    float post;
    /** \desc Pressure after last Kalman calculations [Pa]. */
    float postLast;
    /** \desc Speed of changes of calculated pressure [100*Pa/s]. */
    float derivativePost;
    /** \desc Error Covariance, used to calculate gain in current Kalman prediction. */
    float errorCovPriori;
    /** \desc Error Covariance, calculated in update, used to calculate errorCovPriori in next prediction. */
    float errorCovPost;
    /** \desc Kalman update gain. */
    float gain;
} ap_KalmanData_t;

/** \desc Saving time events happen. */
typedef struct
{
    /** \desc Rocket launch. */
    struct
    {
        unsigned int Sec;
        unsigned int dSec;
    } launch;
    /** \desc First engine burnout. */
    struct
    {
        unsigned int Sec;
        unsigned int dSec;
    } burnout1;
    /** \desc Secong engine start. */
    struct
    {
        unsigned int Sec;
        unsigned int dSec;
    } stg2Active;
    /** \desc Second engine burnout. */
    struct
    {
        unsigned int Sec;
        unsigned int dSec;
    } burnout2;
    /** \desc Peak altitude reached. */
    struct
    {
        unsigned int Sec;
        unsigned int dSec;
    } apogee;
    /** \desc Minimum velocity reached. */
    struct
    {
        unsigned int Sec;
        unsigned int dSec;
    } minV;
    /** \desc Landing time. */
    struct
    {
        unsigned int Sec;
        unsigned int dSec;
    } land;
    /** \desc Drogue parachute fuse fire. */
    struct
    {
        unsigned int Sec;
        unsigned int dSec;
    } para1;
    /** \desc Main parachute fuse fire. */
    struct
    {
        unsigned int Sec;
        unsigned int dSec;
    } para2;
    /** \desc Stage 2 fuse fire. */
    struct
    {
        unsigned int Sec;
        unsigned int dSec;
    } stg2Fire;
} ap_Event_t;

/** \desc Saving time events happen. */
typedef struct
{
    /** \desc Rocket angle at start [deg]. */
    float RocketAngleStart;
    /** \desc Pressure at earth ground [Pa]. */
    float PressureGround;
    /** \desc Minimum pressure recorded at flight (peak altitude) [Pa]. */
    float PressureMinimum;
    /** \desc Maximum velocity during the flight [m/s]. */
    float VAxisMax;
    /** \desc Maximum altitude [m]. */
    float AltitudeMax;
    /** \desc Height above mean sea level [m]. Used to calculate relative altitude [m]. */
    float HeightAMSL;
    /** \desc Velocity at the moment of leaving launchpad. */
    float LaunchpadVelocity;
    /** \desc Velocity at the moment of burnout of first engine. */
    float Engine1Burnout_VAxis;
    /** \desc Altitude at the moment of burnout of first engine. */
    float Engine1Burnout_Altitude;
    /** \desc Pressure at the moment of burnout of first engine. */
    float Engine1Burnout_Pressure;
    /** \desc Rocket angle at the moment of burnout of first engine. */
    float Engine1Burnout_RocketAngle;
    /** \desc Velocity at the moment of burnout of second engine. */
    float Engine2Burnout_VAxis;
    /** \desc Altitude at the moment of burnout of second engine. */
    float Engine2Burnout_Altitude;
    /** \desc Pressure at the moment of burnout of second engine. */
    float Engine2Burnout_Pressure;
    /** \desc Rocket angle at the moment of burnout of second engine. */
    float Engine2Burnout_RocketAngle;
} ap_summaryData_t;
#endif
