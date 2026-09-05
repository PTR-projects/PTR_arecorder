#ifndef SENSORS_H
#define SENSORS_H

/*****************************************************************************/
/*                                 DEFINES                                   */
/*****************************************************************************/
#define MMA6519_STATUS_OK               0x5E00

#define READ_INC_ACC                    0xC0
#define WRITE_INC_ACC                   0x40
#define HACC_WRITE_BIT                  0x40
#define HACC_ODD_PARITY                 0x80
#define PRESSURE_I2C_ADDRESS            0xC0

#define I2C_WRITE                       0x00
#define I2C_READ                        0x01

#define HACC_READ_ERROR                 0xFFFF
#define HACC_MAX_NUMBER_OF_READ_RETRY   10

#define TEMP_SENSOR_CONSTANT            1832.0
#define TEMP_SUPPLY_VOLTAGE_MV          3300.0f
#define TEMP_NO_OF_ADC_DIVS             1023.0f
#define TEMP_MV_PER_DEGREE_CELCIUS      12.9f

#define LIS_CTRL_REG1        0x20
#define LIS_CTRL_REG2        0x21
#define LIS_CTRL_REG3        0x22
#define LIS_CTRL_REG4        0x23
#define LIS_CTRL_REG5        0x24
#define LIS_HP_FILTER_RESET  0x25
#define LIS_REFERENCE        0x26
#define LIS_STATUS_REG       0x27
#define LIS_OUT_X_L          0x28
#define LIS_OUT_X_H          0x29
#define LIS_OUT_Y_L          0x2A
#define LIS_OUT_Y_H          0x2B
#define LIS_OUT_Z_L          0x2C
#define LIS_OUT_Z_H          0x2D
#define LIS_INT1_CFG         0x30
#define LIS_INT1_SOURCE      0x31
#define LIS_INT1_THS         0x32
#define LIS_INT1_DURATION    0x33
#define LIS_INT2_CFG         0x34
#define LIS_INT2_SOURCE      0x35
#define LIS_INT2_THS         0x36
#define LIS_INT2_DURATION    0x37

// Control register 1
#define LIS_CTRL_REG1_PM2  0x80
#define LIS_CTRL_REG1_PM1  0x40
#define LIS_CTRL_REG1_PM0  0x20
#define LIS_CTRL_REG1_DR1  0x10
#define LIS_CTRL_REG1_DR0  0x08
#define LIS_CTRL_REG1_ZEN  0x04
#define LIS_CTRL_REG1_YEN  0x02
#define LIS_CTRL_REG1_XEN  0x01

#define LIS_CTRL_REG1_ODR50Hz     0x00
#define LIS_CTRL_REG1_ODR100Hz    LIS_CTRL_REG1_DR0
#define LIS_CTRL_REG1_ODR400Hz    LIS_CTRL_REG1_DR1
#define LIS_CTRL_REG1_ODR1000Hz   LIS_CTRL_REG1_DR1 | LIS_CTRL_REG1_DR0

#define LIS_CTRL_REG1_powerDown    0x00,
#define LIS_CTRL_REG1_normalMode   LIS_CTRL_REG1_PM0
#define LIS_CTRL_REG1_lowPower05Hz LIS_CTRL_REG1_PM1
#define LIS_CTRL_REG1_lowPower1Hz  LIS_CTRL_REG1_PM1 | LIS_CTRL_REG1_PM0
#define LIS_CTRL_REG1_lowPower2Hz  LIS_CTRL_REG1_PM2,
#define LIS_CTRL_REG1_lowPower5Hz  LIS_CTRL_REG1_PM2 | LIS_CTRL_REG1_PM0
#define LIS_CTRL_REG1_lowPower10Hz LIS_CTRL_REG1_PM2 | LIS_CTRL_REG1_PM1

// Control register 2
#define LIS_CTRL_REG2_BOOT  0x80
#define LIS_CTRL_REG2_HPM1  0x40
#define LIS_CTRL_REG2_HPM0  0x20
#define LIS_CTRL_REG2_FDS   0x10
#define LIS_CTRL_REG2_HPEN2 0x08
#define LIS_CTRL_REG2_HPEN1 0x04
#define LIS_CTRL_REG2_HPCF1 0x02
#define LIS_CTRL_REG2_HPCF0 0x01

// Control register 3
#define LIS_CTRL_REG3_IHL     0x80
#define LIS_CTRL_REG3_PP_OD   0x40
#define LIS_CTRL_REG3_LIR2    0x20
#define LIS_CTRL_REG3_I2_CFG1 0x10
#define LIS_CTRL_REG3_I2_CFG0 0x08
#define LIS_CTRL_REG3_LIR1    0x04
#define LIS_CTRL_REG3_I1_CFG1 0x02
#define LIS_CTRL_REG3_I1_CFG0 0x01

// Control register 4
#define LIS_CTRL_REG4_BDU    0x80
#define LIS_CTRL_REG4_BLE    0x40
#define LIS_CTRL_REG4_FS1	 0x20
#define LIS_CTRL_REG4_FS0	 0x10
#define LIS_CTRL_REG4_STSIGN 0x08
// 0                         0x04
#define LIS_CTRL_REG4_ST     0x02
#define LIS_CTRL_REG4_SIM    0x01

// Control register 5
// Unused                      7..2
#define LIS_CTRL_REG5_TURNON_1 0x02
#define LIS_CTRL_REG5_TURNON_0 0x01


/*****************************************************************************/
/*                                 TYPEDEFS                                  */
/*****************************************************************************/

/** \desc Structure holding all accelerometer data. */
typedef struct
{
    int x;
    int y;
    int z;
    int ha;
    /* Acceleration along rocket axis in [m/s^2]. */
    float a_axis;
} apAcceleration_t;

/*****************************************************************************/
/*                                FUNCTIONS                                  */
/*****************************************************************************/
inline void spi_init( void );
inline int spi_transmit( int aT_buffer );

inline void i2c2_init( void );
int i2c2_read( char *aR_buffer, int aBytesToRead );
int i2c2_transmit( char aT_buffer );
int i2c_command( int aCommand1, int aCommand2 );
int i2c_buffer_read( int aCommand, char *aR_buffer, int aBytesToRead );

void acc24g_config( void );
void read_acc24( apAcceleration_t *acc );
int acc80g_config( void );
int read_acc80( void );

void init_pressure( void );
float read_pressure( void );
float p2altitude( float aPressure );

inline float temp_calculate( unsigned int aMeasurement, int aOffset );

#endif
