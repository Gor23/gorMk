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

#define RECIEVE_ARRAY_SIZE	64

#include "string.h"
#include "fonts.h"
#include "images.h"
#include "events.h"

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

enum processStatuses
    {
    BUFFER_OVERFLOW,
    NOT_COMPLETE,
    COMPLETE
    };

typedef struct
    {
	text firsTeamName;
	text secondTeamName;
	text teamDevider;
	text firstTeamScore;
	text secondTeamScore;
	text scoreDevider;
	text firstTeamAdditional;
	text secondTeamAdditional;
    } ScoreForm;

typedef enum
    {
    SIMPLE_FORM,
    EXTENDED_FORM
    } FormType;

void Video_init(void);
void Video_change_buffers(uint8_t *firstBuff, uint8_t *secondBuff);
uint8_t Video_put_string(text *textStruct, const tChar *fonts);
void Video_move_string_left(text *textStruct, uint8_t step);
void Video_move_string_right(text *textStruct, uint8_t step);
uint8_t Video_put_n_move_string_left(text *textStruct, const tChar *fonts, uint8_t step);
void Video_put_image(image *imgPtr);
uint8_t *Video_put_string_fonts(uint8_t *text, const tChar *fonts);
void Video_put_and_move_string(uint8_t *text, const tChar *fonts);
uint8_t Video_put_image_edge(image *imgPtr);
void Video_move_image(image *imgPtr, uint16_t xMove, uint16_t yMove);
uint8_t Video_put_gif(imageGif *imgPtr, uint8_t invertFlag);
void Video_put_form(ScoreForm *form, FormType type);
void Video_send_data_to_display(void);
void Video_clear_trancieve_buffer(void);
void Video_cmd(uint8_t *comandPtr, uint16_t size);
char *Video_get_answer (void);
void Video_clear_recieve_buffer(void);

#endif /* STRINGS_H_ */
