#ifndef APLIB_H
#define APLIB_H

/*****************************************************************************/
/*                                 INCLUDES                                  */
/*****************************************************************************/
#include "p24FJ128GB206.h"
#include "main.h"
#include "FSIO.h"
#include "SD-SPI.h"
#include "BoardConfiguration.h"
#include "dbg.h"

/*****************************************************************************/
/*                                 DEFINES                                   */
/*****************************************************************************/
/** \desc Perform doftware reset. */
#define software_reset()            {__asm__ volatile ("reset");}

/** \desc Write one line of the header in data file. */
#define write_header_line( M, ... ) (void)ap_sprintf_safe( ap_SendBuffer, SEND_BUFFER_SIZE, M, ##__VA_ARGS__ );       \
                                    (void)FSfwrite( ap_SendBuffer, 1, strlen( ap_SendBuffer ), ap_FpMeas )

/** \desc Write one line of the summary data in data file and summary file. */
#define write_footer_line( M, ... ) (void)ap_sprintf_safe( ap_SendBuffer, SEND_BUFFER_SIZE, M, ##__VA_ARGS__ );       \
                                    /*(void)FSfwrite( ap_SendBuffer, 1, strlen( ap_SendBuffer ), ap_FpFlightSummary );  */\
                                    (void)FSfwrite( ap_SendBuffer, 1, strlen( ap_SendBuffer ), ap_FpMeas )

/** \desc Write one line of the summary data in data file and summary file. */
#define write_footer_line_summary( M, ... ) (void)ap_sprintf_safe( ap_SendBuffer, SEND_BUFFER_SIZE, M, ##__VA_ARGS__ ); \
                                    (void)FSfwrite( ap_SendBuffer, 1, strlen( ap_SendBuffer ), ap_FpMeas );

/*****************************************************************************/
/*                                FUNCTIONS                                  */
/*****************************************************************************/
inline void adc_init( void );
inline void timer_init( void );
inline void timer2_init( void );
inline void timer3_init( void );
void delay_ms( int ms );
void ServoSet( unsigned int periodTimeUs, unsigned int controlTimeUs );
inline void ServoStop( void );
inline void uart_init( void );
void uart_t( char* );
int uart_read( char*, int );
int ap_sprintf_safe( char *aOutput, int max_char, char *aInput, ... );
void kalman_filter( ap_KalmanData_t *data );
void io_init( void );
void write_header( FSFILE *fp_meas, ap_ConfigurationData_t *conf_data );
void writeInitialSummary( ap_summaryData_t *ap_Summary );
void writeSummary( ap_summaryData_t *ap_Summary, ap_Event_t *Event );
void error( int aErrNumber );
void warning(int aErrNumber);
void info( int aNumberOfBeeps );
void beep( int aDelay );
inline void buzzer_on( void );
inline void buzzer_off( void );
inline void led_on( void );
inline void led_off( void );
inline void led_toggle( void );
void nvm_CheckFlags( void );
void nvm_ConfDataReadAll( ap_ConfigurationData_t *conf_data );
int nvm_ConfDataGet( unsigned int configurationBitNumber );
void nvm_UpdateConfData( unsigned int configurationBitNumber, ap_ConfigurationData_t *conf_data );

#endif
