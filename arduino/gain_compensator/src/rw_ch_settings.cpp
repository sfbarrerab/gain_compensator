#include "rw_ch_settings.h"

command_t previous_configuration[MAX_NUMBER_OF_CHANNELS];

void init_channels(){

  for(uint8_t i = 0; i < MAX_NUMBER_OF_CHANNELS; i++){
    previous_configuration[i] = {NULL, NULL, NULL};
    EEPROM.get(INITIAL_ADDR+i*sizeof(command_t),previous_configuration[i]);
    
    // if no previous setting was configured, set default values
    if(previous_configuration[i].command == NULL){
      previous_configuration[i].channel = i;
      previous_configuration[i].command = DEFAULT_COMMAND;
      previous_configuration[i].value = DEFAULT_VALUE;
    }

  }
}

void update_config_epprom(command_t new_configuration){
  EEPROM.put(INITIAL_ADDR+new_configuration.channel*sizeof(command_t),new_configuration);
}

void read_config_epprom(command_t* current_ch_configurations[MAX_NUMBER_OF_CHANNELS]){
    
  for(uint8_t i = 0; i < MAX_NUMBER_OF_CHANNELS; i++){
    EEPROM.get(INITIAL_ADDR+i*sizeof(command_t),*current_ch_configurations[i]);
  }
}