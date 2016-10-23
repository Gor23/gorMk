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
#include "typedefs.h"

void Video_init(void);
void Video_change_buffers(uint8_t *firstBuff, uint8_t *secondBuff);
uint8_t Video_put_string(Text *textStruct, const tChar *fonts);
void Video_move_string_left(Text *textStruct, uint8_t step);
void Video_move_string_right(Text *textStruct, uint8_t step);
uint8_t Video_put_n_move_string_left(Text *textStruct, const tChar *fonts, uint8_t step);
void Video_put_image(Image *imgPtr);
uint8_t *Video_put_string_fonts(uint8_t *text, const tChar *fonts);
void Video_put_and_move_string(uint8_t *text, const tChar *fonts);
uint8_t Video_put_image_edge(Image *imgPtr);
void Video_move_image(Image *imgPtr, uint16_t xMove, uint16_t yMove);
uint8_t Video_put_gif(imageGif *imgPtr, uint8_t invertFlag);
void Video_put_form(ScoreForm *form, FormType type);
void Video_send_data_to_display(void);
void Video_clear_trancieve_buffer(void);
void Video_cmd(uint8_t *comandPtr, uint16_t size);
char *Video_get_answer (void);
void Video_clear_recieve_buffer(void);
void Video_send_init_to_display(uint8_t *comandPtr, uint16_t size);
void Video_align_for_right_side(Text *text,  const tChar *fonts);

#endif /* STRINGS_H_ */
