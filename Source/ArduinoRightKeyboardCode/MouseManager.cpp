//
//
//

#include <Mouse.h>
#include "KeyboardButton.h"
#include "MiniTrackball.h"
#include "MouseManager.h"

MouseManager::MouseManager(MiniTrackBall *miniTrackBall, KeyboardButton *middleScrollButton)
{
  this->miniTrackBall = miniTrackBall;
  this->middleScrollButton = middleScrollButton;
  this->displacementMax = 15;
}

void MouseManager::Execution()
{
  unsigned long now = millis();

  uint8_t track_data[5];

  this->miniTrackBall->GetTrackData(track_data);

  signed long x =  this->displacementTotal(track_data[2], track_data[3]);
  signed long y =  this->displacementTotal(track_data[0], track_data[1]);

  while (x != 0 || y != 0) {
    signed char displacementX = this->displacementBase(x);
    if (displacementX == x)
      x = 0;
    else if (x > 0)
      x = x - this->displacementMax;
    else if (x < 0)
      x = x + this->displacementMax;

    signed char displacementY =  this->displacementBase(y);
    if (displacementY == y)
      y = 0;
    else if (y > 0)
      y = y - this->displacementMax;
    else if (y < 0)
      y = y + this->displacementMax;

    if (this->middleScrollButton->CurrentState == LOW)
      Mouse.move(0, 0, displacementY * 0.3);
    else
      Mouse.move(displacementX, displacementY, 0);
  }
}

signed long MouseManager::displacementTotal(signed char value1, signed char value2)
{
  signed long value = (value2 - value1);
  
  if (value == 0)
    return 0;
  else if(value > 10)
    value = 10;
  else if(value < -10)
     value = -10; 
     
  signed long result = pow(5, abs(value));

  if (result > 150)
    result = 150;

  if (value < 0)
    result = -result;

  return result;
}

signed char MouseManager::displacementBase(signed long value) {
  if (value > this->displacementMax)
    return this->displacementMax;
  else if (value < -this->displacementMax)
    return -this->displacementMax;
  else
    return value;
}
