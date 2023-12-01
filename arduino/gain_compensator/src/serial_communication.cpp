#include "serial_communication.h"

// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
SemaphoreHandle_t x_serial_txrx_semaphore;

// Queue to handle messages between serial task and analog ports task
QueueHandle_t x_commands_queue;

void task_rxtx_serial(void *pvParameters){

    command_t received_message;
    // Create a queue of 10 elements of possible commands
    x_commands_queue = xQueueCreate(10, sizeof(command_t));  
  
    while(true){
        // take the semaphore, if not available wait for 5ms
        if ( xSemaphoreTake( x_serial_txrx_semaphore, ( TickType_t ) 5 ) == pdTRUE )
        {
            while (!Serial.available());
            double value = Serial.readString().toDouble();
            Serial.println(value+1.0);
            xSemaphoreGive( x_serial_txrx_semaphore );  // give the semaphore
        }
        vTaskDelay( 15 / portTICK_PERIOD_MS);
  }
  
}

