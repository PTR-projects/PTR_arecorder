/*****************************************************************************/
/*                                 INCLUDES                                  */
/*****************************************************************************/
#include <main.h>
#include <APlib.h>
#include <FSIO.h>
#include <SD-SPI.h>
#include <DEE_Emulation_16-bit.h>
#include <Sensors.h>
#include <math.h>
#include <stdarg.h>

#include <libpic30.h>

/*****************************************************************************/
/*                             GLOBAL VARIABLES                              */
/*****************************************************************************/
extern char ap_SendBuffer[];
extern ap_ArecorderState_t ap_ArecorderState;
extern FSFILE *ap_FpMeas;
//extern FSFILE *ap_FpFlightSummary;

/*****************************************************************************/
/*                                 DEFINES                                   */
/*****************************************************************************/
/** \desc Number of milisecons between timer1 ticks. */
#define TIMER1_INT_MS   10
/** \desc Number of milisecons between timer2 ticks. */
#define TIMER2_INT_MS   10
/** \desc Number of milisecons between timer3 ticks. */
#define TIMER3_INT_MS   100

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
inline void timer_init( void )
{
    PR1 = FCY/8000*TIMER1_INT_MS;
    /* Set interrupt priority. */
    IPC0bits.T1IP = 5;
    /* Reset interrupt flag. */
    IFS0bits.T1IF = 0;
    /* Turn on the interrupt. */
    IEC0bits.T1IE = 1;
    /* Set timer clock - FCY/8 = F_OSC/16. */
    _TCKPS = 1;
    /* Turn on timer. */
    _TON = 1;
}

/******************************************************************************
 * \brief Function initializes timer2 for configuriation and calibration.
 *
 * \input None.
 *
 * \output None.
 * ****************************************************************************/
inline void timer2_init( void )
{
    PR2 = FCY/8000*TIMER2_INT_MS;
    /* Set interrupt priority. */
    IPC1bits.T2IP = 6;
    /* Reset interrupt flag. */
    IFS0bits.T2IF = 0;
    /* Turn on the interrupt. */
    IEC0bits.T2IE = 1;
    /* Set timer clock - FCY/8 = F_OSC/16. */
    T2CONbits.TCKPS = 1;
}

/******************************************************************************
 * \brief Function initializes timer3 for sending data during calibration.
 *
 * \input None.
 *
 * \output None.
 * ****************************************************************************/
inline void timer3_init(void)
{
    PR3 = FCY/8000*TIMER3_INT_MS/8;
    /* Set interrupt priority. */
    IPC2bits.T3IP = 4;
    /* Reset interrupt flag. */
    IFS0bits.T3IF = 0;
    /* Turn on the interrupt. */
    IEC0bits.T3IE = 1;
    /* Set timer clock - FCY/64 = F_OSC/128. */
    T3CONbits.TCKPS = 2;
}

/******************************************************************************
 * \brief Function initializes adc.
 *
 * \input None.
 *
 * \output None.
 * ****************************************************************************/
/** \brief Function initializes adc. */
inline void adc_init(void)
{
    /* Data Output Format: Signed Fraction (Q15 format). */
    _FORM = 0;
    /* Internal counter ends sampling and starts conversion. */
    _SSRC = 7;
    /* A/D Sample Auto-Start. */
    _ASAM = 1;
    /* Interrupt every 5 samples. */
    _SMPI = 4;
    /* ADC Clock is derived from Systems Clock. */
    _ADRC = 0;
    /* Enable input scan. */
    _CSCNA = 1;
    AD1CHS = 4;
    /* Sampled pins - AN 0, 1, 2, 3, 6. */
    AD1CSSL = 0x4F; //0b0000000001001111;
    /* ADC Conversion Clock Tad = Tcy*( ADCS + 1 ) */
    AD1CON3bits.ADCS = 64U;
    /* Tsamp + Tconv = 28*Tad + 12*Tad */
    _SAMC = 28;  
    /* ADC interrupt priority. */
    IPC3bits.AD1IP = 6;
    /* Clear the A/D interrupt flag bit. */
    IFS0bits.AD1IF = 0;
    /* Do Not Enable A/D interrupt. */
    IEC0bits.AD1IE = 1;

    /* Enable ADC. */
    _ADON = 1;
}

/******************************************************************************
 * \brief Function waits for desired number of miliseconds doing nothing.
 *
 * \input None
 *
 * \output None.
 * ****************************************************************************/
#define NUMBER_OF_ASSEMBLY_INSTRUCTIONS     8
void delay_ms( int a_ms )
{
    __delay_ms(a_ms);
//    int milisec, i;
//    for( milisec = 0; milisec < a_ms; milisec++ )
//    {
//        for( i = 0; i < ( FCY/( 1000 * NUMBER_OF_ASSEMBLY_INSTRUCTIONS ) ); i++ )
//        {
//            ;
//        }
//    }    
}
#ifdef SERVO_CONTROL
/******************************************************************************
 * \brief Function initializes PWM driver for driving servo.
 *
 * \input unsigned int periodTimeUs
 *      Period of control signal, in [us], max 4 us without prescaler.
 *
 * \input unsigned int controlTimeUs
 *      ON time of control signal,in [us], max 4 us without prescaler.
 * 
 * \output None.
 * ****************************************************************************/
void ServoSet( unsigned int periodTimeUs, unsigned int controlTimeUs )
{
    T5CONbits.TON = 0;
    TMR5 = 0;
    
    OC1R = (unsigned int)(((float)FCY * controlTimeUs)/1000000 - 1);
    PR5 = (unsigned int)(((float)FCY * periodTimeUs)/1000000 - 1);
    OC1TMR = PR5;
    
    OC1CON1 = 0;
    OC1CON2 = 0;
    OC1CON1bits.OCTSEL = 3;
    OC1CON1bits.OCM = 6;
    OC1CON2bits.SYNCSEL = 0x0F;
    T5CONbits.TON = 1;
}

/******************************************************************************
 * \brief Function stops sending control signal to servo.
 *
 * \input None.
 * 
 * \output None.
 * ****************************************************************************/
inline void ServoStop( void )
{
    OC1R = 0;
}
#endif
/******************************************************************************
 * \brief Function initializes UART driver.
 *
 * \input None
 *
 * \output None.
 * ****************************************************************************/
