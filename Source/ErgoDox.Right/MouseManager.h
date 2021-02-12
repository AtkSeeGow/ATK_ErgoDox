// MouseManager.h

#ifndef _MOUSEMANAGER_h
#define _MOUSEMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class MouseManager {
  public:
    MouseManager();
    void Execution();
    KeyboardButton *MouseButtons[10];
  private:
    void displacementl();
    unsigned long lastChangeStateTime;
    unsigned long displacementlValue;
};

#endif
