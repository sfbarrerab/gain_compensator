#include "gui_mainpage.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

gui_mainpage_t mainpage;
Screens current_screen;



void init_main_page(){

	tft.fillScreen(ILI9341_BLACK);

	mainpage.set_page_button = new Button(0, 0, MENU_BTN_WIDTH, MENU_BTN_HEIGHT, "Set", NULL, NULL);
	mainpage.powers_page_button = new Button(0, MENU_BTN_HEIGHT, MENU_BTN_WIDTH, MENU_BTN_HEIGHT, "Powers", NULL, NULL);
	mainpage.attenuations_page_button = new Button(0, 2*MENU_BTN_HEIGHT, MENU_BTN_WIDTH, MENU_BTN_HEIGHT, "Atten.", NULL, NULL);

	mainpage.set_page_button->is_released(tft);
	mainpage.powers_page_button->is_released(tft);
	mainpage.attenuations_page_button->is_released(tft);
}


void update_gui_main_page()
{
	mainpage.set_page_button->update_state(x,y,tft);
	mainpage.powers_page_button->update_state(x,y,tft);
	mainpage.attenuations_page_button->update_state(x,y,tft);
}

void delete_main_page(){
	delete mainpage.set_page_button;
	delete mainpage.powers_page_button;
	delete mainpage.attenuations_page_button;
}