inline void uart_init( void )
{
    /* Baudrate = FCY / (16 * ( U1BRG + 1 ) ) */
    U1BRG = 33;
    /* No flow control. */
    U1MODEbits.RTSMD = 1;
    /* High baud rate enabled. */
    U1MODEbits.BRGH = 1;
    U1STAbits.UTXISEL1 = 1;
    U1STAbits.UTXISEL0 = 0;
    /* Set interrupt priority. */
    _U1RXIP = 5;
    /* Clear receive interrupt flag. */
    _U1RXIF = 0;
    /* Do not enable UART receive interrupt. */
    _U1RXIE = 0;
    /* Enable UART. */
    U1MODEbits.UARTEN = 1;
    /* U1TX pin is controlled by UART. */
    U1STAbits.UTXEN = 1;
}

/******************************************************************************
 * \brief Function sends a string of characters to UART.
 *
 * \input char *aT_buffer
 *      Pointer to null-terminated string of characters to be sent.
 *
 * \output None.
 * ****************************************************************************/
void uart_t( char *aT_buffer )
{
    int i = 0;
    while( TRUE )
    {
        if( aT_buffer[i] == '\0' )
        {
            break;
        }
        /* Wait until buffer not full. */
        while( U1STAbits.UTXBF );
        U1TXREG = (unsigned int)aT_buffer[i];
        i++;
    }
}

/******************************************************************************
 * \brief Function formats data and saves it to buffer.
 *
 * \input char *aOutput
 *      Pointer to buffer to save the output.
 *
 * \input int max_char
 *      Maximum number of characters to be written to output buffer.
 *
 * \input char *aInput
 *      Pointer to buffer from string of characters is being read.
 *
 * \notes Recognized flags are as in usual sprintf, although their number is limited.
 *  Types of numbers recognized:
 *      - i, d  - decimal numbers,
 *      - u     - unsigned decimal numbers,
 *      - f     - floating point numbers, WARNING! implementation is simple -
 *                  max number if 150 000, precision is one digit after comma,
 *      - x, X  - hexadecimal numbers,
 * Flags recognized:
 *      - 0     - print zeroes instead of whitespaces,
 *      - digit before type - minimum number of printed characters,
 *      - '.'   - next digit means floating point number precision,
 *      - l     - number is long,
 *
 * \output 0 if success, 1 if buffer is too small
 * ****************************************************************************/
