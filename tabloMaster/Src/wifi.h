/*
 * wifi.h
 *
 *  Created on: 29 сент. 2016 г.
 *      Author: IGOR
 */

#ifndef WIFI_H_
#define WIFI_H_

#include "main.h"
#include "string.h"

#define WIFI_RECIEVE_ARRAY_SIZE 300
#define JSON_TYPE_MAX_LENGTH	20
#define JSON_VALUE_MAX_LENGTH	20

#define Wifi_uart 	huart2
#define Wifi_timer	htim6

#define WIFI_RECEIVE_TIME_TRIGER 3000

extern char wifiRecieveBuffer [WIFI_RECIEVE_ARRAY_SIZE];
extern uint8_t wifiFlags;



//////////pererph init/////////
void MX_USART2_UART_Init (void);
void MX_TIM6_Init (void);

/////////user functions///////////////
void Wifi_parser (void);
void Wifi_data_update(void);
uint8_t Wifi_parser_get_value (const char *keyPtr, uint8_t outputStringMaxSize, char *outputArrPtr);
void uart2_start_recieve_trigger (uint8_t isNeedTurnOn);
uint8_t Wifi_string_copy(const char *sourcePtr, char *destPtr, uint8_t destSize);
void Wifi_get_time(char *strPtr, uint8_t arraySize);
void Wifi_void_function ();
void Wifi_init ();
enum wifiEvents
{
  DATA_UPDATE
};


#endif /* WIFI_H_ */
