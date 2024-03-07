#pragma once
#include "EEPROM.h"
#include "Arduino.h"

#define MAX_NUMBER_OF_CHANNELS 8
#define INITIAL_ADDR 100
#define DEFAULT_COMMAND 1
#define DEFAULT_VALUE 0

typedef struct{
  uint8_t command;
  uint8_t channel;
  int value;
}command_t;

void init_channels();
void read_config_epprom(command_t* current_ch_configurations[MAX_NUMBER_OF_CHANNELS]);
void update_config_epprom(command_t new_configuration);