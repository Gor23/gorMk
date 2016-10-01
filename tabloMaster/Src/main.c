/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

#include "stm32f1xx_hal.h"
#include "main.h"
#include "string.h"
#include "video.h"
#include "images.h"
#include "wifi.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

IWDG_HandleTypeDef hiwdg;

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_rx;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_uart4_tx;
DMA_HandleTypeDef hdma_usart1_tx;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
void uart4_recieve(void);
void uart4_trancieve(void);
void dma_trancieve_callback (void);

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_CRC_Init(void);
static void MX_IWDG_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_UART4_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM7_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
#define MAX_FRAME	150


volatile uint32_t timer1;
volatile uint32_t timer2;
volatile uint16_t driverTimer = 0;
volatile uint16_t timerStopValue = 100;
volatile uint8_t ready = 0;
volatile uint8_t dmaSend = 0;

uint8_t answerOk = 0;
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
static const char lcd_image_mas[1024] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xE0, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC,
  0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
  0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
  0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF,
  0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
  0x7F, 0x00, 0x00, 0x7E, 0x7F, 0x7F, 0x7F, 0x00,
  0x00, 0x7F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xF0, 0xFF, 0xFF, 0x3F, 0x01, 0x00,
  0xF0, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F,
  0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
  0xF8, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x0F, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0xF0, 0xFE, 0xFF, 0x1F, 0x03, 0x00, 0x00, 0x00,
  0xFF, 0xFF, 0xFF, 0xE1, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x80, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00,
  0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0xFE, 0xFE,
  0x7E, 0x1E, 0x1E, 0x1E, 0x0E, 0x1E, 0x1E, 0x1E,
  0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0xFF, 0xFF,
  0xFF, 0x00, 0x00, 0x80, 0xE0, 0xE0, 0xE0, 0xE0,
  0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
  0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
  0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
  0xE0, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xE0, 0xE0, 0xFF,
  0xFF, 0x3F, 0x03, 0x00, 0x00, 0x00, 0x00, 0xE0,
  0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0x3F, 0x1F, 0x00, 0x00, 0xF8,
  0xFF, 0xFF, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF,
  0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
  0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x3F, 0x1F, 0x1F,
  0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0xFF, 0xFF, 0xFF,
  0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0x1F, 0x1F,
  0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
  0x07, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0,
  0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0x3F,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF,
  0xFF, 0xFF, 0xFF, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
  0xF8, 0xF8, 0xF8, 0xF8, 0x38, 0x00, 0x00, 0xFF,
  0xFF, 0x07, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03,
  0x03, 0x03, 0x03, 0x03, 0x07, 0xFF, 0xFF, 0x03,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF,
  0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xE7, 0xC0, 0xC0,
  0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x08, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0F, 0x0F, 0x0F, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x07, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07,
  0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
  0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0xF0, 0xFF,
  0x7F, 0x78, 0x78, 0x78, 0xF8, 0xFF, 0x7F, 0x7E,
  0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
  0x78, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x00,
  0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x80, 0xC0, 0xFF, 0xFF, 0xFF, 0x01,
  0x00, 0xFF, 0xFF, 0xFF, 0x3F, 0x3F, 0x3F, 0x3F,
  0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00,
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF,
  0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0x03, 0x00,
  0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x03, 0x00,
  0x80, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1C, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F,
  0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,
  0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,
  0x3F, 0x3F, 0x3F, 0x1F, 0x07, 0x03, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
