// KeyboardManager.h

#ifndef _KEYBOARDMANAGER_h
#define _KEYBOARDMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "KeyboardButton.h"
#include "MouseManager.h"

class KeyboardManager {
  public:
    KeyboardManager(MouseManager *mouseManager);

    void OperationState(int8_t rowPin, int8_t columnPin, bool currentState);
    void Execution();
    void DisplayMappingModeName();

    KeyboardButton *GetMapping(int8_t rowPin, int8_t columnPin);
  private:
    KeyboardButton *getBasicMapping(int8_t rowPin, int8_t columnPin);
    
    KeyboardButton keyboardButtons[40];
};

#endif
