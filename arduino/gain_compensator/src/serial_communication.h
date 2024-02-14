#pragma once
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

#define QUEUE_LEN 10
#define SEMAPHORE_BLOCK_TIME 15
#define QUEUE_SEND_BLOCK_TIME 15
#define MAX_NUMBER_OF_CHANNELS 8
#define MAX_VALUE 256

extern SemaphoreHandle_t x_serial_txrx_semaphore;
extern QueueHandle_t x_received_commands_queue;

typedef struct{
    uint8_t command;
    uint8_t channel;
    int value;
}command_t;

void task_txrx_serial(void *pvParameters);