int ap_sprintf_safe( char *aOutput, int max_char, char *aInput, ... )
{
    /* \brief List of arguments. */
    va_list ap;
    /* \brief j-th char of output string. */
    int j = 0;
    /* \brief i-th char of input string. */
    int i = 0;
    /* \brief Helper variable in converting number to chars. */
    int k = 0;
    /* \brief Number of leading zeroes in converting hexadecimal numbers. */
    int leading_zeroes;
    /* \brief Minimum number of printable digits per number. */
    int width = 1;
    /* \brief Flag if zeroes should be printed instead of whitespaces.
     * \desc If number has less digits than minimum number of printed characters per number, then this flag specifies
     * what chars should be used ti fill remaining chars.
     * 0 - fill with spaces,
     * 1 - fill with leading zeroes. */
    int zero_pad = 0;
    /* \brief Flag if currently processed number is long. */
    int long_i = 0;
    /* \brief Variable holding processed character. */
    char character;
    /* \brief Variable holding processed number. */
    int number;
    /* \brief Temporary variable in converting numbers. */
    int temp;
    /* \brief Temporary unsigned variable in converting numbers. */
    unsigned int utemp;
    /* \brief Number of printable characters after comma. */
    int precision = 2;
    /* \brief Temporary variable for precision. */
    int precision_tmp;
    /* \brief Variable holding processed long number. */
    long number_long;
    /* \brief Temporary variable in converting long numbers. */
    long temp_long;
    /* \brief Variable holding processed float number. */
    double number_float;
    /* \brief Variable holding processed unsigned number. */
    unsigned int unumber;
    /* \brief Temporary buffer to hold semi-processed characters. */
    char str_number[10] = "";
    /* \brief Pointer to buffer containing string of chars to be copied into outbut buffer. */
    char *str_pointer;    

    /* Initialize list of arguments. */
    va_start (ap, aInput);

    /* Go through all Input characters and check if it is a flag*/
    for(; aInput[i] != '\0'; i++ )
    {
        if( aInput[i] == '%' )
        {
            i++;
            /* Flag '0' detected. */
            if( aInput[i] == '0' )
            {
                zero_pad = 1;
                i++;
            }
            /* If there is a digit before number, it is the minimum number of printable digits. */
            if( ( aInput[i] >= '1' ) && ( aInput[i] <= '9' ) )
            {
                width = (int)(aInput[i] - '0');
                i++;
            }
            /* If there is a dot, then next digit means float precision.. */
            if( aInput[i] == '.' )
            {
                i++;
                if( ( aInput[i] >= '0' ) && ( aInput[i] <= '9' ) )
                {
                    precision = (int)(aInput[i] - '0');
                }
                i++;
            }
            /* Default float precision. */
            else
            {
                precision = 2;
            }
            /* Flag 'l' detected. */
            if( aInput[i] == 'l' )
            {
                long_i = 1;
                i++;
            }
            switch( aInput[i] )
            {
            case 'i':
            case 'd':
                /* Long int. */
                if( long_i )
                {
                    number_long = va_arg( ap, long );
                    /* If long number is negative, print '-' and treat as positive number. */
                    if( number_long < 0 )
                    {
                        aOutput[j++] = '-';
                        /* There should be more than three chars left in buffer (new line, line feed and null)
                         * in order to write data. */
                        if( j >= ( max_char - 3 ) )
                        {
                            goto end_of_buffer;
                        }
                        number_long = -number_long;
                    }
                    for( k = 0; number_long >= 65536; k++ )
                    {
                        temp_long = number_long/10;
                        str_number[k] = ( char )( number_long - temp_long*10 + (long int)'0' );
                        number_long = temp_long;
                    }
                    unumber = ( unsigned int )number_long;
                    for(; unumber >= 1; k++ )
                    {
                        utemp = unumber/10;
                        str_number[k] = ( char )( unumber - utemp*10 + (unsigned int)'0' );
                        unumber = utemp;
                    }
                }
                /* Short int. */
                else
                {    
                    number = va_arg( ap, int );
                    /* If number is negative, print '-' and treat as positive number. */
                    if( number < 0 )
                    {
                        aOutput[j++] = '-';
                        /* There should be more than three chars left in buffer (new line, line feed and null)
                         * in order to write data. */
                        if( j >= max_char - 3 )
                        {
                            goto end_of_buffer;
                        }
                        number = -number;
                    }
                    for( k = 0; number >= 1; k++ )
                    {
                        temp = number/10;
                        str_number[k] = ( char )( number - temp*10 + (int)'0' );
                        number = temp;
                    }
                }
                /* Copy data from temporary buffer to output buffer. */
                if( k == 0 )
                {
                    str_number[k++] = (int)'0';
                }
                while( ( k < width ) && k !=0 )
                {
                    if( zero_pad )
                    {
                        str_number[k++] = (int)'0';
                    }
                    else
                    {
                        str_number[k++] = (int)' ';
                    }
                }
                while( k > 0 )
                {
                    aOutput[j++] = str_number[--k];
                        /* There should be more than three chars left in buffer (new line, line feed and null)
                         * in order to write data. */
                    if( j >= ( max_char - 3 ) )
                    {
                        goto end_of_buffer;
                    }
                }
                break;
            case 'u':
                /* Number is unsigned. */
                unumber = va_arg( ap, unsigned int );
                for( k = 0; unumber >= 1; k++ )
                {
                    utemp = unumber/10;
                    str_number[k] = ( char )( unumber - utemp*10 + (unsigned int)'0' );
                    unumber = utemp;
                }
                if( k == 0 )
                {
                    str_number[k++] = (int)'0';
                }
                while( ( k < width ) && k != 0 )
                {
                    if( zero_pad )
                    {
                        str_number[k++] = (int)'0';
                    }
                    else
                    {
                        str_number[k++] = ' ';
                    }
                }
                while( k > 0 )
                {
                    aOutput[j++] = str_number[--k];
                        /* There should be more than three chars left in buffer (new line, line feed and null)
                         * in order to write data. */
                    if( j >= ( max_char - 3 ))
                    {
                        goto end_of_buffer;
                    }
                }
                break;
            case 'f':
                /* Floating point number. */
                number_float = va_arg( ap, float );
                /* Check if number is +inf. */
                if( number_float == HUGE_VAL )
                {
                    aOutput[j++] = 'i';
                    aOutput[j++] = 'n';
                    aOutput[j++] = 'f';
                    /* There should be more than three chars left in buffer (new line, line feed and null)
                     * in order to write data. */
                    if( j >= ( max_char - 3 ) )
                    {
                        goto end_of_buffer;
                    }
                }
                /* Check if number is -inf. */
                else if(number_float == -HUGE_VAL)
                {
                    aOutput[j++] = '-';
                    aOutput[j++] = 'i';
                    aOutput[j++] = 'n';
                    /* There should be more than three chars left in buffer (new line, line feed and null)
                     * in order to write data. */
                    if( j >= ( max_char - 3 ) )
                    {
                        goto end_of_buffer;
                    }
                    aOutput[j++] = 'f';
                    if( j >= ( max_char - 3 ) )
                    {
                        goto end_of_buffer;
                    }
                }
                /* Number doesn't equal to itself only if it is NaN (not a number). */
                else if( number_float == number_float )
                {
                    /* If long number is negative, print '-' and treat as positive number. */
                    if( number_float < 0 )
                    {
                        aOutput[j++] = '-';
                        number_float = -number_float;
                        /* There should be more than three chars left in buffer (new line, line feed and null)
                         * in order to write data. */
                        if( j >= ( max_char - 3 ) )
                        {
                            goto end_of_buffer;
                        }
                    }
                    number_long = ( long )number_float;
                    number_float = number_float - ( float )number_long;
                    for( k = 0; number_long >= 1; k++ )
                    {
                        temp_long = number_long/10;
                        str_number[k] = ( char )( number_long - temp_long*10 + (long)'0' );
                        number_long = temp_long;
                    }
                    if( k == 0 )
                    {
                        str_number[k++] = '0';
                    }
                    while( ( k < width ) && k != 0 )
                    {
                        if(zero_pad)
                        {
                            str_number[k++] = '0';
                        }
                        else
                        {
                            str_number[k++] = ' ';
                        }
                    }
                    while( k > 0 )
                    {
                        aOutput[j++] = str_number[--k];
                        /* There should be more than three chars left in buffer (new line, line feed and null)
                         * in order to write data. */
                        if( j >= ( max_char - 3 ) )
                        {
                            goto end_of_buffer;
                        }
                    }
                    
                    if( precision > 0 )
                    {
                        aOutput[j++] = '.';
                        /* There should be more than three chars left in buffer (new line, line feed and null)
                         * in order to write data. */
                        if( j >= ( max_char - 3 ) )
                        {
                            goto end_of_buffer;
                        }
                        precision_tmp = precision;
                        while( precision_tmp-- )
                        {
                            number_float = number_float*10;
                        }
                        if( precision >= 5 )
                        {
                            number_long = ( long )number_float;
                            for( k = 0; number_long >= 1; k++ )
                            {
                                temp_long = number_long/10;
                                str_number[k] = ( char )(number_long - temp_long*10 + (long)'0');
                                number_long = temp_long;
                            }
                        }
                        else
                        {
                            number = ( int )number_float;
                            for( k = 0; number >= 1; k++ )
                            {
                                temp = number/10;
                                str_number[k] = ( char )(number - temp*10 + (int)'0');
                                number = temp;
                            }
                        }    
                        if( k == 0 )
                        {
                            str_number[k++] = '0';
                        }
                        while( ( k < precision ) && k != 0)
                        {
                            str_number[k++] = '0';
                        }
                        while( k > 0 )
                        {
                            aOutput[j++] = str_number[--k];
                            /* There should be more than three chars left in buffer (new line, line feed and null)
                             * in order to write data. */
                            if( j >= ( max_char - 3 ) )
                            {
                                goto end_of_buffer;
                            }
                        }
                    } // if( precision > 0 )
                } // else if( number_float == number_float )
                /* number wasn't equal to itself, so it is a NaN. */
                else
                {
                    aOutput[j++] = 'N';
                    aOutput[j++] = 'a';
                    aOutput[j++] = 'N';
                    /* There should be more than three chars left in buffer (new line, line feed and null)
                     * in order to write data. */
                    if( j >= ( max_char - 3 ) )
                    {
                        goto end_of_buffer;
                    }
                }    
                break;
            case 'x':
            case 'X':
                /* Number is hexadecimal. */
                leading_zeroes = 2;
                number = va_arg( ap, int );
                for( k = 0; number >= 1; k++ )
                {
                    temp = number/16;
                    str_number[k] = ( char )( number - temp*16 + (int)'0' );
                    number = temp;
                }
                if( k < leading_zeroes )
                {
                    while( k < leading_zeroes )
                    {
                        str_number[k++] = '0';
                    }
                }    
                if( k == 0 )
                {
                    aOutput[j++] = '0';
                    /* There should be more than three chars left in buffer (new line, line feed and null)
                     * in order to write data. */
                    if( j >= ( max_char - 3 ) )
                    {
                        goto end_of_buffer;
                    }
                }
                else
                {
                    while( k > 0 )
                    {
                        if( str_number[--k] > '9' )
                        {
                            /* Correction for digits A-F. */
                            aOutput[j++] = (char)((int)str_number[k] + (int)'A' - (int)'9' - 1);
                        }
                        else
                        {
                            aOutput[j++] = str_number[k];
                        }
                        /* There should be more than three chars left in buffer (new line, line feed and null)
                         * in order to write data. */
                        if( j >= ( max_char - 3 ) )
                        {
                            goto end_of_buffer;
                        }
                    }    
                }
                break;
            case 'c':
                /* Single character. */
                character = va_arg( ap, char );
                aOutput[j++] = character;
                /* There should be more than three chars left in buffer (new line, line feed and null)
                 * in order to write data. */
                if( j >= ( max_char - 3 ) )
                {
                    goto end_of_buffer;
                }
                break;
            case 's':
                /* String of characters. */
                str_pointer = va_arg( ap, char* );
                while( *str_pointer != NULL)
                {
                    aOutput[j++] = *str_pointer++;
                }
                /* There should be more than three chars left in buffer (new line, line feed and null)
                 * in order to write data. */
                if( j >= ( max_char - 3 ) )
                {
                    goto end_of_buffer;
                }
                break;
            case '%':
                /* Two % occured after each other - print sinlge %. */
                aOutput[j++] = '%';
                /* There should be more than three chars left in buffer (new line, line feed and null)
                 * in order to write data. */
                if( j >= ( max_char - 3 ) )
                {
                    goto end_of_buffer;
                }
                break;
            default:
                /* In case of unrecognized flag, just copy it to output buffer. */
                aOutput[j++] = aInput[i-1];
                /* There should be more than three chars left in buffer (new line, line feed and null)
                 * in order to write data. */
                if( j >= ( max_char - 3 ) )
                {
                    goto end_of_buffer;
                }
                aOutput[j++] = aInput[i];
                if( j >= ( max_char - 3 ) )
                {
                    goto end_of_buffer;
                }
                break;
            }
            long_i = 0;
            width = 1;
            zero_pad = 0;
        } //if( aInput[i] == '%' )
        /* If there are no flag, just copy input to output. */
        else
        {
            aOutput[j++] = aInput[i];
            /* There must be place at least for ending null character. */
            if(j >= max_char - 1)
            {
                goto end_of_buffer;
            }
        }
    }
    aOutput[j++] = '\0';
    if( j >= max_char )
    {
        goto end_of_buffer;
    }
    va_end (ap);
    return 0;
    
end_of_buffer:
    if( max_char >= 3 )
    {
        aOutput[max_char - 3] = '\r';
        aOutput[max_char - 2] = '\n';
        aOutput[max_char - 1] = '\0';
    }    
    va_end (ap);
    return 1;
}

