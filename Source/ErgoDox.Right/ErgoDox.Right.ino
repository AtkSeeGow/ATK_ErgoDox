#include <Wire.h>
#include <Mouse.h>
#include <LiquidCrystal_I2C.h>

#include "KeyboardButton.h"
#include "KeyboardManager.h"
#include "MouseManager.h"

MouseManager mouseManager = MouseManager();
KeyboardManager keyboardManager = KeyboardManager(&mouseManager);

int8_t rowPins[] = { A3, A2, A1, A0, 15, 14, 16, 10 };
int8_t columnPins[] = { 4, 5, 6, 7, 8, 9 };

void setup()
{
  Serial.begin(9600);
  Mouse.begin();

  for (int8_t pin : rowPins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  for (int8_t pin : columnPins) {
    pinMode(pin, INPUT_PULLUP);
  }
}

void loop()
{
  for (int8_t rowPin : rowPins)
  {
    digitalWrite(rowPin, LOW);

    for (int8_t columnPin : columnPins)
    {
      bool currentState = digitalRead(columnPin);
      keyboardManager.OperationState(rowPin, columnPin, currentState);
    }

    digitalWrite(rowPin, HIGH);
  }

  keyboardManager.Execution();
  mouseManager.Execution();
}
