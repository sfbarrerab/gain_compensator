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
extern QueueHandle_t x_messages_to_send_queue;

typedef struct{
    uint8_t command;
    uint8_t channel;
    int value;
}command_t;

typedef struct{
    uint8_t channel;
    int value;
}message_t;

void task_rx_serial(void *pvParameters);
void task_tx_serial(void *pvParameters);