/******************************************************************************
 * \brief Funciton return absolute value of input.
 *
 * \input float data
 *      Input data.
 *
 * \output float
 *      Absolute value of input data.
 *
 * \output None.
 * ****************************************************************************/
float ap_abs( float data )
{
    if( data >= 0 )
    {
        return data;
    }
    else
    {
        return -data;
    }
}

/******************************************************************************
 * \brief Function processes input data using Kalman filtering.
 *
 * \input float data
 *      Input data.
 *
 * \output None.
 * ****************************************************************************/
void kalman_filter( ap_KalmanData_t *data )
{
/********************************** PREDICT ***********************************/
    /* Predict next data. */
    data->priori = data->post + data->derivativePost;
    /* Smooth if rocket is descending */
    if( ap_ArecorderState == AWAITING_FOR_SECOND_PARACHUTE )
    {
        data->errorCovPriori = data->errorCovPost + KALMAN_Q2;
    }
    else
    {
        data->errorCovPriori = data->errorCovPost + KALMAN_Q1;
    }
    /* Gain calculation. */
    data->gain = data->errorCovPriori/( data->errorCovPriori + KALMAN_R );

/*********************************** UPDATE ***********************************/
    /* Update predicted data with actual data. */
    data->post = data->priori + data->gain*( data->raw - data->priori);
    data->derivativePost = data->derivativePost + data->gain*( data->post - data->postLast - data->derivativePost );
    /* Calculate new error covariance. */
    data->errorCovPost = ( 1 - data->gain )*data->errorCovPriori;
    /* Update temporary data for calculating difference between current and last sample. */
    data->postLast = data->post;
}

/******************************************************************************
 * \brief Function initializes inputs and outputs.
 *
 * \input None.
 *
 * \output None.
 * ****************************************************************************/
void io_init( void )
{
    /* Disable all analog pins. */
    ANSB = 0x0000;
    ANSC = 0x0000;
    ANSD = 0x0000;
    ANSF = 0x0000;
    ANSG = 0x0000;
    /* Enable desired analog pins. */
    _ANSB3 = 1;             // Enable analog pin - vbatt
    _ANSB1 = 1;             // Enable analog pin - out 1 sense
    _ANSB0 = 1;             // Enable analog pin - out 2 sense
    _ANSB6 = 1;             // Enable analog pin - out 3 sense
    _ANSB2 = 1;             // Enable analog pin - temp1
    
    //Make sure that the general purpose output driver multiplexed with
    //the VBUS pin is always consistently configured to be tri-stated in
    //USB applications, so as to avoid any possible contention with the host.
    //(ex: maintain TRISFbits.TRISF7 = 1 at all times).
    TRISFbits.TRISF7 = 1;
            
    OUT1 = 0;               // OUT1
    TRIS_OUT1 = 0;          // OUT1
    OUT2 = 0;               // OUT2
    TRIS_OUT2 = 0;          // OUT2
    OUT3 = 0;               // OUT3
    TRIS_OUT3 = 0;          // OUT3
    buzzer_off();
    TRIS_BUZZER = 0;        // BUZZER
    TRIS_LED = 0;           // Red LED.
    IGN_TEST = 0;           // IGN_TEST
    TRIS_IGN_TEST = 0;      // IGN_TEST
    
    CONF_SEL1_PUE = 1;      // conf1 pull up enable
    CONF_SEL2_PUE = 1;      // conf2 pull up enable
    
    _RCDIV = 0;

    /* SPI to SD card. */
    /* MISO     <=> RP22 */
    _SDI1R = RP_I_SPI_MISO;
    /* RP24     <=> MOSI */
    RP_O_SPI_MOSI = 7;
    /* RP23     <=> SCK */
    RP_O_SPI_SCK = 8;

    /* UART */
    /* U1RX     <=> RP1 */
    _U1RXR = RP_I_UART_RX;
    /* RP0      <=> U1TX */
    RP_O_UART_TX = 3;
    
#ifdef SERVO_CONTROL
    /* RP18 <=> PWM1 (output compare1)*/
    RP_O_PWM_1 = 18;
#endif
}

