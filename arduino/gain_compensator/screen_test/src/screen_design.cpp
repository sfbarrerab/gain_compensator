// Slider widget demo, requires display with touch screen

// Requires widget library here:
// https://github.com/Bodmer/TFT_eWidget

#include "screen_design.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite knob = TFT_eSprite(&tft); // Sprite for the slide knob

SliderWidget s1 = SliderWidget(&tft, &knob);    // Slider 1 widget
SliderWidget s2 = SliderWidget(&tft, &knob);    // Slider 2 widget

int x_old = 0;
int y_old = 0;

void init_layout_screen() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FF18);

  // Create a parameter set for the slider
  slider_t param;

  // Slider slot parameters
  param.slotWidth = 9;           // Note: ends of slot will be rounded and anti-aliased
  param.slotLength = 200;        // Length includes rounded ends
  param.slotColor = TFT_BLUE;    // Slot colour
  param.slotBgColor = TFT_BLACK; // Slot background colour for anti-aliasing
  param.orientation = H_SLIDER;  // sets it "true" for horizontal

  // Slider control knob parameters (smooth rounded rectangle)
  param.knobWidth = 15;          // Always along x axis
  param.knobHeight = 25;         // Always along y axis
  param.knobRadius = 5;          // Corner radius
  param.knobColor = TFT_WHITE;   // Anti-aliased with slot backgound colour
  param.knobLineColor = TFT_RED; // Colour of marker line (set to same as knobColor for no line)

  // Slider range and movement speed
  param.sliderLT = 0;            // Left side for horizontal, top for vertical slider
  param.sliderRB = 100;          // Right side for horizontal, bottom for vertical slider
  param.startPosition = 50;      // Start position for control knob
  param.sliderDelay = 0;         // Microseconds per pixel movement delay (0 = no delay)

  // Create slider using parameters and plot at 0,0
  s1.drawSlider(0, 0, param);

  // Show bounding box (1 pixel outside slider working area)
  int16_t x, y;    // x and y can be negative
  uint16_t w, h;   // Width and height
  s1.getBoundingRect(&x, &y, &w, &h);     // Update x,y,w,h with bounding box
  tft.drawRect(x, y, w, h, TFT_DARKGREY); // Draw rectangle outline
/*
  // Alternative discrete fns to create/modify same slider - but fn sequence is important...
  s1.createSlider(9, 200, TFT_BLUE, TFT_BLACK, H_SLIDER);
  s1.createKnob(15, 25, 5, TFT_WHITE, TFT_RED);
  s1.setSliderScale(0, 100);
  s1.drawSlider(0, 0);
*/
  s1.setSliderPosition(50);
  s1.setSliderPosition(100);

  // Update any parameters that are different for slider 2
  param.slotWidth = 4;
  param.orientation = V_SLIDER; // sets it "false" for vertical

  param.knobWidth = 19;
  param.knobHeight = 19;
  param.knobRadius = 19/2; // Half w and h so creates a circle

  param.sliderLT = 200;     // Top for vertical slider
  param.sliderRB = 0;       // Bottom for vertical slider
  param.sliderDelay = 2000; // 2ms per pixel movement delay (movement is blocking until complete)

  s2.drawSlider(0, 50, param);

  s2.getBoundingRect(&x, &y, &w, &h);
  tft.drawRect(x, y, w, h, TFT_DARKGREY);
/*
  // Alternative discrete fns to create/modify same slider - but fn sequence is important...
  s2.createSlider(4, 200, TFT_BLUE, TFT_BLACK, V_SLIDER);
  s2.createKnob(19, 19, 9, TFT_WHITE, TFT_RED);
  s2.setSliderScale(200, 0, 2000);
  s2.drawSlider(0, 50);
*/
  // Move slider under software control
  s2.setSliderPosition(50);
  s2.setSliderPosition(100);

}

void task_screen_layout(void *pvParameters)
{

  while(1){


    if (s1.checkTouch(x, y)) {
      Serial.print("Slider 1 = "); Serial.println(s1.getSliderPosition());
    }
    if (s2.checkTouch(x, y)) {
      Serial.print("Slider 2 = "); Serial.println(s2.getSliderPosition());
    }

    
    
    vTaskDelay(40/ portTICK_PERIOD_MS);
  }

}