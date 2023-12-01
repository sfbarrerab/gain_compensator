#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "serial_communication.h"
#include "analog_read_write.h"


void setup() {
    Serial.begin(115200);
    Serial.setTimeout(10); // This time might be increased if the string is large

    if ( x_serial_txrx_semaphore == NULL )  // Check to confirm that the Serial Semaphore has not already been created.
    {
        x_serial_txrx_semaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore
        if ( ( x_serial_txrx_semaphore ) != NULL )
            xSemaphoreGive( ( x_serial_txrx_semaphore ) );  // Make the Serial Port available for use
    }

    // Create 2 queues of 10 elements for possible commands and messages
    x_received_commands_queue = xQueueCreate(QUEUE_LEN, sizeof(command_t)); 
    x_messages_to_send_queue = xQueueCreate(QUEUE_LEN,sizeof(message_t)); 
    
    // Create task
    xTaskCreate(
      task_rx_serial
      ,  "Rx for serial communication"   // name
      ,  128  // stack size
      ,  NULL
      ,  2  // Priority 
      ,  NULL );

    xTaskCreate(
      task_tx_serial
      ,  "Tx for serial communication"   // name
      ,  128  // stack size
      ,  NULL
      ,  2  // Priority 
      ,  NULL );

    xTaskCreate(
      task_analogue_read_write
      ,  "Analogue ports reading writing"   // name
      ,  128  // stack size
      ,  NULL
      ,  2  // Priority 
      ,  NULL );
    
    // Task scheduler is automatically initiated

}

void loop() {
   // task already setup run the whole process

}
