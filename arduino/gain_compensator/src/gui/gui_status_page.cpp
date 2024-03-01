#include "gui_set_page.h"

void init_status_page(){
  tft.fillRect(MENU_BTN_WIDTH,0,SCREEN_WIDTH-MENU_BTN_WIDTH,SCREEN_HEIGHT,ILI9341_BLACK);
  command_t* current_ch_configurations[MAX_NUMBER_OF_CHANNELS];

  // Allocate memory for each command_t structure
  for (uint8_t i = 0; i < MAX_NUMBER_OF_CHANNELS; i++) {
    current_ch_configurations[i] = new command_t;
  }

  read_config_epprom(current_ch_configurations);
  for(uint8_t i = 0; i < MAX_NUMBER_OF_CHANNELS; i++){
    Serial.println("Channel "+ String(i+1) + " settings:");
    Serial.println(current_ch_configurations[i]->channel);
    Serial.println(current_ch_configurations[i]->command);
    Serial.println(current_ch_configurations[i]->value);
  }

  // Free dynamically allocated memory
  for (uint8_t i = 0; i < MAX_NUMBER_OF_CHANNELS; i++) {
    delete current_ch_configurations[i];
  }
}