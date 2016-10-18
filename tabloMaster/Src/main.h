/*
 * main.h
 *
 *  Created on: 31 мая 2016 г.
 *      Author: IGOR
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include "stm32f1xx_hal.h"

#define false 0
#define true 1

#define UART_SPEED 256000

#define xMatrix	2
#define yMatrix 2



#define TRANCIEVE_ARRAY_SIZE 	256*xMatrix*yMatrix
#define RECIEVE_BUFFER_SIZE 	10

#define TEXT_BUF_SIZE 		1024
#define COMM_TEXT_BUF_SIZE 	256
#define SYSTEM_TEXT_BUF_SIZE	256
#define STRING_BUF_SIZE 	512

#define TIMER_1_STOP_VALUE	100
#define TIMER_2_STOP_VALUE	200

#define	HUART4_RECIEVE_TIMEOUT 70

#define NO_ANSWER_TIMEOUT 20

enum modes {
	LOGO_MODE, SCORE_MODE, GOAL_MODE, STRING_MODE, TEST_MODE, WINNER_MODE, POINT_MODE
};

enum driverStatus {
	INIT, CHANGE_BUFER, ANSWER_CHECK, SEND_DATA, WAIT_FOR_DATA_IS_SEND
};

extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart2;

extern volatile uint32_t timer1;
extern volatile uint32_t timer2;
extern volatile uint16_t driverTimer;
extern volatile uint16_t timerStopValue;
extern volatile uint8_t ready;
extern volatile uint8_t dmaSend;

#endif /* MAIN_H_ */

