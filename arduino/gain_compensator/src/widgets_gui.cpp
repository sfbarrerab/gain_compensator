#include "widgets_gui.h"

// Base class for GUI widgets
class Widget {
public:
  Widget(int x, int y, int width, int height) : x(x), y(y), width(width), height(height), disabled(0) {}

  virtual void onTouch() = 0;
  virtual int getStatus() const = 0;
  int isDisabled() const {
    return disabled;
  }
  void setDisabled(int value) {
    disabled = value;
  }

protected:
  int x, y, width, height, disabled;
};

class Button : public Widget {
public:
  Button(int x, int y, int width, int height, const char* label, void (*callback)())
      : Widget(x, y, width, height), label(label), callback(callback), clicked(0) {}

  void onTouch() override {
    // Execute the callback when the button is touched
    if (callback != nullptr && !disabled) {
      callback();
    }

    // Update the status of the button
    clicked = 1;
  }

  // Modify getStatus to return the status of the button
  int getStatus() const override {
    return clicked ? 1 : 0;
  }

private:
  const char* label;
  void (*callback)();
  bool clicked;
};

// Modify Slider class to include specific status parameters
class Slider : public Widget {
public:
  Slider(int x, int y, int width, int height, int minValue, int maxValue, int* value, const char* label)
      : Widget(x, y, width, height), minValue(minValue), maxValue(maxValue), value(value), label(label) {}

  void onTouch() override {
    // Implement code to handle slider touch
  }

  // Modify getStatus to return the status of the slider
  int getStatus() const override {
    return *value;
  }

private:
  const char* label;
  int minValue, maxValue;
  int* value;
};

// Modify Checkbox class to include specific status parameters
class Checkbox : public Widget {
public:
  Checkbox(int x, int y, int width, int height, bool* checked)
      : Widget(x, y, width, height), checked(checked) {}

  void onTouch() override {
    // Implement code to handle checkbox touch
    *checked = !(*checked);
  }

  // Modify getStatus to return the status of the checkbox
  int getStatus() const override {
    return *checked ? 1 : 0;
  }

private:
  bool* checked;
};
