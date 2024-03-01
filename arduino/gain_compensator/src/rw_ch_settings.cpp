#include "rw_ch_settings.h"

command_t previous_configuration[MAX_NUMBER_OF_CHANNELS];

void init_channels(){

  for(uint8_t i = 0; i < MAX_NUMBER_OF_CHANNELS; i++){
    previous_configuration[i] = {NULL, NULL, NULL};
    EEPROM.get(INITIAL_ADDR+i*sizeof(command_t),previous_configuration[i]);
    
    // init the space if no previous setting was configured
    if(previous_configuration[i].command == NULL){
      previous_configuration[i].channel = i;
      previous_configuration[i].command = NULL;
      previous_configuration[i].value = NULL;
    }

  }
}

void update_config_epprom(command_t new_configuration){
  EEPROM.put(INITIAL_ADDR+new_configuration.channel*sizeof(command_t),new_configuration);
}

void read_config_epprom(){
  
  for(uint8_t i = 0; i < MAX_NUMBER_OF_CHANNELS; i++){
    EEPROM.get(INITIAL_ADDR+i*sizeof(command_t),previous_configuration[i]);

    Serial.println("Channel "+ String(i+1) + " settings:");
    Serial.println(previous_configuration[i].channel);
    Serial.println(previous_configuration[i].command);
    Serial.println(previous_configuration[i].value);
  }
}