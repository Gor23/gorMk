/*
 * strings.h
 *
 *  Created on: 1 июля 2016 г.
 *      Author: lihodey_i
 */

#ifndef VIDEO_H_
#define VIDEO_H_


#define ARRAY_SYMBOLS_OFFSET 32
#define RUS_ARRAY_OFFSRET 66


#define SPACE_WIDTH 1

#include "string.h"
#include "fonts.h"
#include "images.h"


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
} image;

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
} videoBuff;

typedef struct
{
	int32_t stringShift;
	uint16_t visibleRightEdge;
	uint16_t visibleLeftEdge;
	uint16_t visibleDownEdge;
	uint16_t xOffset;
	uint16_t yOffset;
	uint8_t *stringPtr;
} text;

typedef struct
{
	uint16_t visibleSymbols;
	uint16_t visibleRightEdge;
	uint16_t visibleLeftEdge;
	uint16_t xOffset;
	uint16_t yOffset;
	uint8_t *stringPtr;
} textBuff;

enum processStatuses {
	BUFFER_OVERFLOW, NOT_COMPLETE, COMPLETE
};




void Video_change_buffers (videoBuff *vbPtr, uint8_t *firstBuff, uint8_t *secondBuff);
uint8_t Video_put_string (text *textStruct, const tChar *fonts, videoBuff *videoBuffPtr);
void Video_move_string_left(text *textStruct, uint8_t step);
void Video_move_string_right(text *textStruct, uint8_t step);
uint8_t Video_put_n_move_string_left(text *textStruct, const tChar *fonts, uint8_t step, videoBuff *videoBuffPtr);
void Video_put_image (image *imgPtr, videoBuff *videoBuffPtr);
uint8_t *Video_put_string_fonts (uint8_t *text, const tChar *fonts, image *videoBuffPtr);
void Video_put_and_move_string (uint8_t *text, const tChar *fonts, image *videoBuffPtr);
uint8_t Video_put_image_edge (image *imgPtr, videoBuff *videoBuffPtr);
void Video_move_image (image *imgPtr, videoBuff *videoBuffPtr, uint16_t xMove, uint16_t yMove);
uint8_t Video_put_gif (imageGif *imgPtr, videoBuff *videoBuffPtr, uint8_t invertFlag);

#endif /* STRINGS_H_ */
