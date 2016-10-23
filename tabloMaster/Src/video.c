/*
 * strings.c

 *
 *  Created on: 1 июля 2016 г.
 *      Author: lihodey_i
 */

#include "video.h"

UART_HandleTypeDef huart4;
DMA_HandleTypeDef hdma_uart4_tx;
TIM_HandleTypeDef htim2;

videoBuff mainBuffer;
uint8_t videoBuffer[TRANCIEVE_ARRAY_SIZE];
uint8_t videoBufferSec[TRANCIEVE_ARRAY_SIZE];
uint8_t uartRecieveBuffer[RECIEVE_ARRAY_SIZE];

static void MX_DMA_Init(void);
static void MX_UART4_Init(void);
static void MX_TIM2_Init(void);
void uart4_trancieve(void);
void uart4_recieve(void);
void void_function(uint8_t in);
void dma_trancieve_callback(void);

void Video_init()
    {
    mainBuffer.xLength = xMatrix * 64;
    mainBuffer.yLength = TRANCIEVE_ARRAY_SIZE / mainBuffer.xLength;
    mainBuffer.size = TRANCIEVE_ARRAY_SIZE;
    mainBuffer.bufferArrayPtr = videoBuffer;
    mainBuffer.readBufferArrayPointer = videoBufferSec;
    mainBuffer.writeFlag = 0;
    memset(videoBuffer, 0x00, TRANCIEVE_ARRAY_SIZE);
    memset(videoBufferSec, 0x00, TRANCIEVE_ARRAY_SIZE);
    memset(uartRecieveBuffer, 0x00, RECIEVE_ARRAY_SIZE);
    MX_DMA_Init();
    MX_UART4_Init();
    MX_TIM2_Init();
    USER_UART_Recieve_INIT(&huart4, uartRecieveBuffer, sizeof(uartRecieveBuffer));
    }

void Video_clear_trancieve_buffer(void)
    {
    memset(videoBuffer, 0x00, TRANCIEVE_ARRAY_SIZE);
    }

void Video_clear_recieve_buffer(void)
    {
    USER_UART_Clear_Recieve_Buffer(&huart4, RECIEVE_ARRAY_SIZE);
    }

void Video_change_buffers(uint8_t *firstBuff, uint8_t *secondBuff)
    {
    if (mainBuffer.writeFlag)
	{
	mainBuffer.bufferArrayPtr = secondBuff;
	mainBuffer.readBufferArrayPointer = firstBuff;
	mainBuffer.writeFlag = 0;
	}
    else
	{
	mainBuffer.bufferArrayPtr = firstBuff;
	mainBuffer.readBufferArrayPointer = secondBuff;
	mainBuffer.writeFlag = 1;
	}
    }

uint8_t Video_put_string(text *textStruct, const tChar *fonts)
    {
    uint32_t yOffsetInBits = textStruct->yOffset * mainBuffer.xLength;
    int32_t letterOffset = textStruct->xOffset + yOffsetInBits + textStruct->stringShift;
    int32_t temp = letterOffset;
    uint16_t x = 0;
    uint16_t y = 0;
    uint16_t letter;
    uint8_t asciCode = 0;
    uint8_t hieghtInBytes = 0;
    uint8_t lastLetter = 0;

    if (fonts[asciCode].image->height % 8)
	{
	hieghtInBytes = fonts[asciCode].image->height / 8 + 1;
	}
    else
	{
	hieghtInBytes = fonts[asciCode].image->height / 8;
	}

    for (letter = 0; letter < strlen((char*) textStruct->stringPtr); letter++)
	{
	asciCode = textStruct->stringPtr[letter];
	if (asciCode > 0x7D)
	    {
	    //asciCode -= RUS_ARRAY_OFFSRET;
	    asciCode -= 1;
	    }
	asciCode -= ARRAY_SYMBOLS_OFFSET;

	for (y = 0; y < hieghtInBytes; y++)
	    {
	    for (x = 0; x < fonts[asciCode].image->width; x++)
		{
		if (temp >= mainBuffer.size)
		    {
		    return BUFFER_OVERFLOW;
		    }
		if (temp >= (int32_t) (textStruct->visibleRightEdge + yOffsetInBits + mainBuffer.xLength * y))
		    {
		    //temp++;
		    lastLetter = 1;
		    break;
		    }
		if (temp < (int32_t) (textStruct->xOffset + mainBuffer.xLength * (y + textStruct->yOffset)))
		    {
		    break;
		    }
		mainBuffer.bufferArrayPtr[temp] = fonts[asciCode].image->arrayPointer[x
			+ y * fonts[asciCode].image->width];
		temp++;
		}
	    temp = temp + mainBuffer.xLength - x;
	    }

	if (lastLetter)
	    {
	    return NOT_COMPLETE;
	    }
	letterOffset += (fonts[asciCode].image->width);
	temp = letterOffset;
	}
    return COMPLETE;
    }

