#include "analog_read_write.h"

void task_analogue_read_write(void *pvParameters){

    command_t received_command;
    while(1)
    {
        // If the queue has been already created and it has an element
        if(x_commands_queue != NULL && xQueueReceive(x_commands_queue, (void *)&received_command, 0) == pdTRUE){

        }
    }
}