#include "gui_popup.h"

confirmation_popup_t submit_popup_layout;

void submit_popup(){
  submit_popup_layout.close_button = new Button(150, 150, 70, 30, "Close", NULL, NULL);
	submit_popup_layout.close_button->is_released(tft);
}