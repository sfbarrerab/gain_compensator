#pragma once
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "serial_communication.h"

// Define an array of Arduino analog ports
const int analog_input_ports[MAX_NUMBER_OF_CHANNELS] = {A0, A1, A2, A3, A4, A5, A6, A7};
const int analog_output_ports[MAX_NUMBER_OF_CHANNELS] = {2, 3, 4, 5, 6, 7, 8, 12}; // channel 9 is used by TFT dispaly

void task_analogue_read_write(void *pvParameters);
