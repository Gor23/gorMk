#include "wifi.h"
#include "events.h"
#include <string.h>

//char wifiRecieveArray[WIFI_RECIEVE_ARRAY_SIZE];

TIM_HandleTypeDef htim6;
UART_HandleTypeDef huart2;

const char type[] = "game_type";
const char system[] = "SYSTEM";
const char noGames[] = "NO_GAMES";
const char time[] = "time";
const char badConn1[] = "BAD_CONN=1";
const char badConn2[] = "BAD_CONN=2";
const char badConn3[] = "BAD_CONN=3";
const char badConn4[] = "BAD_CONN=4";
const char badConn5[] = "BAD_CONN=5";
const char idle[] = "Idle";
const char connecting[] = "Connecting";
const char wrongPassword[] = "Wrong Password";
const char noAPFound[] = "No AP Found";
const char fail[] = "Fail";
const char connected[] = "Connected";
const char firstTeamName[] = "team_name_first";
const char secondTeamName[] = "team_name_second";
const char firstTeamScore[] = "score_first";
const char secondTeamScore[] = "score_second";
const char additionalFirstTeamScore[] = "winPeriodFirst";
const char additionalSecondTeamScore[] = "winPeriodSecond";
const char actionType[] = "action_type";
const char winnerTeamName[] = "team_name";
const char score[] = "score";
const char customMessage[] = "custom_message";
const char messageBody[] = "message_body";

char wifiRecieveBuffer[WIFI_RECIEVE_ARRAY_SIZE] =
    {
    0
    };

char *ptrWifiRecieveBuffer;
uint8_t wifiFlags = 0;

void
Wifi_parser_remove_first_and_last(char *arrayPtr);

void Wifi_data_update(void)
    {
    wifiFlags |= 1 << DATA_UPDATE;
    USER_UART_Recieve_STOP(&Wifi_uart);
    HAL_TIM_Base_Stop(&Wifi_timer);
    }

void Wifi_null_removing()
    {
    for (uint16_t i = 0; i < WIFI_RECIEVE_ARRAY_SIZE; i++)
	{
	if (wifiRecieveBuffer[i] != 0)
	    {
	    ptrWifiRecieveBuffer = &wifiRecieveBuffer[i];
	    return;
	    }
	}
    }