/******************************************************************************
 * \brief Function writes header into data file.
 *
 * \input FSFILE *fp_meas
 *      Pointer to file in SD Card.
 *
 * \input ap_ConfigurationData_t *conf_data
 *      Pointer structure holding configuration data.
 *
 * \output None.
 * ****************************************************************************/
void write_header( FSFILE *filePointer, ap_ConfigurationData_t *conf_data )
{
    /* Check if pointer is not null. */
    if( filePointer == NULL )
    {
        return;
    }
    
    write_header_line( "Serial number,%d\r\n", conf_data->SerialNumber );
    write_header_line( "Owner name,%s\r\n", conf_data->OwnerName );
    write_header_line( "Owner phone,%s\r\n", conf_data->OwnerPhone );
    write_header_line( "Configuration selected,%d\r\n", conf_data->conf_select + 1 );
    write_header_line( "X_1_g (24g),%d\r\n", conf_data->A_1_g );
    write_header_line( "Hx_1_g (80g),%d\r\n", conf_data->H_1_g );
    write_header_line( "X_0_g (24g),%d\r\n", conf_data->A_0_g );
    write_header_line( "Hx_0_g (80g),%d\r\n", conf_data->H_0_g );
    write_header_line( "Y_0_g (24g),%d\r\n", conf_data->Y_0_g );
    write_header_line( "Z_0_g (24g),%d\r\n", conf_data->Z_0_g );
    write_header_line( "Hacc present,%d\r\n", conf_data->HaccPresent );
    write_header_line( "SecondEngineDelayTrigger [s],%d\r\n", conf_data->SecondEngineDelayTrigger );
    write_header_line( "MainParachuteTriggerHeight [m],%d\r\n", conf_data->MainParachuteTriggerAltitude );
    write_header_line( "LaunchpadHeight [m],%d\r\n", conf_data->LaunchpadHeight );
    write_header_line( "Drogue parachute failure detection [m/s],%d\r\n", conf_data->DrogueParaFailTreshold );
    write_header_line( "TemperatureOffset1 [deg],%d\r\n", conf_data->TemperatureOffset1 );
    write_header_line( "Pressure coefficient #1,44330.77\r\n" );
    write_header_line( "Pressure coefficient #2,0.1902632\r\n" );
    write_header_line( "Pressure at sea level [Pa],101325\r\n" );
    write_header_line( "Samples per second,100\r\n\r\n" );     /* Extra new line. */
    write_header_line( "seconds,X_acc,Y_acc,Z_acc,HX_acc," );
    write_header_line( "Pressure,Kalman pressure,temp,Vaxis,AltitudeFromPressure," );
    write_header_line( "Altitude,State,VelocityP,ParachuteFailureSenseCnt\r\n" );
    
    (void)FSfsync( filePointer );
}


/******************************************************************************
 * \brief Function writes summary into data file.
 *
 * \input ap_summaryData_t *ap_Summary
 *      Pointer structure holding summary data.
 *
 * \output None.
 * ****************************************************************************/
void writeInitialSummary( ap_summaryData_t *ap_Summary )
{
    write_footer_line_summary( "Rocket angle at launch,%.1f,[deg]\r\n", ap_Summary->RocketAngleStart );
    write_footer_line_summary( "Velocity at the moment of leaving launchpad,%.1f,[m/s]\r\n", ap_Summary->LaunchpadVelocity );
    write_footer_line_summary( "Pressure at ground level,%.0f,[Pa]\r\n", ap_Summary->PressureGround );
}

/******************************************************************************
 * \brief Function writes summary into data file.
 *
 * \input ap_summaryData_t *ap_Summary
 *      Pointer structure holding summary data.
 *
 * \output None.
 * ****************************************************************************/
