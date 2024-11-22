#ifndef BTN_TASK_H
#define BTN_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "publisher_task.h"

/******************************************************************************
* Extern Global Variables
******************************************************************************/
extern QueueHandle_t DataQueue; // Reference to the publisher's DataQueue
#define MQTT_BTN_TOPIC       "wesvr/feeds/button"
/******************************************************************************
* Function Prototypes
******************************************************************************/
/**
 * @brief FreeRTOS task to handle button state changes and send messages to the queue.
 *
 * @param pvParameters Task-specific parameters (not used).
 */
void btn_task(void *pvParameters);

#endif /* BTN_TASK_H */
