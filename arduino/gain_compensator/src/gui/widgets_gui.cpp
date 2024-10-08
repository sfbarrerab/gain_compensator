#include "widgets_gui.h"

// **************** WIDGET CLASS *****************

Widget::Widget(int x, int y, int width, int height, const char* label, bool* gui_change_triggered) : x(x), y(y), width(width), height(height), label(label), gui_change_triggered(gui_change_triggered), disabled(false) {}

// Constructor for the circular components (like radiobox)
Widget::Widget(int x, int y, int radious, const char* label, bool* gui_change_triggered) : x(x), y(y), radious(radious), label(label), gui_change_triggered(gui_change_triggered), disabled(false){}

Widget::~Widget(){

}

bool Widget::is_disabled() const {
  return disabled;
}

void Widget::set_disabled(bool value) {
  disabled = value;
}

void Widget::update_state(int x, int y, Adafruit_ILI9341 tft){

}


// **************** BUTTON CLASS *****************

Button::Button(int x, int y, int width, int height, const char* label, void (*callback)(), bool* gui_change_triggered)
    : Widget(x, y, width, height, label, gui_change_triggered), callback(callback), last_debounce_time(0), last_touch_processed(false) {}

void Button::set_label(const char* new_label) {
  label = new_label;
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
	tft.setCursor(x + 6, y + (height/2)-6);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(2);
	tft.println(label);
}

void Button::is_pressed(Adafruit_ILI9341 tft){
	tft.fillRect(x-2, y-2, width+4, height+4, ILI9341_BLUE);
	tft.setCursor(x + 6, y + (height/2)-6);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(2);
	tft.println(label);
}

void Button::update_state(int x_touch, int y_touch, Adafruit_ILI9341 tft){
	
	bool old_status = last_touch_processed;
	if ((x_touch > x) && (x_touch < (x + width)) && (y_touch > y) && (y_touch <= (y + height)))
	{
		last_touch_processed = true;
	}else{
		last_touch_processed = false;
	}

	if(old_status != last_touch_processed){
		last_debounce_time = millis();
	}

	if ((millis() - last_debounce_time) < DEBOUNCE_TIME) {
		if (last_touch_processed) {
			this->is_pressed(tft);

		} else {
			this->is_released(tft);
			if (callback != nullptr) {
				callback();
			}
		}
	}


}

// **************** SLIDER CLASS *****************
Slider::Slider(int x, int y, int width, int height, int min_value, int max_value, int* value, const char* label, int r_slider,  bool* gui_change_triggered)
    : Widget(x, y, width, height, label, gui_change_triggered), min_value(min_value), max_value(max_value), value(value), r_slider(r_slider) {}

void Slider::change_label(const char* new_label){
	label = new_label;
}

void Slider::update_slider_value(int x_touched){
	double step = double(width)/double(max_value-min_value);
	*value = int(double(x_touched-x)/step)+min_value;
	if(*value < min_value){
		*value = min_value;
	}

	if(*value > max_value){
		*value = max_value;
	}
}

int Slider::value_to_x_position(int val){
	double step = double(width)/double(max_value-min_value);
	int x_position = (double(val-min_value)*step)+x+r_slider;
	return x_position;
}

void Slider::init_slider(Adafruit_ILI9341 tft){
	char buffer[10];
	
	int color;
	if(!disabled){
		color = ILI9341_BLUE;
	}else{
		color = ILI9341_LIGHTGREY;
	}

	tft.fillRect(x,y-r_slider,width+2.2*r_slider,2.2*r_slider,ILI9341_BLACK);
	tft.fillRect(x+r_slider,y,width,height,color);
	tft.fillCircle(value_to_x_position(*value),y+(height/2),r_slider,color);
	if(*gui_change_triggered){
		tft.fillRect(x,y-2*r_slider,150,15,ILI9341_BLACK);
	}

	tft.setCursor(x, y-2*r_slider);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(2);
	tft.println(label);

	sprintf(buffer, "%d", *value);
	tft.fillRect(x+140,y-2*r_slider-2,60,16,ILI9341_BLACK);
	tft.setCursor(x+150, y-2*r_slider-2);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(2);
	tft.println(buffer);
}

