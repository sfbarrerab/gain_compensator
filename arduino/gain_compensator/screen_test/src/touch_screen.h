#pragma once
#include <Arduino.h>
#include <Wire.h>      // this is needed for FT6206
#include <Adafruit_FT6206.h>

#include <SPI.h>
#include <TFT_eSPI.h>

#define DISPLAY_PIXEL_HEIGHT 240
#define DISPLAY_PIXEL_WIDTH 320

extern int x,y;

void init_touch_screen();
void task_touch_screen(void *pvParameters);