//  MX_CRC_Init();
//  MX_IWDG_Init();
//  MX_SPI1_Init();
//  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_UART4_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
//  MX_TIM6_Init();
//  MX_TIM7_Init();
  uint8_t yPosition = 0;
  uint8_t frame = 0;
  uint8_t init_array[] = {'I', 'N', xMatrix, yMatrix, '\n'};
  uint32_t xMove = 0;

  image ballImage;
  image textBuffer;
  image stringBuffer;
  image commandTextBuffer;
  videoBuff mainBuffer;
  text testString;
  scoreForm footballForm;
  imageGif goalGif;
  imageGif logoGif;
  imageGif winerGif;

  uint8_t uartRecieveBuffer[64];
  uint8_t videoBuffer[TRANCIEVE_ARRAY_SIZE];
  uint8_t videoBufferSec[TRANCIEVE_ARRAY_SIZE];
  uint8_t textBuff[TEXT_BUF_SIZE];
  uint8_t commandTextBuff [COMM_TEXT_BUF_SIZE];
  uint8_t stringBuff [STRING_BUF_SIZE];
  uint8_t *subStringPtr = 0;


   uint8_t imageMode = LOGO_MODE;
   uint32_t ticks = 40;



   char *ptr_char0;
   char *ptr = NULL;

   ///////////////////// set buffer an images properties
   //footballForm.formImage

   goalGif.frames = 14;
   goalGif.frameSize = 1024;
   goalGif.imageArrayPtr = goal;
   goalGif.xLength = 128;
   goalGif.xOffset = 0;
   goalGif.yLength = 8;
   goalGif.yOffset = 0;
   goalGif.currentFrame = 0;
   goalGif.repeats = 20;
   goalGif.repeatsFrom = 12;

   logoGif.frames = 4;
   logoGif.frameSize = 1024;
   logoGif.imageArrayPtr = logo;
   logoGif.xLength = 128;
   logoGif.xOffset = 0;
   logoGif.yLength = 8;
   logoGif.yOffset = 0;
   logoGif.currentFrame = 0;
   logoGif.repeats = 0;
   logoGif.repeatsFrom = 0;

   winerGif.frames = 15;
   winerGif.frameSize = 1024;
   winerGif.imageArrayPtr = imagesWinner;
   winerGif.xLength = 128;
   winerGif.xOffset = 0;
   winerGif.yLength = 8;
   winerGif.yOffset = 0;
   winerGif.currentFrame = 0;
   winerGif.repeats = 0;
   winerGif.repeatsFrom = 0;

   ballImage.xLength = 128;
   ballImage.yLength = 8;
   ballImage.size = ballImage.xLength * ballImage.yLength;
   ballImage.xOffset = 0;
   ballImage.yOffset = 0;
   ballImage.imageArrayPtr = lcd_image_mas;

   textBuffer.xLength = 128;
   textBuffer.yLength = TEXT_BUF_SIZE/textBuffer.xLength;
   textBuffer.visibleLeftEdge = 0;
   textBuffer.visibleRightEdge = textBuffer.xLength;
   textBuffer.size = TEXT_BUF_SIZE;
   textBuffer.xOffset = 0;
   textBuffer.yOffset = 0;
   textBuffer.imageArrayPtr = textBuff;

   stringBuffer.xLength = 128;
   stringBuffer.yLength = STRING_BUF_SIZE/stringBuffer.xLength;
   stringBuffer.visibleLeftEdge = 0;
   stringBuffer.visibleRightEdge = stringBuffer.xLength;
   stringBuffer.size = STRING_BUF_SIZE;
   stringBuffer.xOffset = 0;
   stringBuffer.yOffset = 0;
   stringBuffer.imageArrayPtr = stringBuff;


   commandTextBuffer.xLength = 128;
   commandTextBuffer.yLength = COMM_TEXT_BUF_SIZE/textBuffer.xLength;
   commandTextBuffer.visibleLeftEdge = 0;
   commandTextBuffer.visibleRightEdge = commandTextBuffer.xLength;
   commandTextBuffer.size = COMM_TEXT_BUF_SIZE;
   commandTextBuffer.xOffset = 0;
   commandTextBuffer.yOffset = 0;
   commandTextBuffer.imageArrayPtr = commandTextBuff;

   mainBuffer.xLength = xMatrix*64;
   mainBuffer.yLength = TRANCIEVE_ARRAY_SIZE/mainBuffer.xLength;
   mainBuffer.size = TRANCIEVE_ARRAY_SIZE;
   mainBuffer.bufferArrayPtr = videoBuffer;
   mainBuffer.readBufferArrayPointer = videoBufferSec;
   mainBuffer.writeFlag = 0;

   testString.letterHight = 8;
   testString.letterWidth = 5;
   testString.xOffset = 0;
   testString.yOffset = 0;
   testString.stringPtr = "Риверсофт";
   ///////////////////////////

   memset (videoBuffer, 0x00, TRANCIEVE_ARRAY_SIZE);
   memset (textBuff, 0x00, TEXT_BUF_SIZE);
   memset (stringBuff, 0x00, STRING_BUF_SIZE);
   memset (uartRecieveBuffer, 0x00 ,sizeof(uartRecieveBuffer));
   memset (videoBufferSec, 0x00, TRANCIEVE_ARRAY_SIZE);
//   HAL_TIM_Base_Start_IT(&htim6);
   /* USER CODE END 2 */

   /* Infinite loop */
   /* USER CODE BEGIN WHILE */
