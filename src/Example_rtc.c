/*
===============================================================================
 Name        : Example_rtc.c
 Author      : Ms. Ing. Marcos D. Aranda
 Version     : 1.0
 Copyright   : $(copyright)
 Description : Este ejemplo utilizada el reloj de tiempo real RTC de la placa LPC1769.
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include <sapi_rtc.h>
#include <sapi_gpio.h>
#include <sapi_delay.h>
#include <sapi_uart.h>
#include "itoa.h"

/* Buffer */
static char uartBuff[10];

/* Enviar fecha y hora en formato "DD/MM/YYYY, HH:MM:SS" */
void showDateAndTime( rtc_t * rtc ){

	/* Conversión de entero a ascii con base decimal */
   itoa( (int) (rtc->mday), (char*)uartBuff, 10 ); /* 10 significa decimal */
   /* Envio el dia */
   if( (rtc->mday)<10 ){
      uartWriteByte( UART_3, '0' );
	  uartWriteString( UART_3, uartBuff );
	  uartWriteByte( UART_3, '/' );
   }
   /* Conversión de entero a ascii con base decimal */
   itoa( (int) (rtc->month), (char*)uartBuff, 10 ); /* 10 significa decimal */
   /* Envio el mes */
   if( (rtc->month)<10 ){
      uartWriteByte( UART_3, '0' );
   	  uartWriteString( UART_3, uartBuff );
   	  uartWriteByte( UART_3, '/' );
   }
   /* Conversión de entero a ascii con base decimal */
   itoa( (int) (rtc->year), (char*)uartBuff, 10 ); /* 10 significa decimal */
   /* Envio el año */
   if( (rtc->year)<10 ){
      uartWriteByte( UART_3, '0' );
      uartWriteString( UART_3, uartBuff );

   }
      uartWriteString( UART_3, ", ");


   /* Conversión de entero a ascii con base decimal */
   itoa( (int) (rtc->hour), (char*)uartBuff, 10 ); /* 10 significa decimal */
   /* Envio la hora */
   if( (rtc->hour)<10 ){
      uartWriteByte( UART_3, '0' );
      uartWriteString( UART_3, uartBuff );
      uartWriteByte( UART_3, ':' );
   }
   /* Conversión de entero a ascii con base decimal */
   itoa( (int) (rtc->min), (char*)uartBuff, 10 ); /* 10 significa decimal */
   /* Envio los minutos */
   if( (rtc->min)<10 ){
      uartWriteByte( UART_3, '0' );
      uartWriteString( UART_3, uartBuff );
      uartWriteByte( UART_3, ':' );
   }
   /* Conversión de entero a ascii con base decimal */
   itoa( (int) (rtc->sec), (char*)uartBuff, 10 ); /* 10 significa decimal */
   /* Envio los segundos */
   if( (rtc->sec)<10 ){
      uartWriteByte( UART_3, '0' );
      uartWriteString( UART_3, uartBuff );
   }

   /* Envio un 'enter' */
      uartWriteString( UART_3, "\r\n");
}
// TODO: insert other definitions and declarations here

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

    // TODO: insert code here
    /*Inicializo la UART3 a 115200 baudios*/
    uartInit( UART_3, 115200 );

       /* Estructura RTC */
       rtc_t rtc;

       rtc.year = 2016;
       rtc.month = 7;
       rtc.mday = 3;
       rtc.wday = 1;
       rtc.hour = 14;
       rtc.min = 30;
       rtc.sec = 0;

       bool_t val = 0;
       uint8_t i = 0;

       uartWriteString( UART_3, "Inicializar RTC\r\n" );
       /* Inicializar RTC */
       rtcInit();

       uartWriteString( UART_3, "Establecer fecha y hora\r\n" );
       /* Establecer fecha y hora*/
       rtcWrite( &rtc );

       /*El RTC tarda en setear la hora, por eso el delay*/
       delaySec(0,2);

       for( i=0; i<10; i++ ){
          /* Leer fecha y hora */
          val = rtcRead( &rtc );
          /* Mostrar fecha y hora en formato "DD/MM/YYYY, HH:MM:SS" */
          showDateAndTime( &rtc );
          delaySec(0,1);
       }

       rtc.year = 2021;
       rtc.month = 7;
       rtc.mday = 7;
       rtc.wday = 1;
       rtc.hour = 21;
       rtc.min = 20;
       rtc.sec= 0;

       /* Establecer fecha y hora */
       uartWriteString( UART_3, "Establecer fecha y hora\r\n" );
       val = rtcWrite( &rtc );

       /* ------------- REPETIR POR SIEMPRE ------------- */
       while(1) {

             val = rtcRead( &rtc );
             if(val){
             /* Mostrar fecha y hora en formato "DD/MM/YYYY, HH:MM:SS" */
             showDateAndTime( &rtc );
             delaySec(0, 1);
             }
       }

       /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
          por ningun S.O. */
       return 0 ;
    }
