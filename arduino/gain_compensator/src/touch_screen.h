#pragma once
#include <Wire.h>      // this is needed for FT6206
#include <Adafruit_FT6206.h>
#include <Arduino_FreeRTOS.h>
//#include <TouchScreen.h>

#define DISPLAY_PIXEL_HEIGHT 240
#define DISPLAY_PIXEL_WIDTH 320

extern int x,y;
extern Adafruit_FT6206 ctp;

void init_touch_screen();
void task_touch_screen(void *pvParameters);