//   USER_UART_clear_rx(&huart2);
//   USER_UART_enable_RX_IT(&huart2);
   HAL_Delay(10);
   uint8_t videoDriverStatus = INIT;
   uint8_t noAnswerTimer = 0;



  USER_UART_Recieve_INIT(&huart4, uartRecieveBuffer, sizeof(uartRecieveBuffer));
  USER_UART_Recieve_INIT (&huart2, wifiRecieveArray, sizeof(uartRecieveBuffer));
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uart4_trancieve();
  HAL_UART_Transmit_IT(&huart4, (uint8_t*)&init_array, sizeof(init_array));
  while (1)
  {
	  if (!driverTimer)
	  {
		  switch (videoDriverStatus)
		  	  {
		  	  case INIT:
		  		  if (HAL_UART_Transmit_IT(&huart2, (uint8_t*)&init_array, sizeof(init_array)) == HAL_OK)
		  		  {
		  			  videoDriverStatus = CHANGE_BUFER;
		  		  }
		  		  driverTimer = 100;
		  		  break;

		  	  case CHANGE_BUFER:
		  		  if (HAL_UART_Transmit_DMA(&huart2, (uint8_t*)"BUFC\n", strlen("BUFC\n")) == HAL_OK)
		  		  {
		  			  videoDriverStatus = ANSWER_CHECK;
		  			  //videoDriverStatus = SEND_DATA;
		  			  driverTimer = 3;
		  		  }
		  		  else
		  		  {
		  			driverTimer = 0;
		  		  }
		  		  //////////////////
//		  		  HAL_UART_Transmit_IT(&huart2, (uint8_t*)"BUFC\n", strlen("BUFC\n"));
//		  		  videoDriverStatus = SEND_DATA;
//		  		  driverTimer = 10;
		  		  /////////////////
		  		  break;

		  	  case ANSWER_CHECK:
		  		  if (strstr((char*)uartRecieveBuffer, "0123"))
		  		  {
		  			  USER_UART_Clear_Recieve_Buffer(&huart4, sizeof(uartRecieveBuffer));
		  			  noAnswerTimer = 0;
		  			  driverTimer = 3;
		  			  videoDriverStatus = SEND_DATA;
		  		  }
		  		  else
		  		  {
		  			  noAnswerTimer++;
		  			  driverTimer = 1;
		  			  if (noAnswerTimer == NO_ANSWER_TIMEOUT)
		  			  {
		  				  noAnswerTimer = 0;
		  				  driverTimer = 500;
		  				  videoDriverStatus = INIT;
		  			  }
		  			//виждать и отправить инит пакет
		  		  }
		  		  break;

		  	  case SEND_DATA:
		  		 if (HAL_UART_Transmit_DMA(&huart2, (uint8_t*)&videoBuffer, TRANCIEVE_ARRAY_SIZE) == HAL_OK)
		  		 {
		  			 ready = 1;
		  			 videoDriverStatus = WAIT_FOR_DATA_IS_SEND;
		  		 }
		  		 driverTimer = 0;
		  		 break;

		  	  case WAIT_FOR_DATA_IS_SEND:
		  		  if (dmaSend)
		  		  {
		  			  ready = 0;
		  			  dmaSend = 0;
		  		  }
		  		  if (ready)
		  		  {
		  			videoDriverStatus = CHANGE_BUFER;
		  		  }
		  		  driverTimer = 0;
		  		  break;
		  	  }
	  }




//	  if (!answerOk)
//	  {
//		  HAL_Delay(1000);
//		  HAL_UART_Transmit_IT(&huart2, (uint8_t*)&init_array, sizeof(init_array));
//		  HAL_Delay(100);
//	  }



//	  if ((ready)&&(!dmaSend))
//      //if (ready)
//	  //if (timer1 == TIMER_1_STOP_VALUE)
//	  {
//		 HAL_Delay(3);
//		 uart4_trancieve();
//		 HAL_UART_Transmit_DMA(&huart4, (uint8_t*)"BUFC\n", strlen("BUFC\n"));
//		// HAL_UART_Transmit_IT(&huart4, (uint8_t*)"BUFC\n", strlen("BUFC\n"));
//		 //(HAL_UART_Transmit_IT(&huart2, (uint8_t*)"BUFC\n", strlen("BUFC\n")) != HAL_OK);
//		 //USER_UART_enable_RX_IT (&huart2);
//		 HAL_Delay(3);
//		 while (!ptr)
//		 {
//			 ptr = strstr((char*)uartRecieveBuffer, "0123");
//		 }
//		 ptr = NULL;
//		 USER_UART_Clear_Recieve_Buffer(&huart4, sizeof(uartRecieveBuffer));
//		// USER_UART_clear_rx(&huart2);
//		 /*if (ptr == NULL)
//		 {
//			answerOk = 0;
//		 }
//		 else
//		 {*/
//		// Video_change_buffers(&mainBuffer, videoBuffer, videoBufferSec);
//		//	answerOk = 1;
//
//			//HAL_UART_Transmit_DMA(&huart2, (uint8_t*)&lcd_image_mas, TRANCIEVE_ARRAY_SIZE);
//		 	uart4_trancieve();
//			HAL_UART_Transmit_DMA(&huart4, (uint8_t*)&videoBuffer, TRANCIEVE_ARRAY_SIZE);
//		// }
//		// HAL_UART_Transmit_IT(&huart4, (uint8_t*)&videoBuffer, TRANCIEVE_ARRAY_SIZE);
//		dmaSend = 1;
//		ready = 0;
//		timer1 = 0;
//	  }


	  if ((timer2 == timerStopValue)&&(!ready))
	  {
		 //memset (videoBuffer, 0x00, TRANCIEVE_ARRAY_SIZE);
		 switch (imageMode)
		 {
		 case TEST_MODE:
			 timerStopValue = 300;
			 Video_put_image (&ballImage, &mainBuffer);
			 break;

		 case LOGO_MODE:
			 timerStopValue = 250;
			 Video_put_gif (&logoGif, &mainBuffer, false);
			 ticks--;
			 if (!ticks)
			 {
				 imageMode = GOAL_MODE;
				 ticks = 80;
			 }
			 break;

		 case GOAL_MODE:
			 timerStopValue = 70;
			 if (Video_put_gif (&goalGifStruct, &mainBuffer, false) == 'S')
				 {
				 	 imageMode = SCORE_MODE;
				 	 ticks = 20;
				 }
			 break;

		 case SCORE_MODE:
			 timerStopValue = 400;
			 Video_put_string_fonts ((uint8_t*)"0:1", Font2_array, &textBuffer);
			 Video_put_and_move_string ((uint8_t*)"Франция - Португалия", FontSmall_array, &commandTextBuffer);
			 Video_move_image(&textBuffer, &mainBuffer, 18, 0);
			 Video_move_image(&commandTextBuffer, &mainBuffer, 0, 6);
			 Video_put_image(&textBuffer, &mainBuffer);
			 Video_put_image(&commandTextBuffer, &mainBuffer);
			 ticks--;

			 if (!ticks)
			 {
				 imageMode = WINNER_MODE;
				 ticks = 80;
			 }
			 break;

		 case WINNER_MODE:
		 			 timerStopValue = 20;
 		 			 ticks--;
 		 			 Video_put_gif (&winerGif, &mainBuffer, true);
 		 			 if (!ticks)
 		 			 {
 		 			 	imageMode = STRING_MODE;
 		 			 	ticks = 100;
 		 			 }
 		 			 break;

		 case STRING_MODE:
			 timerStopValue = 300;
			 Video_put_and_move_string ((uint8_t*)"DISPLAY v1.0", FontSmall_array, &stringBuffer);
			 Video_move_image(&stringBuffer, &mainBuffer, 0, 3);
			 Video_put_image(&stringBuffer, &mainBuffer);
			 /*xMove += 4;
			 if (xMove == 128)
				 xMove = 0;*/
			 ticks--;

			 	if (!ticks)
			    {
			 		imageMode = LOGO_MODE;
			 		ticks = 20;
			 	}
			 break;

		 default: break;
		 }

		  ready = 1;
		  timer2 = 0;
	  }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/* USER CODE BEGIN 4 */

void uart4_recieve(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
}

void uart4_trancieve(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
}

void dma_trancieve_callback (void)
{
		uart4_recieve();
}
/* USER CODE END 4 */

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* CRC init function */
static void MX_CRC_Init(void)
{

  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }

}

/* IWDG init function */
static void MX_IWDG_Init(void)
{

  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_4;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }

}

/* SPI1 init function */
static void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }

}

/* TIM1 init function */
static void MX_TIM1_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

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
    Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

/* TIM6 init function */
static void MX_TIM6_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;

  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 0;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

/* TIM7 init function */
static void MX_TIM7_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;

  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 0;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 0;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

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
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 256000;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
 // huart2.resrtTimer = &resetWifiRecieveTimer;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();

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

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