void writeSummary( ap_summaryData_t *ap_Summary, ap_Event_t *Event )
{
    /** \desc Helper variable to calculate time. */
    static unsigned int EventTemp;
    /** \desc Helper variable to calculate time. */
    static unsigned int EventTempSec;

    write_footer_line( "Pressure at apogee,%.0f,[Pa]\r\n", ap_Summary->PressureMinimum );
    write_footer_line( "Maximum velocity at rocket axis,%.1f,[m/s]\r\n", ap_Summary->VAxisMax );
    //(void)FSfsync( ap_FpFlightSummary );
    (void)FSfsync( ap_FpMeas );

    write_footer_line( "Maximum altitude (acc),%.0f,[m]\r\n", ap_Summary->AltitudeMax );
    write_footer_line( "Maximum altitude (pressure),%.0f,[m]\r\n",
                       p2altitude( ap_Summary->PressureMinimum ) - ap_Summary->HeightAMSL );
    //(void)FSfsync( ap_FpFlightSummary );
    (void)FSfsync( ap_FpMeas );

    write_footer_line( "Velocity at first engine burnout,%.0f,[m/s]\r\n", ap_Summary->Engine1Burnout_VAxis );
    write_footer_line( "Altitude  at first engine burnout,%.0f,[m]\r\n", ap_Summary->Engine1Burnout_Altitude );
    //(void)FSfsync( ap_FpFlightSummary );
    (void)FSfsync( ap_FpMeas );

    write_footer_line( "Pressure at first engine burnout,%.0f,[Pa]\r\n", ap_Summary->Engine1Burnout_Pressure );
    write_footer_line( "Rocket angle at first engine burnout,%.1f,[deg]\r\n", ap_Summary->Engine1Burnout_RocketAngle );
    //(void)FSfsync( ap_FpFlightSummary );
    (void)FSfsync( ap_FpMeas );

    write_footer_line( "Velocity at second engine burnout,%.0f,[m/s]\r\n", ap_Summary->Engine2Burnout_VAxis );
    write_footer_line( "Altitude  at second engine burnout,%.0f,[m]\r\n", ap_Summary->Engine2Burnout_Altitude );
    //(void)FSfsync( ap_FpFlightSummary );
    (void)FSfsync( ap_FpMeas );

    write_footer_line( "Pressure at second engine burnout,%.0f,[Pa]\r\n", ap_Summary->Engine2Burnout_Pressure );
    write_footer_line( "Rocket angle at second engine burnout,%.1f,[deg]\r\n", ap_Summary->Engine2Burnout_RocketAngle );
    //(void)FSfsync( ap_FpFlightSummary );
    (void)FSfsync( ap_FpMeas );

    write_footer_line( "Rocket launch,%d.%d,[s]\r\n", Event->launch.Sec, Event->launch.dSec );
    write_footer_line( "Burnout of first stage engine,%d.%02d,[s]\r\n", Event->burnout1.Sec, Event->burnout1.dSec );
    write_footer_line( "Ignitting second stage engine fuse,%d.%02d,[s]\r\n", Event->stg2Fire.Sec, Event->stg2Fire.dSec );
    //(void)FSfsync( ap_FpFlightSummary );
    (void)FSfsync( ap_FpMeas );

    write_footer_line( "Firing second stage engine,%d.%02d,[s]\r\n", Event->stg2Active.Sec, Event->stg2Active.dSec );
    write_footer_line( "Burnout of second stage engine,%d.%02d,[s]\r\n", Event->burnout2.Sec, Event->burnout2.dSec );
    write_footer_line( "Apogee detection,%d.%02d,[s]\r\n", Event->apogee.Sec, Event->apogee.dSec );
    //(void)FSfsync( ap_FpFlightSummary );
    (void)FSfsync( ap_FpMeas );

    write_footer_line( "Minimum velocity around apogee,%d.%02d,[m/s]\r\n", Event->minV.Sec, Event->minV.dSec );
    write_footer_line( "Firing drogue parachute,%d.%02d,[s]\r\n", Event->para1.Sec, Event->para1.dSec );
    //(void)FSfsync( ap_FpFlightSummary );
    (void)FSfsync( ap_FpMeas );

    write_footer_line( "Firing main parachute,%d.%02d,[s]\r\n", Event->para2.Sec, Event->para2.dSec );
    write_footer_line( "Rocket landing,%d.%02d,[s]\r\n", Event->land.Sec, Event->land.dSec );

    // czas pracy silnika pierwszego stopnia =
    //      koniec pracy silnika pierwszego stopnia - start pracy silnika pierwszego stopnia
    if( Event->burnout1.dSec < Event->launch.dSec )
    {
        EventTemp = Event->burnout1.dSec + 100 - Event->launch.dSec;
        EventTempSec = Event->burnout1.Sec - Event->launch.Sec - 1;
    }
    else
    {
        EventTemp = Event->burnout1.dSec - Event->launch.dSec;
        EventTempSec = Event->burnout1.Sec - Event->launch.Sec;
    }

    write_footer_line( "First engine burning time,%d.%02d,[s]\r\n", EventTempSec, EventTemp );

    // czas pracy silnika drugiego stopnia =
    //      koniec pracy silnika drugiego stopnia - start pracy silnika drugiego stopnia
    if( Event->burnout2.dSec < Event->stg2Active.dSec )
    {
        EventTemp = Event->burnout2.dSec + 100 - Event->stg2Active.dSec;
        EventTempSec = Event->burnout2.Sec - Event->stg2Active.Sec - 1;
    }
    else
    {
        EventTemp = Event->burnout2.dSec - Event->stg2Active.dSec;
        EventTempSec = Event->burnout2.Sec - Event->stg2Active.Sec;
    }
    write_footer_line( "Second engine burning time,%d.%02d,[s]\r\n", EventTempSec, EventTemp );

    // czas lotu na pułap = czas osiągnięcia pułapu - start pracy silnika pierwszego stopnia
    if( Event->apogee.dSec < Event->launch.dSec )
    {
        EventTemp = Event->apogee.dSec + 100 - Event->launch.dSec;
        EventTempSec = Event->apogee.Sec - Event->launch.Sec - 1;
    }
    else
    {
        EventTemp = Event->apogee.dSec - Event->launch.dSec;
        EventTempSec = Event->apogee.Sec - Event->launch.Sec;
    }
    //(void)FSfsync( ap_FpFlightSummary );
    (void)FSfsync( ap_FpMeas );
    
    write_footer_line( "Time to apogee,%d.%02d,[s]\r\n", EventTempSec, EventTemp );

    // całkowity czas lotu = czas lądowania - start pracy silnika pierwszego stopnia
    if( Event->land.dSec < Event->launch.dSec )
    {
        EventTemp = Event->land.dSec + 100 - Event->launch.dSec;
        EventTempSec = Event->land.Sec - Event->launch.Sec - 1;
    }
    else
    {
        EventTemp = Event->land.dSec - Event->launch.dSec;
        EventTempSec = Event->land.Sec - Event->launch.Sec;
    }
    write_footer_line( "Total flight time,%d.%02d,[s]\r\n", EventTempSec, EventTemp );
    //(void)FSfsync( ap_FpFlightSummary );
    (void)FSfsync( ap_FpMeas );
}

/******************************************************************************
 * \brief Function sends error message to UART and beeps to indicate error.
 *
 * \desc Function sends error message to UART and beeps number of times to indicate error.
 *      Number of beeps means error number.
 *
 * \input int aErrNumber
 *      Error number.
 *
 * \output None.
 * ****************************************************************************/
void error( int aErrNumber )
{
    (void)ap_sprintf_safe(ap_SendBuffer, SEND_BUFFER_SIZE, "ERR %d\r\n", aErrNumber);
    uart_t(ap_SendBuffer);
    buzzer_on();
    delay_ms(1000);
    buzzer_off();
    while(1);
}

/******************************************************************************
 * \brief Function beeps to indicate warning.
 *
 * \desc Function beeps number of times to indicate warning. Number of beeps means error number.
 *
 * \input int aErrNumber
 *      Error number.
 *
 * \output None.
 * ****************************************************************************/
void warning( int aErrNumber )
{
    buzzer_on();
    delay_ms(1000);
    buzzer_off();
    delay_ms(200);
    while( aErrNumber-- )
    {
        beep(200);
        delay_ms(200);
    }
}

/******************************************************************************
 * \brief Function beeps specified number times.
 *
 * \input int aNumberOfBeeps
 *      Number of beeps.
 *
 * \output None.
 * ****************************************************************************/
void info( int aNumberOfBeeps )
{
    while(aNumberOfBeeps--)
    {
        beep(200);
        delay_ms(200);
    }
}

/******************************************************************************
 * \brief Function beeps and lights LED at the same time.
 *
 * \input int aDelay
 *      Duration of beep.
 *
 * \output None.
 * ****************************************************************************/
void beep( int aDelay )
{
    led_on();
    buzzer_on();
    delay_ms( aDelay );
    led_off();
    buzzer_off();
}

/******************************************************************************
 * \brief Function turns on the buzzer.
 *
 * \input None.
 *
 * \output None.
 * ****************************************************************************/
void buzzer_on(void)
{
    BUZZER = 1;
}

