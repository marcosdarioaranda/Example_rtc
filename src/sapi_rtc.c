/*
 * sapi_rtc.c
 *
 *  Created on: 7 jul. 2021
 *      Author: MARCO
 */





/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
#include <sapi_rtc.h>
#include "chip.h"
#include "stdint.h"
#include <sapi_delay.h>
/*
 * @Brief: Configure RTC peripheral.
 * @param  rtc_t rtc: RTC structure
 * @return bool_t true (1) if config it is ok
 */
bool_t rtcInit( void )
{


   bool_t ret_val = 1;
/*
   static bool_t init;

   if( init ){
      // Already initialized
      ret_val = 0;
   } else {
*/
      /* RTC Block section ------------------------- */
      Chip_RTC_Init(LPC_RTC);

      /* Set current time for RTC */
      /* Current time is 22:00:00 , 2016-07-02 */

   /*
      RTC_TIME_T rtcTime;
      rtcTime.time[RTC_TIMETYPE_SECOND]     = 0;
      rtcTime.time[RTC_TIMETYPE_MINUTE]     = 0;
      rtcTime.time[RTC_TIMETYPE_HOUR]       = 0;
      rtcTime.time[RTC_TIMETYPE_DAYOFWEEK]  = 0;
      rtcTime.time[RTC_TIMETYPE_DAYOFMONTH] = 0;
      rtcTime.time[RTC_TIMETYPE_MONTH]      = 0;
      rtcTime.time[RTC_TIMETYPE_YEAR]       = 0;
      Chip_RTC_SetFullTime(LPC_RTC, &rtcTime);
      */


      //rtcWrite( rtc );

      /* Enable rtc (starts increase the tick counter
         and second counter register) */
      Chip_RTC_Enable(LPC_RTC, ENABLE);


      delayMs(0, 2100);

      //init = 1;
   //}

   return ret_val;
}

/*
 * @Brief: Get time from RTC peripheral.
 * @param  rtc_t rtc: RTC structure
 * @return bool_t true (1) if config it is ok
 */
bool_t rtcRead( rtc_t * rtc )
{
   bool_t ret_val = 1;

   RTC_TIME_T rtcTime;

   Chip_RTC_GetFullTime(LPC_RTC, &rtcTime);

   rtc->sec = rtcTime.time[RTC_TIMETYPE_SECOND];
   rtc->min = rtcTime.time[RTC_TIMETYPE_MINUTE];
   rtc->hour = rtcTime.time[RTC_TIMETYPE_HOUR];
   rtc->wday = rtcTime.time[RTC_TIMETYPE_DAYOFWEEK];
   rtc->mday = rtcTime.time[RTC_TIMETYPE_DAYOFMONTH];
   rtc->month = rtcTime.time[RTC_TIMETYPE_MONTH];
   rtc->year = rtcTime.time[RTC_TIMETYPE_YEAR];

   return ret_val;
}

/*
 * @Brief: Set time on RTC peripheral.
 * @param  rtc_t rtc: RTC structure
 * @return bool_t true (1) if config it is ok
 */
bool_t rtcWrite( rtc_t * rtc )
{
   bool_t ret_val = 1;

   RTC_TIME_T rtcTime;

   rtcTime.time[RTC_TIMETYPE_SECOND]     = rtc->sec;
   rtcTime.time[RTC_TIMETYPE_MINUTE]     = rtc->min;
   rtcTime.time[RTC_TIMETYPE_HOUR]       = rtc->hour;
   rtcTime.time[RTC_TIMETYPE_DAYOFWEEK]  = rtc->wday;
   rtcTime.time[RTC_TIMETYPE_DAYOFMONTH] = rtc->mday;
   rtcTime.time[RTC_TIMETYPE_MONTH]      = rtc->month;
   rtcTime.time[RTC_TIMETYPE_YEAR]	     = rtc->year;

   Chip_RTC_SetFullTime(LPC_RTC, &rtcTime);

   return ret_val;
}
