#include "widgets_gui.h"

// **************** WIDGET CLASS *****************

Widget::Widget(int x, int y, int width, int height,  const char* label) : x(x), y(y), width(width), label(label), height(height), disabled(false) {}

// Constructor for the circular components (like checkbox)
Widget::Widget(int x, int y, int radious, const char* label) : x(x), y(y), radious(radious), label(label), disabled(false) {}

bool Widget::is_disabled() const {
  return disabled;
}

void Widget::set_disabled(bool value) {
  disabled = value;
}

void Widget::update_state(int x, int y, Adafruit_ILI9341 tft){

}


// **************** BUTTON CLASS *****************

Button::Button(int x, int y, int width, int height, const char* label, void (*callback)())
    : Widget(x, y, width, height, label), callback(callback), status(false), disabled(false),
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

void Button::update_state(int x_touch, int y_touch, Adafruit_ILI9341 tft){
	
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
Slider::Slider(int x, int y, int width, int height, int minValue, int maxValue, int* value, const char* label)
    : Widget(x, y, width, height,label), minValue(minValue), maxValue(maxValue), value(value) {}


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
Checkbox::Checkbox(int x, int y, int radious, bool* checked, const char* label)
    : Widget(x, y,radious, label), checked(checked), last_debounce_time(0), last_touch_processed(false) {}

int Checkbox::get_status() const {
  return *checked ? 1 : 0;
}

void Checkbox::is_checked(Adafruit_ILI9341 tft) {
	tft.drawCircle(x,y,radious,ILI9341_WHITE);
	tft.fillCircle(x,y,radious-4,ILI9341_WHITE);
	tft.setCursor(x + 2*radious+3, y-1);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(2);
	tft.println(label);
}


void Checkbox::is_not_checked(Adafruit_ILI9341 tft) {
	tft.drawCircle(x,y,radious,ILI9341_WHITE);
	tft.fillCircle(x,y,radious-4,ILI9341_BLACK);
	tft.setCursor(x + 2*radious+3, y-1);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(2);
	tft.println(label);
}

void Checkbox::update_state(int x_touch, int y_touch, Adafruit_ILI9341 tft){
	
	if ((x_touch > (x - radious)) && (x_touch < (x + radious)) && (y_touch > (y - radious)) && (y_touch <= (y + radious)))
	{
		last_debounce_time = millis();
	}else{
		last_touch_processed = false;
	}

	if ((millis() - last_debounce_time) < DEBOUNCE_TIME) {
		if(!last_touch_processed){
			*checked = !(*checked);
			if(*checked){
				this->is_checked(tft); 
			}else{
				this->is_not_checked(tft);
			}		
			last_touch_processed = true;
		}
	}
}
