#include "widgets_gui.h"

/*
Library writen by Santiago Barrera

This library is only fro being able to use Adafruit ILI9341 library to create
some widgets in slow microcontrollers, like arduino uno or arduino mega, where 
you cannot use LVGL for example.

As it is limited to Adafruit library, some of the widgets are rough created, with
hot pixel pushed parameters. So, be patient with it.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
The above copyright notice and this permissionotice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. InO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


// **************** WIDGET CLASS *****************

Widget::Widget(int x, int y, int width, int height) : x(x), y(y), width(width), height(height), disabled(false) {}

bool Widget::is_disabled() const {
  return disabled;
}

void Widget::set_disabled(bool value) {
  disabled = value;
}

void Widget::draw_widget(Adafruit_ILI9341 tft){

}


// **************** BUTTON CLASS *****************

Button::Button(int x, int y, int width, int height, const char* label, void (*callback)())
    : Widget(x, y, width, height), label(label), callback(callback), status(false), disabled(false),
		 last_debounce_time(0) {}

int Button::get_status() const {
  return status ? 1 : 0;
}

void Button::set_label(const char* newLabel) {
  label = newLabel;
}

const char* Button::get_label() const {
  return label;
}

void Button::set_callback(void (*cb)()) {
  callback = cb;
}

void Button::is_released(Adafruit_ILI9341 tft){
	tft.drawRect(x-1, y-1, width+2, height+2, ILI9341_BLACK);
	tft.drawRect(x-2, y-2, width+4, height+4, ILI9341_BLACK);
	tft.fillRect(x, y, width, height, ILI9341_BLUE);
	tft.setCursor(x + 6, y + (height/4));
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(2);
	tft.println(label);
}

void Button::is_pressed(Adafruit_ILI9341 tft){
	tft.fillRect(x-2, y-2, width+4, height+4, ILI9341_BLUE);
	tft.setCursor(x + 6, y + (height/4));
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(2);
	tft.println(label);
}

void Button::update_button_state(int x_touch, int y_touch, Adafruit_ILI9341 tft){
	
	bool old_status = status;
	if ((x_touch > x) && (x_touch < (x + width)) && (y_touch > y) && (y_touch <= (y + height)))
	{
		status = true;
	}else{
		status = false;
	}

	if(old_status != status){
		last_debounce_time = millis();
	}

	if ((millis() - last_debounce_time) < DEBOUNCE_TIME) {
		if (status) {
			this->is_pressed(tft);
			if (callback != nullptr) {
				callback();
			}
		} else {
			this->is_released(tft);
		}
	}


}

// **************** SLIDER CLASS *****************
Slider::Slider(int x, int y, int width, int height, int minValue, int maxValue, int* value)
    : Widget(x, y, width, height), minValue(minValue), maxValue(maxValue), value(value) {}


int Slider::get_status() const {
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

int Checkbox::get_status() const {
  return *checked ? 1 : 0;
}

bool Checkbox::isChecked() const {
  return *checked;
}