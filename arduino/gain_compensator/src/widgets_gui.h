#include <Adafruit_GFX.h>    // Core graphics library

class Widget {
public:
  Widget(int x, int y, int width, int height);

  virtual void onTouch() = 0;
  virtual int getStatus() const = 0;

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

  void setLabel(const char* label);
  const char* getLabel() const;

  void setCallback(void (*callback)());
  void invokeCallback();

private:
  const char* label;
  void (*callback)(); // Callback function pointer
  bool clicked;
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