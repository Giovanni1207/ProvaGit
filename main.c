/***********************************************************************************
*
* Copyright © 2016-2019 STMicroelectronics - All Rights Reserved
*
* License terms: STMicroelectronics Proprietary in accordance with licensing
* terms SLA0089 at www.st.com
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* EVALUATION ONLY – NOT FOR USE IN PRODUCTION
************************************************************************************/

/* Inclusion of the main header files of all the imported components in the
   order specified in the application wizard. The file is generated
   automatically.*/
#include "components.h"

#include "FreeRTOS.h"
#include "task.h"

uint8_t message_task1[]= "Task1...\r\n";
uint8_t message_task2[]= "Task2...\r\n";

/* Demo tasks */
portTASK_FUNCTION( vTaskOne, pvParameters )
{
  ( void ) pvParameters;
  TickType_t xLastWakeTime = xTaskGetTickCount();
  for ( ;; ) {
    vTaskSuspendAll();
    sd_lld_write(&SD1,message_task1,(uint16_t)(sizeof(message_task1)/sizeof(message_task1[0])));
    xTaskResumeAll();
    pal_lld_togglepad(PORT_A, LED0);
    vTaskDelayUntil( &xLastWakeTime, 200 );
  }
}

/* Demo tasks */
portTASK_FUNCTION( vTaskTwo, pvParameters )
{
  ( void ) pvParameters;
  TickType_t xLastWakeTime = xTaskGetTickCount();
  for ( ;; ) {
    vTaskSuspendAll();
    sd_lld_write(&SD1,message_task2,(uint16_t)(sizeof(message_task2)/sizeof(message_task2[0])));
    xTaskResumeAll();
    vTaskDelayUntil( &xLastWakeTime, 200 );
    pal_lld_togglepad(PORT_A, LED1);
  }
}

/*
 * Application entry point.
 */
int main(void) {

  /* Initialization of all the imported components in the order specified in
     the application wizard. The function is generated automatically.*/
  componentsInit();

  /* Enable Interrupts */
  irqIsrEnable();

  /*
   * Activates the serial driver 1 using the driver default configuration.
   */
  sd_lld_start(&SD1, NULL);

  /* Creating first task to blink LED0 */
  xTaskCreate( vTaskOne,
               (const char * const)"task #1",
               configMINIMAL_STACK_SIZE,
               NULL,
               tskIDLE_PRIORITY + 1,
               NULL );

  /* Creating second task to blink LED1 */
  xTaskCreate( vTaskTwo,
               (const char * const)"task #2",
               configMINIMAL_STACK_SIZE,
               NULL,
               tskIDLE_PRIORITY + 1,
               NULL );

  /* Start the FreeRTOS scheduler */
  vTaskStartScheduler();

  return 0;

}
