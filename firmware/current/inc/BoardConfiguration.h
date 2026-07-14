#ifndef BOARD_CONFIGURATION_H
#define BOARD_CONFIGURATION_H

#define BOARD_2_2

#ifdef BOARD_2_2 // project date 2016.03.30
        // define I/O
        #define ACC_CS                  _LATC14
        #define TRIS_ACC_CS             _TRISC14
        #define HACC_CS                 _LATD8
        #define TRIS_HACC_CS            _TRISD8
        #define OUT1                    _LATB9
        #define OUT2                    _LATB8
        #define OUT3                    _LATB7
        #define TRIS_OUT1               _TRISB9
        #define TRIS_OUT2               _TRISB8
        #define TRIS_OUT3               _TRISB7
        #define BUZZER                  _LATB10
        #define TRIS_BUZZER             _TRISB10
        #define LED_RED                 _LATD1
        #define TRIS_LED                _TRISD1
        #define IGN_TEST                _LATG9
        #define TRIS_IGN_TEST           _TRISG9
        #define CONF_SEL1               _RD5
        #define CONF_SEL1_PUE           _CN14PUE
        #define CONF_SEL2               _RD4
        #define CONF_SEL2_PUE           _CN13PUE

        // define remappable pins
        #define RP_I_SPI_MISO           14
        #define RP_O_SPI_MOSI           _RP16R
        #define RP_O_SPI_SCK            _RP29R
        #define RP_I_SENSE_SPI_MISO     11
        #define RP_O_SENSE_SPI_MOSI     _RP4R
        #define RP_O_SENSE_SPI_SCK      _RP3R
        #define RP_I_UART_RX            23
        #define RP_O_UART_TX            _RP22R
        #define RP_O_PWM_1              _RP18R

#elif defined BOARD_2_0 // project date 2014.08.17
        // define I/O
        #define ACC_CS                  _LATC14
        #define TRIS_ACC_CS             _TRISC14
        #define HACC_CS                 _LATD8
        #define TRIS_HACC_CS            _TRISD8
        #define OUT1                    _LATB9
        #define OUT2                    _LATB8
        #define OUT3                    _LATB7
        #define TRIS_OUT1               _TRISB9
        #define TRIS_OUT2               _TRISB8
        #define TRIS_OUT3               _TRISB7
        #define BUZZER                  _LATB10
        #define TRIS_BUZZER             _TRISB10
        #define LED_RED                 _LATD1
        #define TRIS_LED                _TRISD1
        #define IGN_TEST                _LATG9
        #define TRIS_IGN_TEST           _TRISG9
        #define CONF_SEL1               _RD5
        #define CONF_SEL1_PUE           _CN14PUE
        #define CONF_SEL2               _RD4
        #define CONF_SEL2_PUE           _CN13PUE

        // define remappable pins
        #define RP_I_SPI_MISO           14
        #define RP_O_SPI_MOSI           _RP16R
        #define RP_O_SPI_SCK            _RP29R
        #define RP_I_SENSE_SPI_MISO     11
        #define RP_O_SENSE_SPI_MOSI     _RP4R
        #define RP_O_SENSE_SPI_SCK      _RP3R
        #define RP_I_UART_RX            23
        #define RP_O_UART_TX            _RP22R

#elif defined BOARD_0_9 // project date 2013.08.12
        // define I/O
        #define ACC_CS                  _LATB13
        #define TRIS_ACC_CS             _TRISB13
        #define HACC_CS                 _LATB12
        #define TRIS_HACC_CS            _TRISB12
        #define OUT1                    _LATA4
        #define OUT2                    _LATB4
        #define OUT3                    _LATA8
        #define TRIS_OUT1               _TRISA4
        #define TRIS_OUT2               _TRISB4
        #define TRIS_OUT3               _TRISA8
        #define BUZZER                  _LATA9
        #define TRIS_BUZZER             _TRISA9
        #define LED_RED                 _LATA10
        #define TRIS_LED                _TRISA10
        #define IGN_TEST                _LATB3
        #define TRIS_IGN_TEST           _TRISB3
        #define CONF_SEL1               _RC5
        #define CONF_SEL1_PUE           _CN26PUE
        #define CONF_SEL2               _RC4
        #define CONF_SEL2_PUE           _CN25PUE
        
        // define remappable pins
        #define RP_I_SPI_MISO           22
        #define RP_O_SPI_MOSI           _RP24R
        #define RP_O_SPI_SCK            _RP23R
        #define RP_I_UART_RX            1
        #define RP_O_UART_TX            _RP0R

#elif defined BOARD_0_8 // project date 2013.06.24
        // define I/O
        #define ACC_CS                  _LATB13
        #define TRIS_ACC_CS             _TRISB13
        #define HACC_CS                 _LATB12
        #define TRIS_HACC_CS            _TRISB12
        #define OUT1                    _LATA4
        #define OUT2                    _LATB4
        #define OUT3                    _LATA8
        #define TRIS_OUT1               _TRISA4
        #define TRIS_OUT2               _TRISB4
        #define TRIS_OUT3               _TRISA8
        #define BUZZER                  _LATA9
        #define TRIS_BUZZER             _TRISA9
        #define LED_RED                 _LATA10
        #define TRIS_LED                _TRISA10
        #define IGN_TEST                _LATB3
        #define TRIS_IGN_TEST           _TRISB3
        #define CONF_SEL1               _RC5
        #define CONF_SEL1_PUE           _CN26PUE
        #define CONF_SEL2               _RC4
        #define CONF_SEL2_PUE           _CN25PUE
        
        // define remappable pins
        #define RP_I_SPI_MISO           22
        #define RP_O_SPI_MOSI           _RP24R
        #define RP_O_SPI_SCK            _RP23R
        #define RP_I_UART_RX            1
        #define RP_O_UART_TX            _RP0R

#elif defined BOARD_0_7        // project date 2012.03.11
        // define I/O
        #define ACC_CS                  _LATA10
        #define TRIS_ACC_CS             _TRISA10
        #define HACC_CS                 _LATA7
        #define TRIS_HACC_CS            _TRISA7
        #define OUT1                    _LATC3
        #define OUT2                    _LATA9
        #define OUT3                    _LATB4
        #define TRIS_OUT1               _TRISC3
        #define TRIS_OUT2               _TRISA9
        #define TRIS_OUT3               _TRISB4
        #define BUZZER                  _LATB12
        #define TRIS_BUZZER             _TRISB12
        #define LED_RED                 _LATA8
        #define TRIS_LED                _TRISA8
        #define IGN_TEST                _LATA4
        #define TRIS_IGN_TEST           _TRISA4
        
        // define remappable pins
        #define RP_I_SPI_MISO           22
        #define RP_O_SPI_MOSI           _RP24R
        #define RP_O_SPI_SCK            _RP23R
        #define RP_I_UART_RX            11
        #define RP_O_UART_TX            _RP10R

#endif

#endif
