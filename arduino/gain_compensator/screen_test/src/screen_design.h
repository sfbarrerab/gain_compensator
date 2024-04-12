#pragma once
#include "FS.h"
#include "Free_Fonts.h" // Include the header file attached to this sketch
#include <TFT_eSPI.h>
#include <TFT_eWidget.h>           // Widget library
#include "touch_screen.h"

void init_layout_screen();
void task_screen_layout(void *pvParameters);