#include "serial_communication.h"

// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
SemaphoreHandle_t x_serial_txrx_semaphore;

// Queue to handle messages between serial task and analog ports task
QueueHandle_t x_received_commands_queue;

// Function to store the received command into the final structure
void command_to_structure(String command, command_t *received_message){
    // Get the positions of the separator "?"
    int question_mark_index1 = command.indexOf('?');
    int question_mark_index2 = command.indexOf('?', question_mark_index1 + 1);

    // Store the values in the structure
    received_message->command = command.substring(0, question_mark_index1).toInt();
    received_message->channel = command.substring(question_mark_index1 + 1, question_mark_index2).toInt();
    received_message->value = command.substring(question_mark_index2 + 1).toInt();
}

void task_rxtx_serial(void *pvParameters){
    command_t received_message;
    // Create a queue of 10 elements of possible commands
    x_received_commands_queue = xQueueCreate(10, sizeof(command_t));  
  
    while(true){
        // take the semaphore, if not available wait for 2ms
        if ( xSemaphoreTake( x_serial_txrx_semaphore, ( TickType_t ) 2 ) == pdTRUE )
        {
            while (!Serial.available());
            String command_received = Serial.readString();
            command_to_structure(command_received , &received_message);
            // send the message into the Queue
            xQueueSend(x_received_commands_queue,(void *)&received_message, 0);
            xSemaphoreGive( x_serial_txrx_semaphore );  // give the semaphore
        }
        vTaskDelay( 15 / portTICK_PERIOD_MS);
  }
  
}