void Wifi_parser(void)
    {
    eventData.eventType = UNDEFINED;
    Wifi_null_removing();

    if (Wifi_parser_get_value(type, MAX_EVENT_STRING_SIZE, (char*) &gameData.gameType))
	{
	Events_clear_strings_event_data();
	Events_clear_strings_game_data();
	eventData.eventType = GAME;
	Wifi_parser_get_value(type, MAX_EVENT_STRING_SIZE, (char*) &gameData.gameType);
	Wifi_parser_get_value(actionType, MAX_EVENT_STRING_SIZE, (char*) &gameData.actionType);
	Wifi_parser_get_value(firstTeamName, MAX_EVENT_STRING_SIZE, (char*) &gameData.firstTeam);
	Wifi_parser_get_value(secondTeamName, MAX_EVENT_STRING_SIZE, (char*) &gameData.secondTeam);
	Wifi_parser_get_value(firstTeamScore, MAX_EVENT_STRING_SIZE, (char*) &gameData.firstTeamScore);
	Wifi_parser_get_value(secondTeamScore, MAX_EVENT_STRING_SIZE, (char*) &gameData.secondTeamScore);
	Wifi_parser_get_value(additionalFirstTeamScore, MAX_EVENT_STRING_SIZE,
		(char*) &gameData.additionalFirstTeamScore);
	Wifi_parser_get_value(additionalSecondTeamScore, MAX_EVENT_STRING_SIZE,
		(char*) &gameData.additionalSecondTeamScore);
	}

    else if (strstr(ptrWifiRecieveBuffer, "WINNER"))
	{
	Events_clear_strings_event_data();
	Events_clear_strings_game_data();
	eventData.eventType = WINNER;
	Wifi_parser_get_value(winnerTeamName, MAX_EVENT_STRING_SIZE, (char*) &gameData.firstTeam);
	Wifi_parser_get_value(score, MAX_EVENT_STRING_SIZE, (char*) &gameData.firstTeamScore);
	}
    else if (strstr(ptrWifiRecieveBuffer, customMessage))
	{
	Events_clear_strings_event_data();
	Events_clear_strings_game_data();
	eventData.eventType = MESSAGE;
	Wifi_parser_get_value(messageBody, MAX_EVENT_STRING_SIZE, (char*) &eventData.eventMessage);
	}
    else if (strstr(ptrWifiRecieveBuffer, noGames))
	{
	Events_clear_strings_event_data();
	eventData.eventType = TIME;
	Wifi_get_time((char*) &eventData.eventMessage, MAX_EVENT_STRING_SIZE);
	}
    else if (strstr(ptrWifiRecieveBuffer, badConn1))
	{
	Events_clear_strings_event_data();
	eventData.eventType = SYSTEM;
	Wifi_string_copy(badConn1, (char*) &eventData.eventMessage,
	MAX_EVENT_STRING_SIZE);
	}
    else if (strstr(ptrWifiRecieveBuffer, badConn2))
	{
	Events_clear_strings_event_data();
	eventData.eventType = SYSTEM;
	Wifi_string_copy(badConn2, (char*) &eventData.eventMessage,
	MAX_EVENT_STRING_SIZE);
	}
    else if (strstr(ptrWifiRecieveBuffer, badConn3))
	{
	Events_clear_strings_event_data();
	eventData.eventType = SYSTEM;
	Wifi_string_copy(badConn3, (char*) &eventData.eventMessage,
	MAX_EVENT_STRING_SIZE);
	}
    else if (strstr(ptrWifiRecieveBuffer, badConn4))
	{
	Events_clear_strings_event_data();
	eventData.eventType = SYSTEM;
	Wifi_string_copy(badConn4, (char*) &eventData.eventMessage,
	MAX_EVENT_STRING_SIZE);
	}
    else if (strstr(ptrWifiRecieveBuffer, badConn5))
	{
	Events_clear_strings_event_data();
	eventData.eventType = SYSTEM;
	Wifi_string_copy(badConn5, (char*) &eventData.eventMessage,
	MAX_EVENT_STRING_SIZE);
	}
//    else if (strstr(ptrWifiRecieveBuffer, idle))
//	{
//	eventData.eventType = HIDDEN;
//	Wifi_string_copy(idle, (char*) &eventData.eventMessage,
//	MAX_EVENT_STRING_SIZE);
//	}
//    else if (strstr(ptrWifiRecieveBuffer, connecting))
//	{
//	eventData.eventType = HIDDEN;
//	Wifi_string_copy(connecting, (char*) &eventData.eventMessage,
//	MAX_EVENT_STRING_SIZE);
//	}
//    else if (strstr(ptrWifiRecieveBuffer, wrongPassword))
//	{
//	eventData.eventType = SYSTEM;
//	Wifi_string_copy(wrongPassword, (char*) &eventData.eventMessage,
//	MAX_EVENT_STRING_SIZE);
//	}
//    else if (strstr(ptrWifiRecieveBuffer, noAPFound))
//	{
//	eventData.eventType = SYSTEM;
//	Wifi_string_copy(noAPFound, (char*) &eventData.eventMessage,
//	MAX_EVENT_STRING_SIZE);
//	}
//    else if (strstr(ptrWifiRecieveBuffer, fail))
//	{
//	eventData.eventType = SYSTEM;
//	Wifi_string_copy(fail, (char*) &eventData.eventMessage,
//	MAX_EVENT_STRING_SIZE);
//	}
//    else if (strstr(ptrWifiRecieveBuffer, connected))
//	{
//	eventData.eventType = HIDDEN;
//	Wifi_string_copy(connected, (char*) &eventData.eventMessage,
//	MAX_EVENT_STRING_SIZE);
//	}

    memset(wifiRecieveBuffer, 0x00, WIFI_RECIEVE_ARRAY_SIZE);
    USER_UART_Recieve_INIT(&Wifi_uart, (uint8_t*) wifiRecieveBuffer,
    WIFI_RECIEVE_ARRAY_SIZE);
    wifiFlags &= ~(1 << DATA_UPDATE);
    }

