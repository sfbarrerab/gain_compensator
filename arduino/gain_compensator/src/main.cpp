#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>
#include "serial_communication.h"
#include "analog_read_write.h"
#include "gui/gui_mainpage.h"
#include "touch_screen.h"
#include "gui/screen_displayed.h"
#include "rw_ch_settings.h"

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10); // This time might be increased if the string is large

  // Create semaphore for serial printing
  if ( x_serial_txrx_semaphore == NULL ) 
  {
    x_serial_txrx_semaphore = xSemaphoreCreateMutex();
    if ( ( x_serial_txrx_semaphore ) != NULL )
      xSemaphoreGive( ( x_serial_txrx_semaphore ) );
  }

  // Create queues of 10 elements for exchange of commands and response
  x_received_commands_queue = xQueueCreate(QUEUE_LEN, sizeof(command_t)); 
  x_messages_to_send_to_pc_queue = xQueueCreate(QUEUE_LEN,sizeof(command_t)); 
  x_messages_to_send_to_gui_queue = xQueueCreate(QUEUE_LEN,sizeof(command_t)); 
    
  // Init peripherials and setup home screen
	init_tft();
  init_touch_screen();
  init_set_page();
  init_channels();
  initi_analog_output_channels();


  // Create tasks 
  xTaskCreate(
    task_txrx_serial
    ,  "Tx and Rx for serial communication"
    ,  128  
    ,  NULL
    ,  2   
    ,  NULL );

  xTaskCreate(
    task_analogue_read_write
    ,  "Analogue ports reading writing"
    ,  128  
    ,  NULL
    ,  2   
    ,  NULL );

  xTaskCreate(
    task_touch_screen
    ,  "Touch screen coordinate acquisition"
    ,  128  
    ,  NULL
    ,  2   
    ,  NULL );

	xTaskCreate(
    task_print_display
    ,  "Display layout and data collection"
    ,  4096  
    ,  NULL
    ,  2   
    ,  NULL );
    
}

void loop() {
  // Hola mundo! :p 
  // Hello world!
  // Hallo Welt! 
}
