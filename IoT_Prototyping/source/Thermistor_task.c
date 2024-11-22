#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "mtb_thermistor_ntc_gpio.h"
#include "cy_mqtt_api.h"
#include <stdio.h>
#include "string.h"
#include "Thermistor_task.h"

/* Macros */
#define THERMISTOR_VDD_PIN            P10_3
#define THERMISTOR_OUT_PIN            P10_1
#define THERMISTOR_GND_PIN            P10_0
#define REFERENCE_RESISTOR            (float)(10000)
#define BETA_CONSTANT                 (float)(3380)
#define INFINITY_RESISTANCE           (float)(0.1192855)

/* Global Variables */
TaskHandle_t thermistor_task_handle;
uint32_t temperature;
cyhal_adc_t adc;
mtb_thermistor_ntc_gpio_t thermistor;
mtb_thermistor_ntc_gpio_cfg_t thermistor_cfg = {
    .r_ref = REFERENCE_RESISTOR,
    .b_const = BETA_CONSTANT,
    .r_infinity = INFINITY_RESISTANCE,
};

/* Function to initialize the thermistor and ADC */
static void thermistor_init(void)
{
    cy_rslt_t result;

    /* Initialize the ADC */
    result = cyhal_adc_init(&adc, THERMISTOR_OUT_PIN, NULL);

    /* Initialize the thermistor */
    result = mtb_thermistor_ntc_gpio_init(&thermistor, &adc,
        THERMISTOR_GND_PIN, THERMISTOR_VDD_PIN, THERMISTOR_OUT_PIN,
        &thermistor_cfg, MTB_THERMISTOR_NTC_WIRING_VIN_NTC_R_GND);

    CY_ASSERT(result == CY_RSLT_SUCCESS);
}

/* Function to read temperature from the thermistor */
static float read_thermistor(void)
{
    return (float) mtb_thermistor_ntc_gpio_get_temp(&thermistor);
}

static void publish_temperature(float temperature)
{
    /* Dynamically allocate memory for the message */
    char *message = pvPortMalloc(10); // Allocate memory for the payload
    if (message == NULL)
    {
        printf("Thermistor Task: Failed to allocate memory for payload.\n");
        return;
    }

    snprintf(message, 10, "%.2f", temperature); // Format the temperature value as a string

    /* Configure MQTT message */
    cy_mqtt_publish_info_t msg;
    msg.topic = MQTT_THERMISTOR_TOPIC;
    msg.topic_len = strlen(MQTT_THERMISTOR_TOPIC);
    msg.payload = message; // Pointer to the dynamically allocated buffer
    msg.payload_len = strlen(message);
    msg.retain = false;

    /* Send the message to the queue */
    if (xQueueSend(DataQueue, &msg, portMAX_DELAY) != pdTRUE)
    {
        printf("Thermistor Task: Failed to send data to publisher task.\n");
        vPortFree(message); // Free memory in case of failure
    }
    else
    {
        printf("Thermistor Task: Sent temperature '%.2f' to publisher task.\n", temperature);
    }
}



/* Thermistor task that reads the thermistor value and publishes it */
void thermistor_task(void *pvParameters)
{
    thermistor_init();

    while (true)
    {
        /* Read thermistor value */
        float temperature = read_thermistor();

        /* Publish temperature to MQTT */
        publish_temperature(temperature);
        /* Wait before publishing again (every 10 seconds) */
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}
