#include "widgets_gui.h"

// **************** WIDGET CLASS *****************

Widget::Widget(int x, int y, int width, int height) : x(x), y(y), width(width), height(height), disabled(false) {}

bool Widget::isDisabled() const {
  return disabled;
}

void Widget::setDisabled(bool value) {
  disabled = value;
}


// **************** BUTTON CLASS *****************

Button::Button(int x, int y, int width, int height, const char* label, void (*callback)())
    : Widget(x, y, width, height), label(label), callback(callback), clicked(false), disabled(false) {}

void Button::onTouch() {
  if (!disabled) {
    clicked = true;
    invokeCallback();
  }
}

int Button::getStatus() const {
  return clicked ? 1 : 0;
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

void Button::invokeCallback() {
  if (callback != nullptr) {
    callback();
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