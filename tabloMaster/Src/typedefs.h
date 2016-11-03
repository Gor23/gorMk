/*
 * typedefs.h
 *
 *  Created on: 23 ���. 2016 �.
 *      Author: IGOR
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

//don`t change!!!!!!!!!!!!!!!!!!
typedef struct
    {
	uint16_t size;
	uint16_t visibleRightEdge;	//visible to
	uint16_t visibleLeftEdge;	//visible from
	uint16_t xLength;			//bit (pixels)
	uint16_t yLength;			//byte (matrix)
	int16_t xOffset;				//x offset in bit
	int16_t yOffset;				//y offset in byte
	uint8_t *imageArrayPtr;		//pointer to array
    } Image;

typedef struct
    {
	uint16_t size;
	uint16_t xLength;			//bit (pixels)
	uint16_t yLength;			// byte (matrix)
	int16_t xOffset;
	int16_t yOffset;
	uint8_t writeFlag;
	uint8_t *bufferArrayPtr;
	uint8_t *readBufferArrayPointer;
    } VideoBuff;

typedef struct
    {
	int32_t stringShift;
	uint16_t visibleRightEdge;
	uint16_t visibleLeftEdge;
	uint16_t visibleDownEdge;
	uint16_t xOffset;
	uint16_t yOffset;
	uint8_t *stringPtr;
    } Text;

typedef struct
    {
	uint16_t visibleSymbols;
	uint16_t visibleRightEdge;
	uint16_t visibleLeftEdge;
	uint16_t xOffset;
	uint16_t yOffset;
	uint8_t *stringPtr;
    } textBuff;

enum processStatuses
    {
    BUFFER_OVERFLOW,
    NOT_COMPLETE,
    COMPLETE
    };

typedef struct
    {
	Text firsTeamName;
	Text secondTeamName;
	Text teamDevider;
	Text firstTeamScore;
	Text secondTeamScore;
	Text scoreDevider;
	Text firstTeamAdditional;
	Text secondTeamAdditional;
    } ScoreForm;

typedef enum
    {
    SIMPLE_FORM,
    EXTENDED_FORM
    } FormType;

typedef enum
    {
    FOOTBALL,
    TENNIS,
    BASKETBALL,
    HOCKEY
    } GameType;

    typedef enum
    {
	GOAL,
	UPDATE,
	POINT
    }ActionType;

    typedef enum
    {
	UNDEFINED,
	SYSTEM,
	GAME,
	WINNER,
	MESSAGE,
	HIDDEN,
	TIME
    }EventType;

    typedef enum
    {
    SYSTEM_LOGO,
	TIME_LOGO
    }LogoType;


#endif /* TYPEDEFS_H_ */
