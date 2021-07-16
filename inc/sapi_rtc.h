/*
 * sapi_rtc.h
 *
 *  Created on: 7 jul. 2021
 *      Author: MARCO
 */
#include <sapi_datatypes.h>
#include "chip.h"
#include "stdint.h"

#ifndef SAPI_RTC_H_
#define SAPI_RTC_H_

/*==================[macros and definitions]=================================*/

#define rtcConfig rtcInit

/*==================[typedef]================================================*/

typedef struct {
   uint16_t year;	 /* 1 to 4095 */
   uint8_t  month; 	 /* 1 to 12   */
   uint8_t  mday;	 /* 1 to 31   */
   uint8_t  wday;	 /* 1 to 7    */
   uint8_t  hour;	 /* 0 to 23   */
   uint8_t  min;	 /* 0 to 59   */
   uint8_t  sec;	 /* 0 to 59   */
} rtc_t;

/*==================[external functions declaration]=========================*/

/*
 * @Brief: Configure RTC peripheral.
 * @param  rtc_t rtc: RTC structure
 * @return bool_t true (1) if config it is ok
 */
bool_t rtcInit( void ); //rtc_t* rtc );

/*
 * @Brief: Get time from RTC peripheral.
 * @param  rtc_t rtc: RTC structure
 * @return bool_t true (1) if config it is ok
 */
bool_t rtcRead( rtc_t* rtc );

/*
 * @Brief: Set time on RTC peripheral.
 * @param  RTC_t rtc: RTC structure
 * @return bool_t true (1) if config it is ok
 */
bool_t rtcWrite( rtc_t* rtc );

#endif /* SAPI_RTC_H_ */
