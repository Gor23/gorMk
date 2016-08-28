/*
 * images.h
 *
 *  Created on: 17 июля 2016 г.
 *      Author: IGOR
 */

#ifndef IMAGES_H_
#define IMAGES_H_

#include <stdint.h>

typedef struct
{
   const uint8_t *imageArrayPtr;		//pointer to array
   uint16_t frameSize;
   uint16_t xLength;
   int16_t xOffset;				//x offset in bit
   int16_t yOffset;				//y offset in byte
   uint8_t yLength;
   uint8_t frames;
   uint8_t currentFrame;
   uint8_t repeats;
   uint8_t repeatsFrom;
} imageGif;

extern const uint8_t goal[];
extern const uint8_t logo[];
extern const uint8_t imagesWinner[];
extern imageGif goalGif;
extern imageGif logoGif;
extern imageGif goalGifStruct;


#endif /* IMAGES_H_ */
