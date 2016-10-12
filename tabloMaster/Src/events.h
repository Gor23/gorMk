/*
 * events.h
 *
 *  Created on: 12 окт. 2016 г.
 *      Author: IGOR
 */

#ifndef EVENTS_H_
#define EVENTS_H_

#include <stdint.h>

#define MAX_EVENT_STRING_SIZE 30

typedef struct {

  uint8_t firstTeam [MAX_EVENT_STRING_SIZE];
  uint8_t secondTeam [MAX_EVENT_STRING_SIZE];
  uint8_t firstTeamScore;
  uint8_t secondTeamScore;
  uint8_t additionalFirstTeamScore;
  uint8_t additionalSecondTeamScore;

} GameData;

typedef struct {

  uint8_t eventType [MAX_EVENT_STRING_SIZE];
  uint8_t eventMessage [MAX_EVENT_STRING_SIZE];

} EventData;

GameData gameData;
EventData eventData;

#endif /* EVENTS_H_ */
