#include "gui_powers_page.h"

gui_powers_page_t powers_page;

void init_powers_page(){

  tft.fillRect(MENU_BTN_WIDTH,0,SCREEN_WIDTH-MENU_BTN_WIDTH,SCREEN_HEIGHT,ILI9341_BLACK);

  for(int i = 0; i < MAX_NUMBER_OF_CHANNELS; i++){
    String label_channel_power = "Ch ";
    label_channel_power += String(i+1);
    label_channel_power += ": ";
    powers_page.channels_power[i] = new Textbox(TEXTBOX_X0,PADDING+((i%4)*SCREEN_HEIGHT/4),(SCREEN_WIDTH-MENU_BTN_WIDTH)/2,10,label_channel_power.c_str(),NULL,ILI9341_BLACK);
  }
}

void update_gui_powers_page(){
  
  for(int i = 0; i < MAX_NUMBER_OF_CHANNELS; i++){
    String label_channel_power = "Ch ";
    label_channel_power += String(i+1);
    label_channel_power += ": ";
    powers_page.channels_power[i]->update_state(tft);
  }
}

void delete_powers_page(){
  for(int i = 0; i < MAX_NUMBER_OF_CHANNELS; i++){
    delete powers_page.channels_power[i];
  }
}