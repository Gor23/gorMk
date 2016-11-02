/*
 * fonts.h
 *
 *  Created on: 11 июля 2016 г.
 *      Author: IGOR
 */

#ifndef FONTS_H_
#define FONTS_H_

#include <stdint.h>
#include "main.h"

typedef struct
{
   const uint8_t *arrayPointer;
   const uint8_t width;
   const uint8_t height;
 } tImage;

typedef struct
{
   const uint8_t charCode;
   const tImage *image;
 } tChar;

extern const tChar Font3_array[];
extern const tChar Font_array[];
extern const tChar Font2_array[];
extern const tChar FontSmall_array[];

#endif /* FONTS_H_ */
