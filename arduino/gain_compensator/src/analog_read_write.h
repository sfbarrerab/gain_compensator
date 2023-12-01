#pragma once
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "serial_communication.h"

// Define an array of Arduino analog ports
const int analog_input_ports[4] = {A0, A1, A2, A3};
const int analog_output_ports[4] = {A4, A5, A6, A7};

typedef struct{
    uint8_t channel;
    int value;
}message_t;

extern QueueHandle_t x_messages_to_send_queue;

void task_analogue_read_write(void *pvParameters);
