#pragma once
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

#define QUEUE_LEN 5
#define SEMAPHORE_TICKS_DELAY 5
#define QUEUE_TICKS_DELAY 5

extern SemaphoreHandle_t x_serial_txrx_semaphore;
extern QueueHandle_t x_received_commands_queue;

// Define strcture of the messages
typedef struct{
    uint8_t command;
    uint8_t channel;
    int value;
}command_t;

void task_rxtx_serial(void *pvParameters);
