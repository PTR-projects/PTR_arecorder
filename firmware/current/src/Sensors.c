/*****************************************************************************/
/*                                 INCLUDES                                  */
/*****************************************************************************/
#include <math.h>
#include <APlib.h>
#include <Sensors.h>
#include <dbg.h>

/*****************************************************************************/
/*                             GLOBAL VARIABLES                              */
/*****************************************************************************/
extern int ap_TimeoutI2C;
extern char ap_BufferError[BUFFER_ERROR_SIZE];

volatile static int HACC_TMP = 0;
/*****************************************************************************/
/*                                FUNCTIONS                                  */
/*****************************************************************************/

/******************************************************************************
 * \brief Function initializes SPI.
 *
 * \input None.
 *
 * \output None.
 * ****************************************************************************/
inline void spi_init(void) {
    /* Remapable pin configuration. */
    _SDI2R = RP_I_SENSE_SPI_MISO; // MISO <=> RP5
    RP_O_SENSE_SPI_MOSI = 10; // RP7  <=> MOSI
    RP_O_SENSE_SPI_SCK = 11; // RP6  <=> SCK

    /* I/O configuration. */
    TRIS_ACC_CS = 0; // ACC SPI CS = output
    ACC_CS = 1; // ACC SPI CS = 1
    TRIS_HACC_CS = 0; // HACC SPI CS = output
    HACC_CS = 1; // HACC SPI CS = 1

    /* SPI driver configuration. */
    SPI2CON1bits.MODE16 = 0; /* 1 = One word (16-bits) wide communication. */
    SPI2CON1bits.CKP = 0; /* 1 = clock Idle state is high. */
    SPI2CON1bits.CKE = 1; /* 1 = output data changes on transition from active clock to idle clock. */
    SPI2CON1bits.MSTEN = 1; /* 1 = master mode. */
    SPI2CON1bits.SMP = 0; /* 1 = data input sampled at end of data output time. */
    SPI2CON1bits.SPRE = 6; /* Secondary prescale, 6 - 2:1. */
    SPI2CON1bits.PPRE = 2; /* Primary prescale, 2 - 4:1. */
    SPI2STATbits.SPIROV = 0; /* Clear receive overflow. */
    SPI2STATbits.SPIEN = 1; /* Enable SPI1. */
}

/******************************************************************************
 * \brief Function transmits one byte to SPI.
 *
 * \input int aT_byte
 *      Byte to be transmitted.
 *
 * \output
 *      Byte received from slave during transmission.
 * ****************************************************************************/
inline int spi_transmit(int aT_byte) {
    SPI2BUF = aT_byte;
    while (!SPI2STATbits.SPIRBF);
    return SPI2BUF;
}

/******************************************************************************
 * \brief Function initializes I2C.
 *
 * \input None.
 *
 * \output None.
 * ****************************************************************************/
inline void i2c2_init(void) {
    /* 40@16MHz = 200 kHz */
    I2C2BRG = 80;
    I2C2CONbits.I2CEN = 1;
}

/******************************************************************************
 * \brief Function reads data from I2C bus.
 *
 * \input char *aR_buffer
 *      Pointer to buffer to write received data.
 *
 * \input int aBytesToRead
 *      Number of bytes to read.
 *
 * \output
 *      Return value:
 *          0 - OK,
 *          1 - Timeout.
 * ****************************************************************************/
int i2c2_read(char *aR_buffer, int aBytesToRead) {
    int i;
    I2C2CONbits.ACKDT = 0;
    for (i = 0; i < (aBytesToRead - 1); i++) {
        I2C2CONbits.RCEN = 1;
        ap_TimeoutI2C = 2;
        while (I2C2CONbits.RCEN) {
            if (ap_TimeoutI2C == 0) {
                return 1;
            }
        }
        aR_buffer[i] = I2C2RCV;
        I2C2CONbits.ACKEN = 1;
        while (I2C2CONbits.ACKEN);
    }

    I2C2CONbits.RCEN = 1;
    ap_TimeoutI2C = 2;
    while (I2C2CONbits.RCEN) {
        if (ap_TimeoutI2C == 0) {
            return 1;
        }
    }

    aR_buffer[i] = I2C2RCV;
    I2C2CONbits.ACKDT = 1;
    I2C2CONbits.ACKEN = 1;
    while (I2C2CONbits.ACKEN);
    return 0;
}

/******************************************************************************
 * \brief Function sends one byte to I2C bus.
 *
 * \input char aT_byte
 *      Byte to send.
 *
 * \output
 *      Return value:
 *          0 - OK,
 *          1 - NACK received.
 * ****************************************************************************/