void Video_move_string_left(text *textStruct, uint8_t step)
    {
    textStruct->stringShift -= step;
    }

void Video_move_string_right(text *textStruct, uint8_t step)
    {
    textStruct->stringShift += step;
    }

uint8_t Video_put_n_move_string_left(text *textStruct, const tChar *fonts, uint8_t step)
    {
    Video_move_string_left(textStruct, step);
    if (Video_put_string(textStruct, fonts) == COMPLETE)
	{
	return COMPLETE;
	}
    else
	{
	return NOT_COMPLETE;
	}
    }

void Video_put_and_move_string(uint8_t *text, const tChar *fonts)
    {
//	static uint8_t *subStringPtr;
//
//	 memset (videoBuffPtr->imageArrayPtr, 0x00, videoBuffPtr->size);
//	 if (subStringPtr)
//	 {
//	 	subStringPtr = Video_put_string_fonts(subStringPtr, fonts, videoBuffPtr);
//	 }
//	 else
//	 {
//	 	subStringPtr = Video_put_string_fonts(text, fonts, videoBuffPtr);
//	 }
    }

void Video_put_image(image *imgPtr)
    {
    uint32_t y = 0;
    uint32_t x = 0;
    uint32_t temp = 0;
    uint32_t imagrByteCounter = 0;

    for (y = 0; y < imgPtr->yLength; y++)
	{
	temp = y * mainBuffer.xLength + imgPtr->xOffset + imgPtr->yOffset;
	for (x = 0; x < imgPtr->xLength; x++)
	    {
	    if (temp < mainBuffer.size)
		{
		mainBuffer.bufferArrayPtr[temp++] = imgPtr->imageArrayPtr[imagrByteCounter++];
		}
	    else
		{
		return;
		}

	    }
	}
    }

uint8_t Video_put_image_edge(image *imgPtr)
    {
    uint8_t answer = 1;
    uint32_t y = 0;
    uint32_t x = 0;
    int32_t temp = 0;
    uint32_t imagrByteCounter = 0;

    for (y = 0; y < imgPtr->yLength; y++)
	{
	temp = y * mainBuffer.xLength + imgPtr->xOffset + imgPtr->yOffset;
	for (x = 0; x < imgPtr->xLength; x++)
	    {
	    if ((temp < mainBuffer.xLength * (y + 1)) || (temp > mainBuffer.xLength))
		{
		mainBuffer.bufferArrayPtr[temp++] = imgPtr->imageArrayPtr[imagrByteCounter++];
		answer = 0;
		}
	    else
		{
		break;
		}

	    }
	}
    return answer;
    }

void Video_move_image(image *imgPtr, uint16_t xMove, uint16_t yMove)
    {
    memset(mainBuffer.bufferArrayPtr, 0x00, mainBuffer.size);
    imgPtr->xOffset = xMove;
    imgPtr->yOffset = mainBuffer.xLength * yMove;
    }

