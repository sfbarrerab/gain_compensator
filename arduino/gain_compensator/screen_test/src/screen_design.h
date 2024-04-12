#pragma once
#include "FS.h"
#include "Free_Fonts.h" // Include the header file attached to this sketch
#include <TFT_eSPI.h>
#include <TFT_eWidget.h>           // Widget library
#include "touch_screen.h"

#define SLIDER_WIDTH 12
#define SLIDER_LENGTH 180
#define SLIDER_KNOB_RADI 15
#define SLIDER_KNOB_WIDTH 15
#define SLIDER_KNOB_HEIGHT 25
#define SLIDER_DELAY 500

#define SLIDER_X0 50
#define SLIDER_Y0 50

#define DELTA_SLIDER_YPOS 100

void init_layout_screen();
void task_screen_layout(void *pvParameters);