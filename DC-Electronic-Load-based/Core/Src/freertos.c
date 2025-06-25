/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "w25qxx.h"
#include "temp.h"
#include "encoder.h"
#include "24c02.h"
#include "ILI9341.h"
#include "lcd.h"
#include "fan_speed.h"
#include "ADS1115.h"
#include "MCP4725.h"
#include "PID.h"
#include "usart.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_obj_my.h"
#include "key.h"
#include "rtc_time.h"



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId lv_taskHandle;
osThreadId encoderHandle;
osThreadId KEYHandle;
osThreadId TimeHandle;
osThreadId Fan_speedHandle;
osThreadId TempHandle;
osThreadId displayHandle;
osThreadId ads1115_valueHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void Startlv_task(void const * argument);
void Startencoder(void const * argument);
void StartKEY(void const * argument);
void StartTime(void const * argument);
void StartFan_speed(void const * argument);
void StartTemp(void const * argument);
void Startdisplay(void const * argument);
void Startads1115_value(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of lv_task */
  osThreadDef(lv_task, Startlv_task, osPriorityIdle, 0, 256);
  lv_taskHandle = osThreadCreate(osThread(lv_task), NULL);

  /* definition and creation of encoder */
  osThreadDef(encoder, Startencoder, osPriorityIdle, 0, 256);
  encoderHandle = osThreadCreate(osThread(encoder), NULL);

  /* definition and creation of KEY */
  osThreadDef(KEY, StartKEY, osPriorityAboveNormal, 0, 256);
  KEYHandle = osThreadCreate(osThread(KEY), NULL);

  /* definition and creation of Time */
  osThreadDef(Time, StartTime, osPriorityIdle, 0, 256);
  TimeHandle = osThreadCreate(osThread(Time), NULL);

  /* definition and creation of Fan_speed */
  osThreadDef(Fan_speed, StartFan_speed, osPriorityIdle, 0, 256);
  Fan_speedHandle = osThreadCreate(osThread(Fan_speed), NULL);

  /* definition and creation of Temp */
  osThreadDef(Temp, StartTemp, osPriorityIdle, 0, 256);
  TempHandle = osThreadCreate(osThread(Temp), NULL);

  /* definition and creation of display */
  osThreadDef(display, Startdisplay, osPriorityIdle, 0, 256);
  displayHandle = osThreadCreate(osThread(display), NULL);

  /* definition and creation of ads1115_value */
  osThreadDef(ads1115_value, Startads1115_value, osPriorityIdle, 0, 256);
  ads1115_valueHandle = osThreadCreate(osThread(ads1115_value), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Startlv_task */
/**
* @brief Function implementing the lv_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Startlv_task */
void Startlv_task(void const * argument)
{
  /* USER CODE BEGIN Startlv_task */
  /* Infinite loop */
  for(;;)
  {
		lv_task_handler();
    osDelay(1);
  }
  /* USER CODE END Startlv_task */
}

/* USER CODE BEGIN Header_Startencoder */
/**
* @brief Function implementing the encoder thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Startencoder */
void Startencoder(void const * argument)
{
  /* USER CODE BEGIN Startencoder */
  /* Infinite loop */
  for(;;)
  {
		encoder_read();
    osDelay(1);
  }
  /* USER CODE END Startencoder */
}

/* USER CODE BEGIN Header_StartKEY */
/**
* @brief Function implementing the KEY thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartKEY */
void StartKEY(void const * argument)
{
  /* USER CODE BEGIN StartKEY */
  /* Infinite loop */
  for(;;)
  {
		KEY_sweep();
    osDelay(1);
  }
  /* USER CODE END StartKEY */
}

/* USER CODE BEGIN Header_StartTime */
/**
* @brief Function implementing the Time thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTime */
void StartTime(void const * argument)
{
  /* USER CODE BEGIN StartTime */
  /* Infinite loop */
  for(;;)
  {
		GET_Time();
    osDelay(1);
  }
  /* USER CODE END StartTime */
}

/* USER CODE BEGIN Header_StartFan_speed */
/**
* @brief Function implementing the Fan_speed thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartFan_speed */
void StartFan_speed(void const * argument)
{
  /* USER CODE BEGIN StartFan_speed */
  /* Infinite loop */
  for(;;)
  {
		Fan_speed_read();
    osDelay(1);
  }
  /* USER CODE END StartFan_speed */
}

/* USER CODE BEGIN Header_StartTemp */
/**
* @brief Function implementing the Temp thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTemp */
void StartTemp(void const * argument)
{
  /* USER CODE BEGIN StartTemp */
  /* Infinite loop */
  for(;;)
  {
		Temp_read();
    osDelay(1);
  }
  /* USER CODE END StartTemp */
}

/* USER CODE BEGIN Header_Startdisplay */
/**
* @brief Function implementing the display thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Startdisplay */
void Startdisplay(void const * argument)
{
  /* USER CODE BEGIN Startdisplay */
  /* Infinite loop */
  for(;;)
  {
		Voltage_Current_display();
    osDelay(1);
  }
  /* USER CODE END Startdisplay */
}

/* USER CODE BEGIN Header_Startads1115_value */
/**
* @brief Function implementing the ads1115_value thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Startads1115_value */
void Startads1115_value(void const * argument)
{
  /* USER CODE BEGIN Startads1115_value */
  /* Infinite loop */
  for(;;)
  {
		ads1115_value_read();
    osDelay(1);
  }
  /* USER CODE END Startads1115_value */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
