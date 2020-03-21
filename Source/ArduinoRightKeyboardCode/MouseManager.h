// MouseManager.h

#ifndef _MOUSEMANAGER_h
#define _MOUSEMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "MiniTrackBall.h"

class MouseManager {
  public:
    MouseManager(MiniTrackBall *miniTrackBall, KeyboardButton *keyboardButton);
    void Execution();
  private:
    MiniTrackBall *miniTrackBall;
    KeyboardButton *middleScrollButton;
    
    unsigned char displacementMin;
    unsigned char displacementMax;
    
    signed long displacementTotal(signed char value1, signed char value2);
    signed char displacementBase(signed long value);
};

#endif
