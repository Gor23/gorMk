#include "wifi.h"

//char wifiRecieveArray[WIFI_RECIEVE_ARRAY_SIZE];
char wifiRecieveArray[WIFI_RECIEVE_ARRAY_SIZE]  =
    { 0 };
char valueArray[JSON_VALUE_MAX_LENGTH] =
  { 0 };
uint8_t wifiFlags = 0;

void
Wifi_parser_remove_first_and_last (char *arrayPtr);

void
Wifi_data_update (void)
{
  wifiFlags |= 1 << DATA_UPDATE;
  USER_UART_Recieve_STOP (&WIFI_UART);
  HAL_TIM_Base_Stop (&WIFI_TIMER);
}

void
Wifi_parser (void)
{
  memset (valueArray, 0x00, JSON_VALUE_MAX_LENGTH);
  if (Wifi_parser_get_value ("TYPE"))
    {
      //TODO вставить case для обработки json
    }
  else
    {

    }
  memset (wifiRecieveArray, 0x00, WIFI_RECIEVE_ARRAY_SIZE);
  USER_UART_Recieve_INIT (&huart2, (uint8_t*)wifiRecieveArray, WIFI_RECIEVE_ARRAY_SIZE);
  wifiFlags &= ~(1 << DATA_UPDATE);
}

/**
 *
 */
Wifi_stop_receiving ()
{

}

/**
 *
 */

uint8_t
Wifi_parser_get_value (const char *keyPtr)
{

  char *ptr;
  char *endPtr;
  ptr = strstr (wifiRecieveArray, keyPtr);
  if (ptr)
    {
      ptr = ptr + strlen (keyPtr) + 2;
      endPtr = strchr (ptr, ',');

      if (!endPtr)
	{
	  endPtr = strchr (wifiRecieveArray, '}');
	  if (!endPtr)
	    {
	      return 0;
	    };
	}

      for (int i = 0; i < (endPtr - ptr); i++)
	{
	  valueArray[i] = ptr[i];
	  if (i >= JSON_VALUE_MAX_LENGTH)
	    {
	      break;
	    }
	}

      if (strchr (valueArray, '"'))
	{
	  Wifi_parser_remove_first_and_last (valueArray);
	  return 's';
	}

      return 'i';
    }
  return 0;
}

void
Wifi_parser_remove_first_and_last (char *arrayPtr)
{
  for (int i = 0; i < strlen (arrayPtr); i++)
    {
      arrayPtr[i] = arrayPtr[i + 1];
      if (arrayPtr[i] == '"')
	{
	  arrayPtr[i] = 0;
	  break;
	}
    }
}