uint8_t Video_put_gif(imageGif *imgPtr, uint8_t invertFlag)
    {

    uint16_t y = 0;
    uint16_t x = 0;
    uint16_t temp = 0;
    uint16_t imagrByteCounter = 0;
    static uint8_t repeats = 0;
    const uint8_t *frameArrayPtr;

    frameArrayPtr = imgPtr->imageArrayPtr + imgPtr->frameSize * imgPtr->currentFrame;
    imgPtr->currentFrame++;

    for (y = 0; y < imgPtr->yLength; y++)
	{
	temp = y * mainBuffer.xLength + imgPtr->xOffset + imgPtr->yOffset;
	for (x = 0; x < imgPtr->xLength; x++)
	    {
	    if (temp < mainBuffer.size)
		{
		if (invertFlag)
		    mainBuffer.bufferArrayPtr[temp++] = ~frameArrayPtr[imagrByteCounter++];
		else
		    mainBuffer.bufferArrayPtr[temp++] = frameArrayPtr[imagrByteCounter++];
		}
	    else
		{
		return 'E';
		}

	    }
	}

    if (imgPtr->currentFrame == imgPtr->frames)
	{
	if (imgPtr->repeats)
	    {
	    repeats++;
	    imgPtr->currentFrame = imgPtr->repeatsFrom;
	    }
	else
	    {
	    repeats = 0;
	    imgPtr->currentFrame = 0;
	    return 'S';
	    }

	}
    if ((repeats == imgPtr->repeats) && (imgPtr->repeats))
	{
	repeats = 0;
	imgPtr->currentFrame = 0;
	return 'S';
	}
    else
	{
	return 'R';
	}
    }

void Video_put_form(ScoreForm *form, FormType type)
    {
    Video_put_string(&form->firstTeamScore, Font2_array);
    Video_put_string(&form->scoreDevider, Font2_array);
    Video_put_string(&form->secondTeamScore, Font2_array);

    Video_put_string(&form->firsTeamName, Font_array);
    Video_put_string(&form->teamDevider, Font_array);
    Video_put_string(&form->secondTeamName, Font_array);

    if (type == EXTENDED_FORM)
	{
	Video_put_string(&form->firstTeamAdditional, Font_array);
	Video_put_string(&form->secondTeamAdditional, Font_array);
	}
    }

void Video_send_data_to_display(void)
    {
    uart4_trancieve();
    HAL_UART_Transmit_DMA(&huart4, (uint8_t*) &videoBuffer,
    TRANCIEVE_ARRAY_SIZE);
    }

void Video_cmd(uint8_t *comandPtr, uint16_t size)
    {
    uart4_trancieve();
    HAL_UART_Transmit_DMA(&huart4, comandPtr, size);
    }

char *Video_get_answer (void)
    {
    return strstr((char*) uartRecieveBuffer, "0123");
    }

void uart4_recieve(void)
    {
    HAL_TIM_Base_Start_IT(&htim2);
    //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
    }

void uart4_trancieve(void)
    {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
    }

void dma_trancieve_callback(void)
    {
    uart4_recieve();
    }

void void_function(uint8_t in)
    {

    }

/* UART4 init function */
static void MX_UART4_Init(void)
    {

    huart4.Instance = UART4;
    huart4.Init.BaudRate = 256000;
    huart4.Init.WordLength = UART_WORDLENGTH_8B;
    huart4.Init.StopBits = UART_STOPBITS_1;
    huart4.Init.Parity = UART_PARITY_NONE;
    huart4.Init.Mode = UART_MODE_TX_RX;
    huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart4.Init.OverSampling = UART_OVERSAMPLING_16;
    huart4.rs485FlowControlFunction = &uart4_recieve;
    huart4.resrtTimer = &void_function;
    if (HAL_UART_Init(&huart4) != HAL_OK)
	{
	//Error_Handler();
	}

    }

/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void)
    {
    /* DMA controller clock enable */
    __HAL_RCC_DMA1_CLK_ENABLE()
    ;
    __HAL_RCC_DMA2_CLK_ENABLE()
    ;

    /* DMA interrupt init */
    /* DMA1_Channel2_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    /* DMA1_Channel4_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
    /* DMA2_Channel4_5_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA2_Channel4_5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Channel4_5_IRQn);
    hdma_uart4_tx.rs485FlowControlFunction = &dma_trancieve_callback;

    }

/* TIM2 init function */
static void MX_TIM2_Init(void)
    {

    TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_MasterConfigTypeDef sMasterConfig;

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 71;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = HUART4_RECIEVE_TIMEOUT;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
	//Error_Handler();
	}

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
	//Error_Handler();
	}

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
	//Error_Handler();
	}
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
