#include "serial_communication.h"

// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
SemaphoreHandle_t x_serial_txrx_semaphore;

// Queue to handle messages between serial task and analog ports task
QueueHandle_t x_received_commands_queue;
QueueHandle_t x_messages_to_send_queue;

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

void task_rx_serial(void *pvParameters){
    command_t received_message;
  
    while(true){
        // take the semaphore, if not available wait for 2ms
        if ( xSemaphoreTake( x_serial_txrx_semaphore, SEMAPHORE_BLOCK_TIME ) == pdTRUE )
        {
            while (!Serial.available());
            String command_received = Serial.readString();
            command_to_structure(command_received , &received_message);
            // send the message into the Queue
            Serial.print("Command received: ");
            Serial.println(command_received);
            xQueueSend(x_received_commands_queue,(void *)&received_message, QUEUE_SEND_BLOCK_TIME);
            xSemaphoreGive( x_serial_txrx_semaphore );  // give the semaphore
        }
        vTaskDelay( 15 / portTICK_PERIOD_MS);
  }
  
}

void task_tx_serial(void *pvParameters){
    message_t message_to_send;
  
    while(true){
        if(x_messages_to_send_queue != NULL && xQueueReceive(x_messages_to_send_queue, (void *)&message_to_send, 0) == pdTRUE)
        {
            if ( xSemaphoreTake( x_serial_txrx_semaphore, portMAX_DELAY ) == pdTRUE )
            {
                while (!Serial.available());
                Serial.print("Channel: ");
                Serial.println(message_to_send.channel);

                Serial.print("Value: ");
                Serial.println(message_to_send.value);

                xSemaphoreGive( x_serial_txrx_semaphore );  // give the semaphore
            }
        }
        vTaskDelay( 15 / portTICK_PERIOD_MS);
  }
  
}