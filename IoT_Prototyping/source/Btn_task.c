#include "cyhal.h"
#include "cybsp.h"
#include "cy_mqtt_api.h"
#include <stdio.h>
#include "Btn_task.h"

/******************************************************************************
* Global Variables
*******************************************************************************/
extern QueueHandle_t DataQueue; // Use the existing queue for communication
static volatile bool btn_state_changed = false; // Flag to track button state change
static bool prev_btn_state = CYBSP_BTN_OFF;     // Previous button state

/******************************************************************************
* Function Prototypes
******************************************************************************/
static void button_isr(void *callback_arg, cyhal_gpio_event_t event);

/******************************************************************************
* Button Task Implementation
******************************************************************************/
void btn_task(void *pvParameters)
{
    // Initialize the button GPIO
    cyhal_gpio_init(CYBSP_USER_BTN, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, CYBSP_BTN_OFF);

    // Initialize the user LED GPIO
    cyhal_gpio_init(CYBSP_USER_LED, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);

    // Register and enable the ISR for button press/release
    cyhal_gpio_register_callback(CYBSP_USER_BTN, &(cyhal_gpio_callback_data_t){
        .callback = button_isr,
        .callback_arg = NULL,
    });
    cyhal_gpio_enable_event(CYBSP_USER_BTN, CYHAL_GPIO_IRQ_BOTH, CYHAL_ISR_PRIORITY_DEFAULT, true);

    while (true)
    {
        // Check if the ISR flagged a button state change
        if (btn_state_changed)
        {
            btn_state_changed = false;

            // Read the current button state
            bool curr_btn_state = cyhal_gpio_read(CYBSP_USER_BTN);

            // Toggle the LED only on the rising edge (high flank)
            if (curr_btn_state == CYBSP_BTN_PRESSED && prev_btn_state == CYBSP_BTN_OFF)
            {
                cyhal_gpio_toggle(CYBSP_USER_LED); // Toggle the user LED
                printf("Button Task: User LED toggled on button press.\n");
            }

            // Prepare the MQTT message
            cy_mqtt_publish_info_t msg;
            msg.topic = MQTT_BTN_TOPIC;
            msg.topic_len = strlen(MQTT_BTN_TOPIC);
            msg.retain = false;
            msg.payload = (curr_btn_state == CYBSP_BTN_PRESSED) ? "ON" : "OFF";
            msg.payload_len = strlen(msg.payload);

            // Send the message to the queue
            if (xQueueSend(DataQueue, &msg, portMAX_DELAY) != pdTRUE)
            {
                printf("Button Task: Failed to send data to publisher task.\n");
            }
            else
            {
                printf("Button Task: Sent '%s' to publisher task.\n", (char *)msg.payload);
            }

            // Update the previous button state
            prev_btn_state = curr_btn_state;
        }

        // Add a small delay to avoid busy-looping
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

/******************************************************************************
* Button ISR
******************************************************************************/
static void button_isr(void *callback_arg, cyhal_gpio_event_t event)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Mark that a button state change occurred
    btn_state_changed = true;

    // Request a context switch if necessary
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
