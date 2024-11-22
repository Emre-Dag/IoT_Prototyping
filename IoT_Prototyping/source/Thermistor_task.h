#ifndef SOURCE_THERMISTOR_H_
#define SOURCE_THERMISTOR_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "publisher_task.h"

/*******************************************************************************
* Macros
********************************************************************************/

/*******************************************************************************
* Function Prototypes
********************************************************************************/
void thermistor_task(void *args);
extern QueueHandle_t DataQueue;
/*******************************************************************************
* Global Variables
********************************************************************************/
/* MQTT Topic for thermistor data */
#define MQTT_THERMISTOR_TOPIC        "wesvr/feeds/thermistor"

extern uint32_t temperature;
extern TaskHandle_t thermistor_task_handle;

#endif /* SOURCE_THERMISTOR_H_ */
