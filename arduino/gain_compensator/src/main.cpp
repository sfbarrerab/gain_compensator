#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>


void task_rxtx_serial(void *pvParameters);

// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
SemaphoreHandle_t x_serial_txrx_semaphore;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10); // This time might be increased if the string is large

  if ( x_serial_txrx_semaphore == NULL )  // Check to confirm that the Serial Semaphore has not already been created.
  {
    x_serial_txrx_semaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore
    if ( ( x_serial_txrx_semaphore ) != NULL )
      xSemaphoreGive( ( x_serial_txrx_semaphore ) );  // Make the Serial Port available for use
  }
  
  // Create task
  xTaskCreate(
    task_rxtx_serial
    ,  "Rx Tx serial communication"   // name
    ,  128  // stack size
    ,  NULL
    ,  2  // Priority 
    ,  NULL );
  
  // Task scheduler is automatically initiated

}

void loop() {
  // task already setup run the whole process

}

void task_rxtx_serial(void *pvParameters){
  
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


// Adding a comment to check if the gitlab from FAU gets updates automatically