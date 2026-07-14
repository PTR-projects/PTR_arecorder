#ifndef __dbg_h__
#define __dbg_h__

#define log_err(M, ...)         ap_sprintf_safe( ap_BufferError, BUFFER_ERROR_SIZE,                             \
                                "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__ );      \
                                uart_t( ap_BufferError )

#define log_sd_err(M, ...)      ap_sprintf_safe( ap_BufferError, BUFFER_ERROR_SIZE,                             \
                                "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__ )/*;      \
                                FSfwrite( ap_BufferError, 1, strlen( ap_BufferError ), ap_FpFlightSummary );    \
                                FSfsync( ap_FpFlightSummary )*/

#define log_warn(M, ...)        ap_sprintf_safe( ap_BufferError, BUFFER_ERROR_SIZE,                             \
                                "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__ );       \
                                uart_t( ap_BufferError )

#define log_sd_warn(M, ...)     ap_sprintf_safe( ap_BufferError, BUFFER_ERROR_SIZE,                             \
                                "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__ )/*;       \
                                FSfwrite( ap_BufferError, 1, strlen( ap_BufferError ), ap_FpFlightSummary );    \
                                FSfsync( ap_FpFlightSummary )*/

#define log_info(M, ...)        ap_sprintf_safe( ap_BufferError, BUFFER_ERROR_SIZE,                             \
                                "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__ );                  \
                                uart_t( ap_BufferError )

#define log_sd_info(M, ...)     ap_sprintf_safe( ap_BufferError, BUFFER_ERROR_SIZE,                             \
                                "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__ )/*;                  \
                                FSfwrite( ap_BufferError, 1, strlen( ap_BufferError ), ap_FpFlightSummary );    \
                                FSfsync( ap_FpFlightSummary )*/

#define check(A, M, ...)        if( !(A) ) { log_err( M, ##__VA_ARGS__ ); goto error; }
#define check_sd(A, M, ...)     if( !(A) ) { log_sd_err( M, ##__VA_ARGS__ ); goto error; }

#define sentinel(M, ...)        { log_err( M, ##__VA_ARGS__ ); goto error; }

#define check_mem(A)            check( (A), "Out of memory." )

#define check_debug(A, M, ...)  if( !(A) ) { DEBUG( M, ##__VA_ARGS__ ); goto error; }

#endif
