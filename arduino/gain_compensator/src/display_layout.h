#pragma once
#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>       // this is needed for display
#include <Adafruit_ILI9341.h>
#include <Wire.h>      // this is needed for FT6206
#include <Adafruit_FT6206.h>
#include <Arduino_FreeRTOS.h>
#include "serial_communication.h"

// The display uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
// Size of the color selection boxes and the paintbrush size
#define BOXSIZE 40
#define PENRADIUS 3

void init_tft();
void task_display(void *pvParameters);