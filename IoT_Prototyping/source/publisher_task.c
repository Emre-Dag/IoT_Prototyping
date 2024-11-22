#include "cyhal.h"
#include "cybsp.h"
#include "FreeRTOS.h"

/* Task header files */
#include "publisher_task.h"
#include "mqtt_task.h"
#include "subscriber_task.h"

/* Configuration file for MQTT client */
#include "mqtt_client_config.h"

/* Middleware libraries */
#include "cy_mqtt_api.h"
#include "cy_retarget_io.h"

/******************************************************************************
* Macros
******************************************************************************/
#define PUBLISHER_TASK_QUEUE_LENGTH     (1u) // Define the queue length
#define PUBLISH_RETRY_LIMIT             (10)
#define PUBLISH_RETRY_MS                (1000)
#define PUBLISH_INTERVAL_MS             (10000)

void print_heap_usage(char *msg); // Declare the function
static void publisher_init(void);
/******************************************************************************
* Global Variables
*******************************************************************************/
/* FreeRTOS task handle for this task. */
TaskHandle_t publisher_task_handle;

/* Handle of the queue holding the commands for the publisher task */
QueueHandle_t publisher_task_q;
QueueHandle_t DataQueue;

cy_mqtt_publish_info_t publish_info =
{
    .qos = (cy_mqtt_qos_t) MQTT_MESSAGES_QOS,
    .topic = MQTT_PUB_TOPIC,
    .topic_len = (sizeof(MQTT_PUB_TOPIC) - 1),
    .retain = false,
    .dup = false
};


void publisher_task(void *pvParameters)
{
	cy_mqtt_publish_info_t received_data;
    publisher_init();
    while (true)
    {
        // Wait for data from the queue
        if (xQueueReceive(DataQueue, &received_data, portMAX_DELAY) == pdTRUE)
        {
            printf("Publisher: Publishing topic '%s' with message '%s'\n",
                   received_data.topic, received_data.payload);

            // Prepare the publish information
            publish_info.topic = received_data.topic;
            publish_info.topic_len = strlen(received_data.topic);
            publish_info.payload = received_data.payload;
            publish_info.payload_len = strlen(received_data.payload);

            cy_rslt_t result = cy_mqtt_publish(mqtt_connection, &publish_info);
            if (result != CY_RSLT_SUCCESS)
            {
                printf("Publisher: MQTT Publish failed with error 0x%0X.\n", (int)result);
            }
        }
        print_heap_usage("publisher_task: After publishing");
    }
}


static void publisher_init(void)
{
	DataQueue = xQueueCreate(10, sizeof(cy_mqtt_publish_info_t)); // Queue can hold up to 10 items

    printf("\nQueue init\n");
}
