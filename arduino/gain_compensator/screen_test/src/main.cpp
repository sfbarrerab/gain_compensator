#include <Arduino.h>
#include "touch_screen.h"
#include "screen_design.h"

void setup() {
  Serial.begin(115200);
  //Serial.setTimeout(10); // This time might be increased if the string is large

  init_touch_screen();
  init_layout_screen();

  xTaskCreate(
    task_screen_layout
    ,  "Layout screen"
    ,  9062  
    ,  NULL
    ,  3   
    ,  NULL );

  xTaskCreate(
    task_touch_screen
    ,  "Touch screen coordinate acquisition"
    ,  1024  
    ,  NULL
    ,  2   
    ,  NULL );
}

void loop() {
  // Hola mundo! :p 
  // Hello world!
  // Hallo Welt! 
}
  