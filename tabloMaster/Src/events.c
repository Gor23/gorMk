/*
 * events.c
 *
 *  Created on: 12 окт. 2016 г.
 *      Author: IGOR
 */
#include "events.h"
#include <string.h>

GameData gameData;
EventData eventData;

void Events_clear_strings_game_data(void)
    {
    memset(&gameData.firstTeam, 0, MAX_EVENT_STRING_SIZE);
    memset(&gameData.secondTeam, 0, MAX_EVENT_STRING_SIZE);
    memset(&gameData.actionType, 0, MAX_EVENT_STRING_SIZE);
    memset(&gameData.firstTeamScore, 0, MAX_EVENT_STRING_SIZE);
    memset(&gameData.secondTeamScore, 0, MAX_EVENT_STRING_SIZE);
    memset(&gameData.additionalFirstTeamScore, 0, MAX_EVENT_STRING_SIZE);
    memset(&gameData.additionalSecondTeamScore, 0, MAX_EVENT_STRING_SIZE);
    }

void Events_clear_strings_event_data(void)
    {
    memset(&eventData.eventMessage, 0, MAX_EVENT_STRING_SIZE);
    memset(&eventData.eventType, 0, MAX_EVENT_STRING_SIZE);
    }