/******************************************************************************
 * \brief Function turns off the buzzer.
 *
 * \input None.
 *
 * \output None.
 * ****************************************************************************/
void buzzer_off(void)
{
    BUZZER = 0;
}

/******************************************************************************
 * \brief Function turns on the LED.
 *
 * \input None.
 *
 * \output None.
 * ****************************************************************************/
void led_on(void)
{
    LED_RED = 1;
}

/******************************************************************************
 * \brief Function turns off the LED.
 *
 * \input None.
 *
 * \output None.
 * ****************************************************************************/
void led_off(void)
{
    LED_RED = 0;
}

/******************************************************************************
 * \brief Function toggles the LED.
 *
 * \input None.
 *
 * \output None.
 * ****************************************************************************/
void led_toggle(void)
{
    LED_RED = ~LED_RED;
}

void nvm_CheckFlags( void )
{
    if( GetPageExpiredPage() )
    {
        warning( WAR_PAGE_EXPIRED );
    }
    if( GetPageCorruptStatus() )
    {
        error( ERR_WRITE );
    }
    if( GetPageWriteError() )
    {
        error( ERR_WRITE );
    }
}
/******************************************************************************
 * \brief Function reads all configuration data from non volatile memory.
 *
 * \input ap_ConfigurationData_t *conf_data
 *      Pointer to structure to write configuration data.
 *
 * \output None.
 * ****************************************************************************/
void nvm_ConfDataReadAll( ap_ConfigurationData_t *conf_data )
{
    unsigned int i;
    unsigned int EERead;
    
    EERead = DataEERead( A_0_G_CALIBRATION );
    if( GetaddrNotFound() == 0 )
    {
        nvm_CheckFlags();
        conf_data->A_0_g = (int)EERead;
    }
    else
    {
        SetaddrNotFound( 0 );
    }
    EERead = DataEERead( Y_0_G_CALIBRATION );
    if( GetaddrNotFound() == 0 )
    {
        nvm_CheckFlags();
        conf_data->Y_0_g = (int)EERead;
    }
    else
    {
        SetaddrNotFound( 0 );
    }
    EERead = DataEERead( Z_0_G_CALIBRATION );
    if( GetaddrNotFound() == 0 )
    {
        nvm_CheckFlags();
        conf_data->Z_0_g = (int)EERead;
    }
    else
    {
        SetaddrNotFound( 0 );
    }
    EERead = DataEERead( HA_0_G_CALIBRATION );
    if( GetaddrNotFound() == 0 )
    {
        nvm_CheckFlags();
        conf_data->H_0_g = (int)EERead;
    }
    else
    {
        SetaddrNotFound( 0 );
    }
    EERead = DataEERead( TEMP1_OFFSET );
    if( GetaddrNotFound() == 0 )
    {
        nvm_CheckFlags();
        conf_data->TemperatureOffset1 = (int)EERead;
    }
    else
    {
        SetaddrNotFound( 0 );
    }
    EERead = DataEERead( MAIN_PARA_H1 + conf_data->conf_select );
    if( GetaddrNotFound() == 0 )
    {
        nvm_CheckFlags();
        conf_data->MainParachuteTriggerAltitude = EERead;
    }
    else
    {
        SetaddrNotFound( 0 );
    }
    EERead = DataEERead( SECOND_ENGINE_DELAY_TRIGGER1 + conf_data->conf_select );
    if( GetaddrNotFound() == 0 )
    {
        nvm_CheckFlags();
        conf_data->SecondEngineDelayTrigger = EERead;
    }
    else
    {
        SetaddrNotFound( 0 );
    }
    EERead = DataEERead( LAUNCHPAD_HEIGHT1 + conf_data->conf_select );
    if( GetaddrNotFound() == 0 )
    {
        nvm_CheckFlags();
        conf_data->LaunchpadHeight = EERead;
    }
    else
    {
        SetaddrNotFound( 0 );
    }
    EERead = DataEERead( DROGUE_PARACHUTE_FAILURE_TRESHOLD1 + conf_data->conf_select );
    if( GetaddrNotFound() == 0 )
    {
        nvm_CheckFlags();
        conf_data->DrogueParaFailTreshold = EERead;
    }
    else
    {
        SetaddrNotFound( 0 );
    }
    EERead = DataEERead( SERIAL_NUMBER );
    if( GetaddrNotFound() == 0 )
    {
        nvm_CheckFlags();
        conf_data->SerialNumber = EERead;
    }
    else
    {
        SetaddrNotFound( 0 );
    }
    for( i = 0; i < OWNER_PHONE_LENGTH; i++ )
    {
        EERead = DataEERead( OWNER_PHONE + i );
        if( GetaddrNotFound() == 0 )
        {
            nvm_CheckFlags();
            conf_data->OwnerPhone[0+2*i] = (char)( (EERead & 0xFF00 ) >> 8);
            if( conf_data->OwnerPhone[0+2*i] == '\0' )
            {
                break;
            }
            conf_data->OwnerPhone[1+2*i] = (char)(EERead & 0x00FF);
            if( conf_data->OwnerPhone[1+2*i] == '\0' )
            {
                break;
            }
        }
        else
        {
            SetaddrNotFound( 0 );
            break;
        }
    }
    conf_data->OwnerPhone[OWNER_PHONE_LENGTH*2] = '\0';
    for( i = 0; i < OWNER_NAME_LENGTH; i++ )
    {
        EERead = DataEERead( OWNER_NAME + i );
        if( GetaddrNotFound() == 0 )
        {
            nvm_CheckFlags();
            conf_data->OwnerName[0+2*i] = (char)( (EERead & 0xFF00 ) >> 8);
            if( conf_data->OwnerName[0+2*i] == '\0' )
            {
                break;
            }
            conf_data->OwnerName[1+2*i] = (char)(EERead & 0x00FF);
            if( conf_data->OwnerName[1+2*i] == '\0' )
            {
                break;
            }
        }
        else
        {
            SetaddrNotFound( 0 );
            break;
        }
    }
    conf_data->OwnerName[OWNER_NAME_LENGTH*2] = '\0';
}

/******************************************************************************
 * \brief Function reads desired configuration data from non volatile memory.
 *
 * \input int configurationBitNumber
 *      Number of configuration data to be read.
 *
 * \output int
 *      Data read from nvm.
 * ****************************************************************************/
