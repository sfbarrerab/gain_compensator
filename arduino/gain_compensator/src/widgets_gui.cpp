#include "widgets_gui.h"

// **************** WIDGET CLASS *****************

Widget::Widget(int x, int y, int width, int height) : x(x), y(y), width(width), height(height), disabled(false) {}

bool Widget::isDisabled() const {
  return disabled;
}

void Widget::setDisabled(bool value) {
  disabled = value;
}

void Widget::draw_widget(Adafruit_ILI9341 tft) const{

}


// **************** BUTTON CLASS *****************

Button::Button(int x, int y, int width, int height, const char* label, void (*callback)())
    : Widget(x, y, width, height), label(label), callback(callback), status(false), disabled(false) {}

void Button::onTouch() {
  if (!disabled) {
		status = !status;
		if (callback != nullptr) {
			callback();
		}
  }
}

int Button::getStatus() const {
  return status ? 1 : 0;
}

void Button::setLabel(const char* newLabel) {
  label = newLabel;
}

const char* Button::getLabel() const {
  return label;
}

void Button::setCallback(void (*cb)()) {
  callback = cb;
}

void Button::draw_widget(Adafruit_ILI9341 tft) const{
	if(status){
		tft.fillRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_RED);
		tft.fillRect(GREENBUTTON_X, GREENBUTTON_Y, GREENBUTTON_W, GREENBUTTON_H, ILI9341_BLUE);
		tft.drawRect(FRAME_X, FRAME_Y, FRAME_W, FRAME_H, ILI9341_BLACK);
		tft.setCursor(GREENBUTTON_X + 6, GREENBUTTON_Y + (GREENBUTTON_H / 2));
		tft.setTextColor(ILI9341_WHITE);
		tft.setTextSize(2);
		tft.println("ON");
	}else{
		tft.fillRect(GREENBUTTON_X, GREENBUTTON_Y, GREENBUTTON_W, GREENBUTTON_H, ILI9341_GREEN);
		tft.fillRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_BLUE);
		tft.drawRect(FRAME_X, FRAME_Y, FRAME_W, FRAME_H, ILI9341_BLACK);
		tft.setCursor(REDBUTTON_X + 6, REDBUTTON_Y + (REDBUTTON_H / 2));
		tft.setTextColor(ILI9341_WHITE);
		tft.setTextSize(2);
		tft.println("OFF");
	}

}

// **************** SLIDER CLASS *****************
Slider::Slider(int x, int y, int width, int height, int minValue, int maxValue, int* value)
    : Widget(x, y, width, height), minValue(minValue), maxValue(maxValue), value(value) {}

void Slider::onTouch() {
  // Implement code to handle slider touch
}

int Slider::getStatus() const {
  return *value;
}

void Slider::setValue(int newValue) {
  // Implement code to set the value within the valid range
}

int Slider::getValue() const {
  return *value;
}



// **************** CHECKBOX CLASS *****************
Checkbox::Checkbox(int x, int y, int width, int height, bool* checked)
    : Widget(x, y, width, height), checked(checked) {}

void Checkbox::onTouch() {
  // Implement code to handle checkbox touch
  *checked = !(*checked);
}

int Checkbox::getStatus() const {
  return *checked ? 1 : 0;
}

bool Checkbox::isChecked() const {
  return *checked;
}