/**
 *
 */
void Wifi_get_time(char *strPtr, uint8_t arraySize)
    {
    char *ptr;
//    char tempArray[50];
//    Wifi_parser_get_value(time, MAX_EVENT_STRING_SIZE, (char*) &tempArray);
    ptr = strchr(ptrWifiRecieveBuffer, 'T');
    if (ptr)
	{
	ptr++;
	for (uint8_t i = 0; i < 5; i++)
	    {
	    strPtr[i] = ptr[i];
	    if (i >= arraySize)
		{
		return;
		}
	    }
	}
    else
	{
	sprintf((char*) strPtr, "Not found");
	}
    }

uint8_t Wifi_parser_get_value(const char *keyPtr, uint8_t outputStringMaxSize, char *outputArrPtr)
    {

    char *ptr;
    char *endPtr;
    ptr = strstr(ptrWifiRecieveBuffer, keyPtr);
    if (ptr)
	{
	ptr = ptr + strlen(keyPtr) + 2;
	endPtr = strchr(ptr, ',');

	if (!endPtr)
	    {
	    endPtr = strchr(ptrWifiRecieveBuffer, '}');
	    if (!endPtr)
		{
		return 0;
		};
	    }

	for (int i = 0; i < (endPtr - ptr); i++)
	    {
	    outputArrPtr[i] = ptr[i];
	    if (i >= outputStringMaxSize)
		{
		break;
		}
	    }

	if (strchr(outputArrPtr, '"'))
	    {
	    Wifi_parser_remove_first_and_last(outputArrPtr);
	    return 's';
	    }

	return 'i';
	}
    return 0;
    }

void Wifi_parser_remove_first_and_last(char *arrayPtr)
    {
    for (int i = 0; i < strlen(arrayPtr); i++)
	{
	arrayPtr[i] = arrayPtr[i + 1];
	if (arrayPtr[i] == '"')
	    {
	    arrayPtr[i] = 0;
	    arrayPtr[i + 1] = 0;
	    break;
	    }
	}
    }

uint8_t Wifi_string_copy(const char *sourcePtr, char *destPtr, uint8_t destSize)
    {
    for (uint8_t i = 0; i < strlen(sourcePtr); i++)
	{
	if (i < destSize)
	    {
	    destPtr[i] = sourcePtr[i];
	    }
	else
	    return 0;
	}
    return 'k';
    }

void MX_TIM6_Init(void)
    {

    TIM_MasterConfigTypeDef sMasterConfig;

    htim6.Instance = TIM6;
    htim6.Init.Prescaler = 7199;
    htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim6.Init.Period = WIFI_RECEIVE_TIME_TRIGER;
    if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
	{
//Error_Handler ();
	}
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
	{
//Error_Handler ();
	}
    HAL_NVIC_EnableIRQ(TIM6_IRQn);
    /* USER CODE BEGIN 5 */
    __HAL_TIM_ENABLE_IT(&htim6, TIM_IT_UPDATE);
    /* USER CODE END 5 */
    }

void Wifi_void_function()
    {

    }
/* USART2 init function */
void MX_USART2_UART_Init(void)
    {

    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    huart2.rs485FlowControlFunction = &Wifi_void_function;
    huart2.resrtTimer = &uart2_start_recieve_trigger;
    if (HAL_UART_Init(&huart2) != HAL_OK)
	{
//Error_Handler ();
	}

    }

void uart2_start_recieve_trigger(uint8_t isNeedTurnOn)
    {
    htim6.Instance->CNT = 0;
    if (isNeedTurnOn != 0)
	{
	htim6.Instance->CR1 |= TIM_CR1_CEN;
	}
    }

void Wifi_init()
    {
    MX_USART2_UART_Init();
    MX_TIM6_Init();
    USER_UART_Recieve_INIT(&huart2, (uint8_t*) wifiRecieveBuffer,
    WIFI_RECIEVE_ARRAY_SIZE);
    }
