#include "gui_status_page.h"

gui_status_page_t status_page;

void init_status_page(){
  tft.fillRect(MENU_BTN_WIDTH,0,SCREEN_WIDTH-MENU_BTN_WIDTH,SCREEN_HEIGHT,ILI9341_BLACK);
  command_t* current_ch_configurations[MAX_NUMBER_OF_CHANNELS];

  // Allocate memory for each command_t structure
  for (uint8_t i = 0; i < MAX_NUMBER_OF_CHANNELS; i++) {
    current_ch_configurations[i] = new command_t;
  }

  read_config_epprom(current_ch_configurations);

  String header = " Channel     Constant     Value";
  status_page.header_status = new Textbox(MENU_BTN_WIDTH+2*PADDING,2*PADDING,SCREEN_WIDTH-MENU_BTN_WIDTH,8,header.c_str(),NULL,ILI9341_BLACK,ILI9341_BLUE,1,NULL);

  for(uint8_t i = 0; i < MAX_NUMBER_OF_CHANNELS; i++){
    String channel_status = "";
    channel_status += "Channel " + String (i+1) + "     ";
    if(current_ch_configurations[i]->command == 1){
      channel_status += "Atten.      ";
    }else if(current_ch_configurations[i]->command == 2){
      channel_status += "Power       ";
    }else{
      channel_status += "NA          ";
    }
    channel_status += String(current_ch_configurations[i]->value) + " dB";
    status_page.channels_status[i] = new Textbox(MENU_BTN_WIDTH+2*PADDING,2*PADDING + (i+1)*SPACING_BETWEEN_LINES,SCREEN_WIDTH-MENU_BTN_WIDTH,8,channel_status.c_str(),NULL,ILI9341_BLACK,ILI9341_WHITE,1,NULL);
    status_page.channels_status[i]->init_label(tft);
  }
  status_page.header_status->init_label(tft);
  // Free dynamically allocated memory
  for (uint8_t i = 0; i < MAX_NUMBER_OF_CHANNELS; i++) {
    delete current_ch_configurations[i];
  }
}

void delete_status_page(){
  for(int i = 0; i < MAX_NUMBER_OF_CHANNELS; i++){
    delete status_page.channels_status[i];
  }
  delete status_page.header_status;
}