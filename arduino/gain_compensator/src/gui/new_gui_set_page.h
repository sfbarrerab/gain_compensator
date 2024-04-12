#pragma once
//#include "FS.h"
#include "Free_Fonts.h" // Include the header file attached to this sketch
#include <TFT_eSPI.h>
#include <TFT_eWidget.h>           // Widget library
#include <Wire.h>      // this is needed for FT6206
#include <Adafruit_FT6206.h>
#include "touch_screen.h"


void test_slider_screen(void *pvParameters);
void init_setup_screen();