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

ScoreForm scoreForm;



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
    eventData.eventType = UNDEFINED;
    }

void Event_set_n_display_score(FormType type)
    {
    switch (type)
	{
    case SIMPLE_FORM:
	scoreForm.firsTeamName.xOffset = FIRST_TEAM_NAME_X_OFFSET;
	scoreForm.firsTeamName.visibleLeftEdge = 0;
	scoreForm.firsTeamName.yOffset = TEAM_NAME_Y_OFFSET;
	scoreForm.firsTeamName.stringShift = 0;
	scoreForm.firsTeamName.visibleRightEdge = FIRST_TEAM_NAME_RIGHT_VISIBLE_EDGE;
	scoreForm.firsTeamName.stringPtr = gameData.firstTeam;

	scoreForm.teamDevider.xOffset = TEAM_DEVIDER_X_OFFSET;
	scoreForm.teamDevider.yOffset = TEAM_NAME_Y_OFFSET;
	scoreForm.teamDevider.stringShift = 0;
	scoreForm.teamDevider.visibleRightEdge = TEAM_DEVIDER_X_OFFSET + 10; //TODO remake to symbol width calculate
	scoreForm.teamDevider.stringPtr = (uint8_t*)"-";

	scoreForm.secondTeamName.xOffset = SECOND_TEAM_NAME_X_OFFSET;	//TODO align to left edge
	scoreForm.secondTeamName.yOffset = TEAM_NAME_Y_OFFSET;
	scoreForm.secondTeamName.stringShift = 0;
	scoreForm.secondTeamName.visibleRightEdge = SECOND_TEAM_NAME_RIGHT_VISIBLE_EDGE;
	scoreForm.secondTeamName.stringPtr = gameData.secondTeam;

	scoreForm.firstTeamScore.xOffset = FIRST_TEAM_SCORE_X_OFFSET;
	scoreForm.firstTeamScore.yOffset = TEAM_SCORE_Y_OFFSET;
	scoreForm.firstTeamScore.stringShift = 0;
	scoreForm.firstTeamScore.visibleRightEdge = FIRST_TEAM_SCORE_RIGHT_VISIBLE_EDGE;
	scoreForm.firstTeamScore.stringPtr = gameData.firstTeamScore;

	scoreForm.scoreDevider.xOffset = SCORE_DEVIDER_X_OFFSET;
	scoreForm.scoreDevider.yOffset = TEAM_SCORE_Y_OFFSET;
	scoreForm.scoreDevider.stringShift = 0;
	scoreForm.scoreDevider.visibleRightEdge = SCORE_DEVIDER_X_OFFSET + 20;//TODO remake to symbol width calculate
	scoreForm.scoreDevider.stringPtr = (uint8_t*)":";

	scoreForm.secondTeamScore.xOffset = SECOND_TEAM_SCORE_X_OFFSET;	//TODO align to left edge
	scoreForm.secondTeamScore.yOffset = TEAM_SCORE_Y_OFFSET;
	scoreForm.secondTeamScore.stringShift = 0;
	scoreForm.secondTeamScore.visibleRightEdge = SECOND_TEAM_SCORE_RIGHT_VISIBLE_EDGE;
	scoreForm.secondTeamScore.stringPtr = gameData.secondTeamScore;

	Video_put_form(&scoreForm, type);			//TODO realize method
	break;

    case EXTENDED_FORM:
	scoreForm.firsTeamName.xOffset = EXT_FIRST_TEAM_NAME_X_OFFSET;
	scoreForm.firsTeamName.yOffset = EXT_TEAM_NAME_Y_OFFSET;
	scoreForm.firsTeamName.stringShift = 0;
	scoreForm.firsTeamName.visibleRightEdge = EXT_FIRST_TEAM_NAME_RIGHT_VISIBLE_EDGE;
	scoreForm.firsTeamName.visibleLeftEdge = 0;
	scoreForm.firsTeamName.stringPtr = gameData.firstTeam;

	scoreForm.teamDevider.xOffset = EXT_TEAM_DEVIDER_X_OFFSET;
	scoreForm.teamDevider.yOffset = EXT_TEAM_NAME_Y_OFFSET;
	scoreForm.teamDevider.stringShift = 0;
	scoreForm.teamDevider.visibleRightEdge = EXT_TEAM_DEVIDER_X_OFFSET + 10; //TODO remake to symbol width calculate
	scoreForm.teamDevider.stringPtr = (uint8_t*)"-";

	scoreForm.secondTeamName.xOffset = EXT_SECOND_TEAM_NAME_X_OFFSET;	//TODO align to left edge
	scoreForm.secondTeamName.yOffset = EXT_TEAM_NAME_Y_OFFSET;
	scoreForm.secondTeamName.stringShift = 0;
	scoreForm.secondTeamName.visibleRightEdge = EXT_SECOND_TEAM_NAME_RIGHT_VISIBLE_EDGE;
	scoreForm.secondTeamName.stringPtr = gameData.secondTeam;

	scoreForm.firstTeamScore.xOffset = EXT_FIRST_TEAM_SCORE_X_OFFSET;
	scoreForm.firstTeamScore.yOffset = EXT_TEAM_SCORE_Y_OFFSET;
	scoreForm.firstTeamScore.visibleLeftEdge = 0;
	scoreForm.firstTeamScore.stringShift = 0;
	scoreForm.firstTeamScore.visibleRightEdge = EXT_FIRST_TEAM_SCORE_RIGHT_VISIBLE_EDGE;
	scoreForm.firstTeamScore.stringPtr = gameData.firstTeamScore;

	scoreForm.scoreDevider.xOffset = EXT_SCORE_DEVIDER_X_OFFSET;
	scoreForm.scoreDevider.yOffset = EXT_TEAM_SCORE_Y_OFFSET;
	scoreForm.scoreDevider.stringShift = 0;
	scoreForm.scoreDevider.visibleRightEdge = EXT_SCORE_DEVIDER_X_OFFSET + 10;//TODO remake to symbol width calculate
	scoreForm.scoreDevider.stringPtr = (uint8_t*)":";

	scoreForm.secondTeamScore.xOffset = EXT_SECOND_TEAM_SCORE_X_OFFSET;	//TODO align to left edge
	scoreForm.secondTeamScore.yOffset = EXT_TEAM_SCORE_Y_OFFSET;
	scoreForm.secondTeamScore.stringShift = 0;
	scoreForm.secondTeamScore.visibleRightEdge = EXT_SECOND_TEAM_SCORE_RIGHT_VISIBLE_EDGE;
	scoreForm.secondTeamScore.stringPtr = gameData.secondTeamScore;

	scoreForm.firstTeamAdditional.xOffset = EXT_FIRST_TEAM_ADD_SCORE_X_OFFSET;
	scoreForm.firstTeamAdditional.yOffset = EXT_TEAM_SCORE_ADD_Y_OFFSET;
	scoreForm.firstTeamAdditional.stringShift = 0;
	scoreForm.firstTeamAdditional.visibleRightEdge = EXT_FIRST_TEAM_ADD_SCORE_RIGHT_VISIBLE_EDGE;
	scoreForm.firstTeamAdditional.stringPtr = gameData.additionalFirstTeamScore;

	scoreForm.secondTeamAdditional.xOffset = EXT_SECOND_TEAM_ADD_SCORE_X_OFFSET;
	scoreForm.secondTeamAdditional.yOffset = EXT_TEAM_SCORE_ADD_Y_OFFSET;
	scoreForm.secondTeamAdditional.stringShift = 0;
	scoreForm.secondTeamAdditional.visibleRightEdge = EXT_SECOND_TEAM_ADD_SCORE_RIGHT_VISIBLE_EDGE;
	scoreForm.secondTeamAdditional.visibleLeftEdge = 64;
	scoreForm.secondTeamAdditional.stringPtr = gameData.additionalSecondTeamScore;

	Video_put_form(&scoreForm, type);			//TODO realize method
	break;
	}
    }

//void Events_put_commands_names()

