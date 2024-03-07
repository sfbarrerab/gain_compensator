#include "analog_read_write.h"

QueueHandle_t x_messages_to_send_to_gui_queue;

void task_analogue_read_write(void *pvParameters){
  command_t received_command;
  command_t message_to_send;

  while(1)
  {
    // If the queue has been already created and it has an element then...
    if(x_received_commands_queue != NULL && xQueueReceive(x_received_commands_queue, (void *)&received_command, 0) == pdTRUE){
      message_to_send.command = received_command.command;
      message_to_send.channel = received_command.channel;
      message_to_send.value = received_command.value;
      if(received_command.command == 0) // Read
      {
        message_to_send.value = analogRead(analog_input_ports[received_command.channel]);
      }else if (received_command.command == 1) //Set attenuation
      {
        // write the value in the selected channel
        analogWrite(analog_output_ports[received_command.channel],received_command.value);
        update_config_epprom(received_command);
      }else if (received_command.command == 2) // Set target power level - PID
      {
        // activate PID algorithm
        update_config_epprom(received_command);
      }else if(received_command.command == 4){ // The reading was received from the pc
        message_to_send.value = analogRead(analog_input_ports[received_command.channel]);  
        if(x_messages_to_send_to_pc_queue != NULL){
          xQueueSend(x_messages_to_send_to_pc_queue,(void *)&message_to_send, QUEUE_SEND_BLOCK_TIME);
        }
      }

      // Send the full message also to the GUI queue to print message in popup
      if(x_messages_to_send_to_gui_queue != NULL){
        xQueueSend(x_messages_to_send_to_gui_queue,(void *)&message_to_send, QUEUE_SEND_BLOCK_TIME);
      }
    }
    vTaskDelay( 5 / portTICK_PERIOD_MS);
  }
}

void initi_analog_output_channels(){
  command_t* current_ch_configurations[MAX_NUMBER_OF_CHANNELS];

  // Allocate memory for each command_t structure
  for (uint8_t i = 0; i < MAX_NUMBER_OF_CHANNELS; i++) {
    current_ch_configurations[i] = new command_t;
  }

  read_config_epprom(current_ch_configurations);

  // Apply configuration
  for (uint8_t i = 0; i < MAX_NUMBER_OF_CHANNELS; i++) {
    if(current_ch_configurations[i]->command == 1){
      analogWrite(analog_output_ports[current_ch_configurations[i]->channel],current_ch_configurations[i]->value);
    }else if (current_ch_configurations[i]->command == 2){
      // activate the PID
    }
  }

  // Free dynamically allocated memory
  for (uint8_t i = 0; i < MAX_NUMBER_OF_CHANNELS; i++) {
    delete current_ch_configurations[i];
  }
}