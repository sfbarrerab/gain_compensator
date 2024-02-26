#include "serial_communication.h"

// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
SemaphoreHandle_t x_serial_txrx_semaphore;

// Queue to handle messages between serial task and analog ports task
QueueHandle_t x_received_commands_queue;
QueueHandle_t x_messages_to_send_to_pc_queue;

// Function to store the received command into the final structure
uint8_t command_to_structure(String command, command_t *received_message){

  // Validation of the input string
  if(!(command.length()>0)){
    return -1;
  }else{
    uint8_t questionMarkCount = 0;
    for (uint8_t i = 0; i < command.length(); i++) {
      if (command.charAt(i) == '?') {
        questionMarkCount++;
      }
    }
    if(questionMarkCount != 2){
      return -1;
    }
  }

  // Get the positions of the separator "?"
  uint8_t question_mark_index1 = command.indexOf('?');
  uint8_t question_mark_index2 = command.indexOf('?', question_mark_index1 + 1);

  // Store the values in the structure
  received_message->command = command.substring(0, question_mark_index1).toInt();
  received_message->channel = command.substring(question_mark_index1 + 1, question_mark_index2).toInt()-1;
  received_message->value = command.substring(question_mark_index2 + 1).toInt();

  // Validation of the received values
  if(!(received_message->command == 0 || received_message->command == 1)){
    return -1;
  }

  if(received_message->channel > MAX_NUMBER_OF_CHANNELS-1){
    return -1;
  }

  if(received_message->value > MAX_VALUE-1){
    return -1;
  }

  return 0;
}

void task_txrx_serial(void *pvParameters){
  command_t received_message;
  command_t message_to_send;

  while(true){
    // take the semaphore if there is an incomming message
    while (Serial.available()){
      if ( xSemaphoreTake( x_serial_txrx_semaphore, SEMAPHORE_BLOCK_TIME ) == pdTRUE )
      {  
        String command_received = Serial.readString();
        command_received.trim(); // remove \n character
        if(!command_to_structure(command_received , &received_message)){
          if(xQueueSend(x_received_commands_queue,(void *)&received_message, QUEUE_SEND_BLOCK_TIME) == pdTRUE){
            // Confirmation message when writing
            if(received_message.command){
              Serial.print("Writing ");
              Serial.print(received_message.value);
              Serial.print(" in channel ");
              Serial.println(received_message.channel + 1);
            }
          }
        }else{
          Serial.print("The command received (");
          Serial.print(command_received);   
          Serial.println(") does not have the right structure/parameters.");
        }

        xSemaphoreGive( x_serial_txrx_semaphore );  // give the semaphore
      }
    }

    if(x_messages_to_send_to_pc_queue != NULL && xQueueReceive(x_messages_to_send_to_pc_queue, (void *)&message_to_send, 0) == pdTRUE)
    {
      if ( xSemaphoreTake( x_serial_txrx_semaphore, SEMAPHORE_BLOCK_TIME ) == pdTRUE ){
        // Serial.print("Channel: ");
        // Serial.print(message_to_send.channel + 1);

        // Serial.print(", Value: ");
        // Serial.println(message_to_send.value);
        xSemaphoreGive( x_serial_txrx_semaphore );
      }
    }
    vTaskDelay( 15 / portTICK_PERIOD_MS);
  }
  
}