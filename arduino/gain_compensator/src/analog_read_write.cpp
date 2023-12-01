#include "analog_read_write.h"

QueueHandle_t x_messages_to_send_queue;

void task_analogue_read_write(void *pvParameters){
    command_t received_command;
    message_t message_to_send;

    x_messages_to_send_queue = xQueueCreate(10,sizeof(message_t));

    while(1)
    {
        // If the queue has been already created and it has an element then...
        if(x_received_commands_queue != NULL && xQueueReceive(x_received_commands_queue, (void *)&received_command, 0) == pdTRUE){
            if(received_command.command == 0)
            {
                message_to_send.channel = received_command.channel;
                message_to_send.value = analogRead(analog_input_ports[received_command.channel]);
                if(x_messages_to_send_queue != NULL){
                    xQueueSend(x_messages_to_send_queue,(void *)&message_to_send,0);
                }
            }else if (received_command.command == 1)
            {
                // write the value in the selected channel
                analogWrite(analog_output_ports[received_command.channel],received_command.value);
            }
        }
        vTaskDelay( 10 / portTICK_PERIOD_MS);

    }
}