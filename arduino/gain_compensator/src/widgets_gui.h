#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>       // this is needed for display
#include <Adafruit_ILI9341.h>
#include <Wire.h>      // this is needed for FT6206
#include <Adafruit_FT6206.h>
#include <Arduino_FreeRTOS.h>
#include "serial_communication.h"
#include <TouchScreen.h>


#define FRAME_X 210
#define FRAME_Y 180
#define FRAME_W 100
#define FRAME_H 50

#define REDBUTTON_X FRAME_X
#define REDBUTTON_Y FRAME_Y
#define REDBUTTON_W (FRAME_W/2)
#define REDBUTTON_H FRAME_H

#define GREENBUTTON_X (REDBUTTON_X + REDBUTTON_W)
#define GREENBUTTON_Y FRAME_Y
#define GREENBUTTON_W (FRAME_W/2)
#define GREENBUTTON_H FRAME_H

class Widget {
public:
  Widget(int x, int y, int width, int height);

  virtual void onTouch() = 0;
  virtual int getStatus() const = 0;
  virtual void draw_widget(Adafruit_ILI9341 tft) const;

  bool isDisabled() const;
  void setDisabled(bool value);

protected:
  int x, y, width, height;
  bool disabled;
};


class Button : public Widget {
public:
  Button(int x, int y, int width, int height, const char* label, void (*callback)());

  void onTouch() override;
  int getStatus() const override;
  void draw_widget(Adafruit_ILI9341 tft) const override;

  void setLabel(const char* label);
  const char* getLabel() const;

  void setCallback(void (*callback)());

private:
  const char* label;
  void (*callback)(); // Callback function pointer
  bool status;
  bool disabled;
};


class Slider : public Widget {
public:
  Slider(int x, int y, int width, int height, int minValue, int maxValue, int* value);

  void onTouch() override;
  int getStatus() const override;

  void setValue(int newValue);
  int getValue() const;

private:
  int minValue, maxValue;
  int* value;
};


class Checkbox : public Widget {
public:
  Checkbox(int x, int y, int width, int height, bool* checked);

  void onTouch() override;
  int getStatus() const override;

  bool isChecked() const;

private:
  bool* checked;
};