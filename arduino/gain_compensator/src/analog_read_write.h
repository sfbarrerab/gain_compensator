#pragma once
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "serial_communication.h"

void task_analogue_read_write(void *pvParameters);