int i2c2_transmit(char aT_byte) {
    I2C2TRN = aT_byte;
    while (I2C2STATbits.TRSTAT);

    if (I2C2STATbits.ACKSTAT) {
        /* NACK received. */
        I2C2CONbits.PEN = 1;
        while (I2C2CONbits.PEN);
        return 1;
    }
    return 0;
}

/******************************************************************************
 * \brief Function sends one two-byte command (with implicit address) to I2C bus.
 *
 * \input int aCommand1
 *      First byte of command.
 *
 * \input int aCommand2
 *      Second byte of command.
 *
 * \output
 *      Return value:
 *          0 - OK,
 *          1 - NACK received.
 * ****************************************************************************/
int i2c_command(int aCommand1, int aCommand2) {
    /* Send I2C start. */
    I2C2CONbits.SEN = 1;
    while (I2C2CONbits.SEN);

    if (i2c2_transmit(PRESSURE_I2C_ADDRESS | I2C_WRITE)) {
        return 1;
    }
    if (i2c2_transmit(aCommand1)) {
        return 1;
    }
    if (i2c2_transmit(aCommand2)) {
        return 1;
    }
    /* Send I2C stop. */
    I2C2CONbits.PEN = 1;
    while (I2C2CONbits.PEN);
    I2C2STAT = 0;
    return 0;
}

/******************************************************************************
 * \brief Function reads larger block of data from I2C bus.
 *
 * \input int aCommand
 *      Command byte to send before read.
 *
 * \input char *aR_buffer
 *      Pointer to buffer to save received data.
 *
 * \input int aBytesToRead
 *      Number of bytes to read.
 *
 * \output
 *      Return value:
 *          0 - OK,
 *          1 - NACK received.
 * ****************************************************************************/
int i2c_buffer_read(int aCommand, char *aR_buffer, int aBytesToRead) {
    int rv;
    /* Send I2C start. */
    I2C2CONbits.SEN = 1;
    while (I2C2CONbits.SEN);

    /* Send address. */
    if (i2c2_transmit(PRESSURE_I2C_ADDRESS | I2C_WRITE)) {
        return 1;
    }

    /* Send command. */
    if (i2c2_transmit(aCommand)) {
        return 1;
    }

    /* Send restart (change of data direction). */
    I2C2CONbits.RSEN = 1;
    while (I2C2CONbits.RSEN);

    /* Send address. */
    if (i2c2_transmit(PRESSURE_I2C_ADDRESS | I2C_READ)) {
        return 1;
    }
    rv = i2c2_read(aR_buffer, aBytesToRead);
    check_debug(rv == 0, "I2C read error");

    /* Send I2C stop. */
    I2C2CONbits.PEN = 1;
    while (I2C2CONbits.PEN);
    I2C2STAT = 0;
    return 0;

error:
    return 1;
}

/******************************************************************************
 * \brief Function initializes and configures low-g accelerometer.
 *
 * \input None.
 *
 * \output None.
 * ****************************************************************************/
void acc24g_config(void) {
    /* Configure SPI for low-g accelerometer. */
    SPI2CON1bits.CKP = 1;
    SPI2CON1bits.CKE = 0;

    /* Select low-g accelerometer. */
    ACC_CS = 0;
    asm("nop");
    spi_transmit(LIS_CTRL_REG1 + WRITE_INC_ACC);
    asm("nop");
    spi_transmit(LIS_CTRL_REG1_normalMode | LIS_CTRL_REG1_ODR100Hz | LIS_CTRL_REG1_ZEN | LIS_CTRL_REG1_YEN | LIS_CTRL_REG1_XEN);   //0b00101111
    asm("nop");
    spi_transmit(0x00); //REG2
    asm("nop");
    spi_transmit(0x00);   //REG3
    asm("nop");
    spi_transmit(LIS_CTRL_REG4_BDU | LIS_CTRL_REG4_BLE | LIS_CTRL_REG4_FS1 | LIS_CTRL_REG4_FS0);   //0b11110000
    asm("nop");
    /* Deselect low-g accelerometer. */
    ACC_CS = 1;
}

/******************************************************************************
 * \brief Function Reads data from low-g accelerometer.
 *
 * \input apAcceleration_t *acc
 *      Pointer to structure containing accelerometer data.
 *
 * \output None.
 * ****************************************************************************/
