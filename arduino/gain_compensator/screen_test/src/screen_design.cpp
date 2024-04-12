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
  param.slotWidth = SLIDER_WIDTH;           // Note: ends of slot will be rounded and anti-aliased
  param.slotLength = SLIDER_LENGTH;        // Length includes rounded ends
  param.slotColor = TFT_BLUE;    // Slot colour
  param.slotBgColor = TFT_BLACK; // Slot background colour for anti-aliasing
  param.orientation = H_SLIDER;  // sets it "true" for horizontal

  // Slider control knob parameters (smooth rounded rectangle)
  param.knobWidth = SLIDER_KNOB_WIDTH;          // Always along x axis
  param.knobHeight = SLIDER_KNOB_HEIGHT;         // Always along y axis
  param.knobRadius = SLIDER_KNOB_RADI;          // Corner radius
  param.knobColor = TFT_WHITE;   // Anti-aliased with slot backgound colour
  param.knobLineColor = TFT_BLUE; // Colour of marker line (set to same as knobColor for no line)

  // Slider range and movement speed
  param.sliderLT = 0;            // Left side for horizontal, top for vertical slider
  param.sliderRB = 130;          // Right side for horizontal, bottom for vertical slider
  param.startPosition = 50;      // Start position for control knob
  param.sliderDelay = SLIDER_DELAY;         // Microseconds per pixel movement delay (0 = no delay)

  // Create slider using parameters and plot at 0,0
 
  s1.drawSlider(SLIDER_X0, SLIDER_Y0, param);
  
  s1.setSliderPosition(50);
  vTaskDelay(10/ portTICK_PERIOD_MS);
  s1.setSliderPosition(100);

  // Update any parameters that are different for slider 2
  param.sliderLT = 0;     // Top for vertical slider
  param.sliderRB = 150;       // Bottom for vertical slider
  param.sliderDelay = SLIDER_DELAY; // 2ms per pixel movement delay (movement is blocking until complete)

  s2.drawSlider(SLIDER_X0, SLIDER_Y0 + DELTA_SLIDER_YPOS, param);
  
  s2.setSliderPosition(50);
  vTaskDelay(10/ portTICK_PERIOD_MS);
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