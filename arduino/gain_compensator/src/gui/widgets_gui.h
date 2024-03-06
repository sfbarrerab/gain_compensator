
/*
  Library writen by Santiago Barrera

  The library pourpose is being able to use Adafruit ILI9341 and GFX library to create
  some widgets in slow microcontrollers, like arduino uno or arduino mega, where 
  you cannot use LVGL, for example.

  As it is limited to Adafruit GFX library, some of the widgets are roughly created, with
  pixel-pushed parameters. So, be patient with it.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/

#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>       // this is needed for display
#include <Adafruit_ILI9341.h>
#include "serial_communication.h"


#define DEBOUNCE_TIME 20

class Widget {
public:
  Widget(int x, int y, int width, int height, const char* label, bool* gui_change_triggered);
  Widget(int x, int y, int radious, const char* label, bool* gui_change_triggered);
  virtual ~Widget();

  virtual void update_state(int x_touch, int y_touch, Adafruit_ILI9341 tft);
  bool is_disabled() const;
  void set_disabled(bool value);

protected:
  int x, y, width, height, radious;
  const char* label;
  bool disabled;
  bool* gui_change_triggered;
};

class Button : public Widget {
public:
  Button(int x, int y, int width, int height, const char* label, void (*callback)(), bool* gui_change_triggered);

  void is_released(Adafruit_ILI9341 tft);
  void is_pressed(Adafruit_ILI9341 tft);
  void update_state(int x_touch, int y_touch, Adafruit_ILI9341 tft) override;

  void set_label(const char* label);
  const char* get_label() const;

  void set_callback(void (*callback)());


private:
  void (*callback)(); // Callback function pointer
  unsigned long last_debounce_time;
  bool last_touch_processed;
};


class Slider : public Widget {
public:
  Slider(int x, int y, int width, int height, int min_value, int max_value, int* value, const char* label,int r_slider, bool* gui_change_triggered);

  void change_label(const char* new_label);
  void update_slider_value(int x_touched);
  int value_to_x_position(int val);
  void init_slider(Adafruit_ILI9341 tft);
  void update_state(int x_touch, int y_touch, Adafruit_ILI9341 tft);

private:
  int min_value, max_value, r_slider;
  int* value;
};


class Radio : public Widget {
public:
  Radio(int x, int y, int radious, bool* selected, const char* label, bool* gui_change_triggered);

  void init_radiobox(Adafruit_ILI9341 tft);
  void update_state(int x_touch, int y_touch, Adafruit_ILI9341 tft) override;


private:
  bool* selected;
  unsigned long last_debounce_time;
  bool last_touch_processed;
};


class Textbox : public Widget {
public:
  Textbox(int x, int y, int width, int height, const char* label, bool* gui_change_triggered, int outline_color, int text_color, int text_size, const char* mini_label);

  void update_label(Adafruit_ILI9341 tft, const char* new_label);
  void init_label(Adafruit_ILI9341 tft);
private:
  int outline_color, text_color, text_size;
  const char* mini_label;
};