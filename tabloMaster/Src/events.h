/*
 * events.h
 *
 *  Created on: 12 окт. 2016 г.
 *      Author: IGOR
 */

#ifndef EVENTS_H_
#define EVENTS_H_

#include <stdint.h>
#include "video.h"
#include "main.h"

#define MAX_EVENT_STRING_SIZE 30
#define MAX_EVENT_STRING_SCORE_SIZE 5

typedef struct
    {

	uint8_t firstTeam[MAX_EVENT_STRING_SIZE];
	uint8_t secondTeam[MAX_EVENT_STRING_SIZE];
	uint8_t actionType[MAX_EVENT_STRING_SIZE];
	uint8_t firstTeamScore[MAX_EVENT_STRING_SCORE_SIZE];
	uint8_t secondTeamScore[MAX_EVENT_STRING_SCORE_SIZE];
	uint8_t additionalFirstTeamScore[MAX_EVENT_STRING_SCORE_SIZE];
	uint8_t additionalSecondTeamScore[MAX_EVENT_STRING_SCORE_SIZE];

    } GameData;

typedef struct
    {

	uint8_t eventType[MAX_EVENT_STRING_SIZE];
	uint8_t eventMessage[MAX_EVENT_STRING_SIZE];

    } EventData;



GameData gameData;
EventData eventData;

void Events_clear_strings_game_data(void);
void Events_clear_strings_event_data(void);

#endif /* EVENTS_H_ */
