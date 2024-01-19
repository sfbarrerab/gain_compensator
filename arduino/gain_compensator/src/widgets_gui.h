#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>       // this is needed for display
#include <Adafruit_ILI9341.h>
#include <Wire.h>      // this is needed for FT6206
#include <Adafruit_FT6206.h>
#include <Arduino_FreeRTOS.h>
#include "serial_communication.h"
#include <TouchScreen.h>

class Widget {
public:
  Widget(int x, int y, int width, int height);

  virtual int get_status() const = 0;
  virtual void draw_widget(Adafruit_ILI9341 tft);

  bool is_disabled() const;
  void set_disabled(bool value);

protected:
  int x, y, width, height;
  bool disabled;
};

#define DEBOUNCE_TIME 50

class Button : public Widget {
public:
  Button(int x, int y, int width, int height, const char* label, void (*callback)());

  int get_status() const override;
  void is_released(Adafruit_ILI9341 tft);
  void is_pressed(Adafruit_ILI9341 tft);
  void update_button_state(int x_touch, int y_touch, Adafruit_ILI9341 tft);

  void set_label(const char* label);
  const char* get_label() const;

  void set_callback(void (*callback)());


private:
  const char* label;
  void (*callback)(); // Callback function pointer
  bool status;
  bool disabled;
  unsigned long last_debounce_time;
};


class Slider : public Widget {
public:
  Slider(int x, int y, int width, int height, int minValue, int maxValue, int* value);

  int get_status() const override;

  void setValue(int newValue);
  int getValue() const;

private:
  int minValue, maxValue;
  int* value;
};


class Checkbox : public Widget {
public:
  Checkbox(int x, int y, int width, int height, bool* checked);

  int get_status() const override;

  bool isChecked() const;

private:
  bool* checked;
};