void read_acc24(apAcceleration_t *acc) {
    /* Configure SPI for low-g accelerometer. */
    SPI2CON1bits.CKP = 1;
    SPI2CON1bits.CKE = 0;

    /* Select low-g accelerometer. */
    ACC_CS = 0;
    asm("nop");
    spi_transmit(LIS_OUT_X_L + READ_INC_ACC);
    asm("nop");
    acc->x = ((spi_transmit(0) << 8) + spi_transmit(0));
    asm("nop");
    acc->y = ((spi_transmit(0) << 8) + spi_transmit(0));
    asm("nop");
    acc->z = ((spi_transmit(0) << 8) + spi_transmit(0));
    asm("nop");
    /* Deselect low-g accelerometer. */
    ACC_CS = 1;
}

uint16_t acc80g_RW(uint16_t data) {
    uint16_t res_H = 0;
    uint16_t res_L = 0;

    /* Configure SPI for high-g accelerometer. */
    SPI2CON1bits.CKP = 0;
    SPI2CON1bits.CKE = 0;

    HACC_CS = 0;
    res_H = spi_transmit(data >> 8);
    res_L = spi_transmit(data & 0x00FF);
    HACC_CS = 1;

    return (res_H << 8) +res_L;
}

uint8_t acc80g_parity(uint16_t input) {
    uint8_t res = 1;
    uint8_t i = 0;

    for (i = 0; i < 16; i++) {
        if (input & 0x0001)
            res ^= 0x01;
        input >>= 1;
    }
    return (res % 2);
}

uint8_t acc80g_readReg(uint8_t reg_address) {
    uint16_t cmd_readReg = 0x0000;
    uint8_t reg_val = 0;

    reg_address &= 0x1F;
    cmd_readReg |= reg_address << 8; //insert address to command
    cmd_readReg |= acc80g_parity(cmd_readReg) << 15; //insert parity bit

    acc80g_RW(cmd_readReg);
    reg_val = acc80g_RW(0x0000);

    return reg_val;
}

uint8_t acc80g_writeReg(uint8_t reg_address, uint8_t val) {
    uint16_t cmd_readReg = 0x0000;
    uint8_t reg_val = 0;

    reg_address &= 0x1F;
    cmd_readReg |= reg_address << 8; //insert address to command
    cmd_readReg |= 1 << 14;
    cmd_readReg |= val & 0x00FF;
    cmd_readReg |= acc80g_parity(cmd_readReg) << 15; //insert parity bit

    acc80g_RW(cmd_readReg);
    //reg_val = acc80g_RW(0x0000);

    //if (((uint8_t) reg_val) == (val))
        return 0;
    //else
    //    return 1;
}

uint16_t acc80g_getXraw() {
    uint16_t cmd_readReg = 0x0000;

    cmd_readReg |= 0 << 14; //Y-axis Acceleration Data Response
    cmd_readReg |= 1 << 13; //Acceleration Data Request
    cmd_readReg |= 1 << 12; //Transferred Accel Data is Raw Data
    cmd_readReg |= 1 << 2; //Unsigned Data Enabled
    cmd_readReg |= 0 << 1; //Disabled / PCM Output Enabled
    cmd_readReg |= acc80g_parity(cmd_readReg) << 0; //insert parity bit

	
	int16_t res = acc80g_RW(cmd_readReg) & 0x03FF;		//Odczytuje próbke samplowaną podczas poprzedniego cyklu
	res -= 512;	// 0g = 512 LSB
	res <<= 6;	//shift 6 to left (increase calibration accuracy)

    return res;
}

uint16_t acc80g_getYraw() {
    uint16_t cmd_readReg = 0x0000;

    cmd_readReg |= 1 << 14; //Y-axis Acceleration Data Response
    cmd_readReg |= 1 << 13; //Acceleration Data Request
    cmd_readReg |= 1 << 12; //Transferred Accel Data is Raw Data
    cmd_readReg |= 1 << 2; //Unsigned Data Enabled
    cmd_readReg |= 0 << 1; //Disabled / PCM Output Enabled
    cmd_readReg |= acc80g_parity(cmd_readReg) << 0; //insert parity bit

    int16_t res = acc80g_RW(cmd_readReg) & 0x03FF;		//Odczytuje próbke samplowaną podczas poprzedniego cyklu
	res -= 512;	// 0g = 512 LSB
	res <<= 6;	//shift 6 to left (increase calibration accuracy)

    return res;
}

uint8_t acc80g_getStatus() {
    return acc80g_readReg(0x14);
}

void acc80g_reset() {
    acc80g_writeReg(0x0A, 0x00);
    acc80g_writeReg(0x0A, 0xC0);
    acc80g_writeReg(0x0A, 0x40);
}

/******************************************************************************
 * \brief Function initializes and configures high-g accelerometer.
 *
 * \input None.
 *
 * \output
 *      Return value from accelerometer. Based on this a check can be done if
 *      accelerometer is connected and working.
 * ****************************************************************************/