void Slider::update_state(int x_touch, int y_touch, Adafruit_ILI9341 tft){
	if (!disabled){
		if ((x_touch >= x-r_slider) && (x_touch <= (x + width+r_slider)) && (y_touch > (y - r_slider)) && (y_touch <= (y + r_slider))){
			this->update_slider_value(x_touch);
			this->init_slider(tft);
		}
	}
	if(*gui_change_triggered){
		this->init_slider(tft);
	}
	
	
}


// **************** RADIOBOX CLASS *****************
Radio::Radio(int x, int y, int radious, bool* selected, const char* label, bool* gui_change_triggered)
    : Widget(x, y, radious, label, gui_change_triggered), selected(selected), last_debounce_time(0), last_touch_processed(false) {}

void Radio::init_radiobox(Adafruit_ILI9341 tft) {
	//*selected = true;
	if(*selected){
		tft.drawCircle(x+radious,y,radious,ILI9341_WHITE);
		tft.fillCircle(x+radious,y,radious-4,ILI9341_WHITE);
		tft.setCursor(x + 2*radious + 5, y-(radious/2));
		tft.setTextColor(ILI9341_WHITE);
		tft.setTextSize(2);
		tft.println(label);
	}else{
		//*selected = false;
		tft.drawCircle(x+radious,y,radious,ILI9341_WHITE);
		tft.fillCircle(x+radious,y,radious-4,ILI9341_BLACK);
		tft.setCursor(x + 2*radious + 5, y-(radious/2));
		tft.setTextColor(ILI9341_WHITE);
		tft.setTextSize(2);
		tft.println(label);
	}
}

void Radio::update_state(int x_touch, int y_touch, Adafruit_ILI9341 tft){
	if(!disabled){
		if (((x_touch > (x - radious)) && (x_touch < (x + radious)) && (y_touch > (y - radious)) && (y_touch <= (y + radious))))
		{
			last_debounce_time = millis();
		}else{
			last_touch_processed = false;
		}
	}
	if ((millis() - last_debounce_time) < DEBOUNCE_TIME) {
		if(!last_touch_processed){
			*selected = true;//!(*selected);  -> Use this instead if you want to change the value of the
											// radiobox each time the widget is pressed. However,
											// I recomend to create another widget for checkboxes
			this->init_radiobox(tft); 	
			last_touch_processed = true;
		}
	}
	if(*gui_change_triggered){		// the change is due to a trigger and not that the widget was touched
		this->init_radiobox(tft); 
	}
}

// **************** LABEL CLASS *****************

Textbox::Textbox(int x, int y, int width, int height, const char* label, bool* gui_change_triggered, int outline_color, int text_color, int text_size, const char* mini_label)
			:Widget(x,y,width,height,label, gui_change_triggered), outline_color(outline_color), text_color(text_color), text_size(text_size), mini_label(mini_label){}


void Textbox::init_label(Adafruit_ILI9341 tft){
	if(mini_label != NULL){
		tft.setCursor(x, y);
		tft.setTextColor(text_color);
		tft.setTextSize(text_size);
		tft.println(mini_label);
		x += 30;
	}
	tft.drawRect(x-2, y-2, width+4, height+4, outline_color);
	tft.drawRect(x-1, y-1, width+2, height+2, outline_color);
	tft.fillRect(x,y,width,height,ILI9341_BLACK),
	tft.setCursor(x, y);
	tft.setTextColor(text_color);
	tft.setTextSize(text_size);
	tft.println(label);
}

void Textbox::update_label(Adafruit_ILI9341 tft, const char* new_label){
	tft.fillRect(x,y,width,height,ILI9341_BLACK),
	tft.setCursor(x, y);
	tft.setTextColor(text_color);
	tft.setTextSize(text_size);
	if(new_label!=NULL)
		tft.println(new_label);
		// Next update: recognize the \n and plot it in a for
}