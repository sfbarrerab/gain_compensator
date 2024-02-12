#pragma once
#include "gui_mainpage.h"

#define TFT_CS 10
#define TFT_DC 9

typedef struct confirmation_popup_t
{
  Button* close_button;
} confirmation_popup_t;


void submit_popup();