int acc80g_config(void) {
    /* Number of iteration in which Arecorder is trying to connect to
     * accelerometer. */
    uint8_t timeout = 10;
    /* Return value from accelerometer. */
    int hacc_present = 0;

    /* Configure SPI for high-g accelerometer. */
    SPI2CON1bits.CKP = 0;
    SPI2CON1bits.CKE = 0;

    delay_ms(10);
    acc80g_reset();
    delay_ms(10);
	
	acc80g_getStatus();
	acc80g_getStatus();

    do {
        hacc_present = acc80g_readReg(0x08);	//MMA_REG_PART_NUMBER
		delay_ms(1);
        timeout--;
    } while ((hacc_present != 0x1B) && (timeout));

    acc80g_writeReg(0x0C, 0x08); //DEVCFG_X Low pass filter 50 Hz on X axis
    acc80g_writeReg(0x0D, 0x08); //DEVCFG_Y Low pass filter 50 Hz on Y axis

    acc80g_writeReg(0x0B, 0x30); //DEVCFG Raw, unsigned data, end of initialization

    return hacc_present == 0x1B;
}

/******************************************************************************
 * \brief Function Reads data from high-g accelerometer.
 *
 * \input None.
 *
 * \output Measured acceleration.
 * ****************************************************************************/
int read_acc80(void) {
    /* Number of iteration in which Arecorder is trying read data from
     * accelerometer. */
    int repeat = 0;
    /* Temporary register. */
    int status;
    /* Measured acceleration. */
    int hacc;

    hacc = acc80g_getYraw();
    /* Configure SPI for high-g accelerometer. */

    //  TODO sprawdzenie poprawności danych?

    return hacc;
}

/******************************************************************************
 * \brief Function initializes and configures pressure sensor.
 *
 * \input None.
 *
 * \output None.
 * ****************************************************************************/
void init_pressure(void) {
    i2c_command(0x2C, 0b10000000);
    i2c_command(0x26, 0b00001010);
}

/******************************************************************************
 * \brief Function Reads data from pressure sensor.
 *
 * \input None.
 *
 * \output
 *      1 - error.
 *      any other value - measured pressure.
 * ****************************************************************************/
float read_pressure(void) {
    /* Return value from I2C bus. */
    int rv;
    /* Buffer for reading data from I2C bus. */
    static unsigned int PressureRaw[3];
    /* Buffer for reading data from I2C bus. */
    static char I2cReadRaw[3];
    /* Returned pressure. */
    float CalculatedPressure;

    rv = i2c_buffer_read(0x01, I2cReadRaw, 3);
    check(rv == 0, "I2C read error.");
    rv = i2c_command(0x26, 0b00001010);
    check(rv == 0, "I2C read error.");
    PressureRaw[0] = (int) I2cReadRaw[0] & 0x00ff;
    PressureRaw[1] = (int) I2cReadRaw[1] & 0x00ff;
    PressureRaw[2] = (int) I2cReadRaw[2] & 0x00ff;
#ifdef PRESSURE_CAN_BE_NEGATIVE
    CalculatedPressure = (long int) (PressureRaw[0] & 0x7F)*1024 + (long int) (PressureRaw[1]*4) + (long int) (PressureRaw[2] >> 6);
    if ((PressureRaw[0] >> 7) == 1) {
        CalculatedPressure = CalculatedPressure | ((long) 0xFF << 24) | ((long) 0xFE << 16);
    }
    return CalculatedPressure;
#else
    return (float) (PressureRaw[0])*1024 + (PressureRaw[1]*4) + (PressureRaw[2] >> 6);
#endif
error:
    return 1;
}

/******************************************************************************
 * \brief Function calculates altitude from pressure.
 *
 * \input float aPressure
 *      Pressure from which altitude is calculated.
 *
 * \output
 *      Calculated altitude.
 * ****************************************************************************/
float p2altitude(float aPressure) {
    return PRESSURE_COEFF_1 * (1 - powf((aPressure / P_SEA_LEVEL), PRESSURE_COEFF_2));
}

/******************************************************************************
 * \brief Function calculates temperature from voltage measurement.
 *
 * \input unsigned int aMeasurement
 *      Raw voltage measurement.
 *
 * \input int aOffset
 *      Temperature offset.
 *
 * \output
 *      Calculated altitude.
 * ****************************************************************************/
inline float temp_calculate(unsigned int aMeasurement, int aOffset) {
    return ( TEMP_SENSOR_CONSTANT -
            (TEMP_SUPPLY_VOLTAGE_MV / TEMP_NO_OF_ADC_DIVS * aMeasurement)) / TEMP_MV_PER_DEGREE_CELCIUS
            - aOffset;
}