int nvm_ConfDataGet( unsigned int configurationDataNumber )
{
    unsigned int EERead;
    if( configurationDataNumber <= EE_LARGEST_ADDRESS )
    {
        EERead = DataEERead( configurationDataNumber );
        if( GetaddrNotFound() == 0 )
        {
            nvm_CheckFlags();
            return (int)EERead;
        }
        /* If data does not exist in nvm, it means it wasn't programmed yet. Return default data. */
        else
        {
            SetaddrNotFound( 0 );
            if( configurationDataNumber == MAIN_PARA_H1 )
            {
                return MAIN_PARA_H1_DEFAULT;
            }
            else if( configurationDataNumber == MAIN_PARA_H2 )
            {
                return MAIN_PARA_H2_DEFAULT;
            }
            else if( configurationDataNumber == MAIN_PARA_H3 )
            {
                return MAIN_PARA_H3_DEFAULT;
            }
            else if( configurationDataNumber == MAIN_PARA_H4 )
            {
                return MAIN_PARA_H4_DEFAULT;
            }
            if( ( configurationDataNumber >= SECOND_ENGINE_DELAY_TRIGGER1 ) &&
                ( configurationDataNumber <= SECOND_ENGINE_DELAY_TRIGGER4 ) )
            {
                return SECOND_ENGINE_DELAY_TRIGGER_DEFAULT;
            }
            if( ( configurationDataNumber >= LAUNCHPAD_HEIGHT1 ) &&
                ( configurationDataNumber <= LAUNCHPAD_HEIGHT4 ) )
            {
                return LAUNCHPAD_HEIGHT_DEFAULT;
            }
            if( ( configurationDataNumber >= DROGUE_PARACHUTE_FAILURE_TRESHOLD1 ) &&
                ( configurationDataNumber <= DROGUE_PARACHUTE_FAILURE_TRESHOLD4 ) )
            {
                return DROGUE_PARA_FAIL_TRESHOLD_DEFAULT;
            }
            return 0;
        }
    }
    return -1;
}

/******************************************************************************
 * \brief Function updates configuration data.
 *
 * \input int configurationBitNumber
 *      Number of configuration data to be read.
 *
 * \input ap_ConfigurationData_t *conf_data
 *
 * \output None.
 * ****************************************************************************/
void nvm_UpdateConfData( unsigned int configurationBitNumber, ap_ConfigurationData_t *conf_data )
{
    unsigned int EERead;

    if( configurationBitNumber == A_0_G_CALIBRATION )
    {
        EERead = DataEERead( A_0_G_CALIBRATION );
        if( GetaddrNotFound() == 0 )
        {
            nvm_CheckFlags();
            conf_data->A_0_g = (int)EERead;
        }
        else
        {
            SetaddrNotFound( 0 );
        }
    }
    else if( configurationBitNumber == Y_0_G_CALIBRATION )
    {
        EERead = DataEERead( Y_0_G_CALIBRATION );
        if( GetaddrNotFound() == 0 )
        {
            nvm_CheckFlags();
            conf_data->Y_0_g = (int)EERead;
        }
        else
        {
            SetaddrNotFound( 0 );
        }
    }
    else if( configurationBitNumber == Z_0_G_CALIBRATION )
    {
        EERead = DataEERead( Z_0_G_CALIBRATION );
        if( GetaddrNotFound() == 0 )
        {
            nvm_CheckFlags();
            conf_data->Z_0_g = (int)EERead;
        }
        else
        {
            SetaddrNotFound( 0 );
        }
    }
    else if( configurationBitNumber == HA_0_G_CALIBRATION )
    {
        EERead = DataEERead( HA_0_G_CALIBRATION );
        if( GetaddrNotFound() == 0 )
        {
            nvm_CheckFlags();
            conf_data->H_0_g = (int)EERead;
        }
        else
        {
            SetaddrNotFound( 0 );
        }
    }
    else if( configurationBitNumber == TEMP1_OFFSET )
    {
        EERead = DataEERead( TEMP1_OFFSET );
        if( GetaddrNotFound() == 0 )
        {
            nvm_CheckFlags();
            conf_data->TemperatureOffset1 = (int)EERead;
        }
        else
        {
            SetaddrNotFound( 0 );
        }
    }
    else if( ( configurationBitNumber >= MAIN_PARA_H1 ) &&
             ( configurationBitNumber <= MAIN_PARA_H4 ) )
    {
        EERead = DataEERead( configurationBitNumber );
        if( GetaddrNotFound() == 0 )
        {
            nvm_CheckFlags();
            conf_data->MainParachuteTriggerAltitude = EERead;
        }
        else
        {
            conf_data->MainParachuteTriggerAltitude = (unsigned int)nvm_ConfDataGet( MAIN_PARA_H1 + conf_data->conf_select );
            SetaddrNotFound( 0 );
        }
    }
    else if( ( configurationBitNumber >= SECOND_ENGINE_DELAY_TRIGGER1 ) &&
             ( configurationBitNumber <= SECOND_ENGINE_DELAY_TRIGGER4 ) )
    {
        EERead = DataEERead( configurationBitNumber );
        if( GetaddrNotFound() == 0 )
        {
            nvm_CheckFlags();
            conf_data->SecondEngineDelayTrigger = EERead;
        }
        else
        {
            conf_data->SecondEngineDelayTrigger = (unsigned int)nvm_ConfDataGet( SECOND_ENGINE_DELAY_TRIGGER1 + conf_data->conf_select );
            SetaddrNotFound( 0 );
        }
    }
    else if( ( configurationBitNumber >= LAUNCHPAD_HEIGHT1 ) &&
             ( configurationBitNumber <= LAUNCHPAD_HEIGHT4 ) )
    {
        EERead = DataEERead( configurationBitNumber );
        if( GetaddrNotFound() == 0 )
        {
            nvm_CheckFlags();
            conf_data->LaunchpadHeight = EERead;
        }
        else SetaddrNotFound( 0 );
    }
    else if( ( configurationBitNumber >= DROGUE_PARACHUTE_FAILURE_TRESHOLD1 ) &&
             ( configurationBitNumber <= DROGUE_PARACHUTE_FAILURE_TRESHOLD4 ) )
    {
        EERead = DataEERead( configurationBitNumber );
        if( GetaddrNotFound() == 0 )
        {
            nvm_CheckFlags();
            conf_data->DrogueParaFailTreshold = EERead;
        }
        else SetaddrNotFound( 0 );
    }
    else if( configurationBitNumber == SERIAL_NUMBER )
    {
        EERead = DataEERead( SERIAL_NUMBER );
        if( GetaddrNotFound() == 0 )
        {
            nvm_CheckFlags();
            conf_data->SerialNumber = EERead;
        }
        else
        {
            conf_data->LaunchpadHeight = (unsigned int)nvm_ConfDataGet( LAUNCHPAD_HEIGHT1 + conf_data->conf_select );
            SetaddrNotFound( 0 );
        }
    }
}
