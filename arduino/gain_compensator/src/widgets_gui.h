
/*
Library writen by Santiago Barrera

The library pourpose is being able to use Adafruit ILI9341 library to create
some widgets in slow microcontrollers, like arduino uno or arduino mega, where 
you cannot use LVGL, for example.

As it is limited to Adafruit library, some of the widgets are roughly created, with
pixel-pushed parameters. So, be patient with it.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
The above copyright notice and this permissio notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. InO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


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
  Widget(int x, int y, int width, int height, const char* label);
  Widget(int x, int y, int radious, const char* label);

  virtual int get_status() const = 0;
  virtual void update_state(int x_touch, int y_touch, Adafruit_ILI9341 tft);

  bool is_disabled() const;
  void set_disabled(bool value);

protected:
  int x, y, width, height, radious;
  bool disabled;
  const char* label;
};

#define DEBOUNCE_TIME 50

class Button : public Widget {
public:
  Button(int x, int y, int width, int height, const char* label, void (*callback)());

  int get_status() const override;
  void is_released(Adafruit_ILI9341 tft);
  void is_pressed(Adafruit_ILI9341 tft);
  void update_state(int x_touch, int y_touch, Adafruit_ILI9341 tft) override;

  void set_label(const char* label);
  const char* get_label() const;

  void set_callback(void (*callback)());


private:
  void (*callback)(); // Callback function pointer
  bool status;
  bool disabled;
  unsigned long last_debounce_time;
};


class Slider : public Widget {
public:
  Slider(int x, int y, int width, int height, int minValue, int maxValue, int* value, const char* label);

  int get_status() const override;

  void setValue(int newValue);
  int getValue() const;

private:
  int minValue, maxValue;
  int* value;
};


class Checkbox : public Widget {
public:
  Checkbox(int x, int y, int radious, bool* checked, const char* label);

  int get_status() const override;

  void is_checked(Adafruit_ILI9341 tft);
  void is_not_checked(Adafruit_ILI9341 tft);
  void update_state(int x_touch, int y_touch, Adafruit_ILI9341 tft) override;


private:
  bool* checked;
  unsigned long last_debounce_time;
  bool last_touch_processed;
};