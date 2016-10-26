/*
 * events.h
 *
 *  Created on: 12 окт. 2016 г.
 *      Author: IGOR
 */

#ifndef EVENTS_H_
#define EVENTS_H_

#include <stdint.h>
#include "typedefs.h"
#include "main.h"

#define MAX_EVENT_STRING_SIZE 30
#define MAX_EVENT_STRING_SCORE_SIZE 5

#define FIRST_TEAM_NAME_X_OFFSET		0
#define TEAM_NAME_Y_OFFSET			6
#define FIRST_TEAM_NAME_RIGHT_VISIBLE_EDGE	TEAM_DEVIDER_X_OFFSET - 1
#define TEAM_DEVIDER_X_OFFSET			X_PIXELS/2-2 	// TODO choose correct value
#define SECOND_TEAM_NAME_X_OFFSET		X_PIXELS/2+4
#define SECOND_TEAM_NAME_RIGHT_VISIBLE_EDGE	X_PIXELS

#define FIRST_TEAM_SCORE_X_OFFSET		0
#define TEAM_SCORE_Y_OFFSET			0
#define FIRST_TEAM_SCORE_RIGHT_VISIBLE_EDGE	SCORE_DEVIDER_X_OFFSET - 1
#define SCORE_DEVIDER_X_OFFSET			X_PIXELS/2-8 	// TODO choose correct value
#define SECOND_TEAM_SCORE_X_OFFSET	   	X_PIXELS/2+6
#define SECOND_TEAM_SCORE_RIGHT_VISIBLE_EDGE	X_PIXELS


#define EXT_FIRST_TEAM_NAME_X_OFFSET			0
#define EXT_TEAM_NAME_Y_OFFSET				6
#define EXT_FIRST_TEAM_NAME_RIGHT_VISIBLE_EDGE		TEAM_DEVIDER_X_OFFSET - 1
#define EXT_TEAM_DEVIDER_X_OFFSET			X_PIXELS/2-2 	// TODO choose correct value
#define EXT_SECOND_TEAM_NAME_X_OFFSET			X_PIXELS/2+4
#define EXT_SECOND_TEAM_NAME_RIGHT_VISIBLE_EDGE		X_PIXELS

#define EXT_FIRST_TEAM_SCORE_X_OFFSET			0
#define EXT_TEAM_SCORE_Y_OFFSET				1
#define EXT_FIRST_TEAM_SCORE_RIGHT_VISIBLE_EDGE		SCORE_DEVIDER_X_OFFSET - 1
#define EXT_SCORE_DEVIDER_X_OFFSET			X_PIXELS/2-6 	// TODO choose correct value
#define EXT_SECOND_TEAM_SCORE_X_OFFSET	   		X_PIXELS/2+10
#define EXT_SECOND_TEAM_SCORE_RIGHT_VISIBLE_EDGE	X_PIXELS

#define	EXT_FIRST_TEAM_ADD_SCORE_X_OFFSET		0
#define	EXT_TEAM_SCORE_ADD_Y_OFFSET			0
#define	EXT_FIRST_TEAM_ADD_SCORE_RIGHT_VISIBLE_EDGE	16
#define	EXT_SECOND_TEAM_ADD_SCORE_X_OFFSET		64		//align to right edge
#define EXT_SECOND_TEAM_ADD_SCORE_RIGHT_VISIBLE_EDGE	X_PIXELS

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

	EventType eventType;
	uint8_t eventMessage[MAX_EVENT_STRING_SIZE];

    } EventData;



extern GameData gameData;
extern EventData eventData;

void Events_clear_strings_game_data(void);
void Events_clear_strings_event_data(void);
void Event_set_n_display_score(FormType type);

#endif /* EVENTS_H_ */
