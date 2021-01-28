//
//
//

#include <Mouse.h>
#include "KeyboardButton.h"
#include "MouseManager.h"

MouseManager::MouseManager()
{
}

void MouseManager::Execution()
{
  if (this->MouseButtons[0]->CurrentState == LOW ||
      this->MouseButtons[1]->CurrentState == LOW ||
      this->MouseButtons[2]->CurrentState == LOW ||
      this->MouseButtons[3]->CurrentState == LOW)
    this->displacementl();


  if (this->MouseButtons[0]->CurrentState == LOW)
  {
    if (this->MouseButtons[4]->CurrentState == LOW)
      Mouse.move(0, 0, 1);
    else
      Mouse.move(0, -this->displacementlValue, 0);
  }

  if (this->MouseButtons[1]->CurrentState == LOW)
    Mouse.move(-this->displacementlValue, 0, 0);

  if (this->MouseButtons[2]->CurrentState == LOW)
  {
    if (this->MouseButtons[4]->CurrentState == LOW)
      Mouse.move(0, 0, -1);
    else
      Mouse.move(0, this->displacementlValue, 0);
  }

  if (this->MouseButtons[3]->CurrentState == LOW)
    Mouse.move(this->displacementlValue, 0, 0);
}

void MouseManager::displacementl()
{
  unsigned long now = millis();
  if (now - this->lastChangeStateTime < 35) {
    this->displacementlValue = this->displacementlValue + 1;
    if (this->displacementlValue > 35) {
      this->displacementlValue = 35;
    }
  }
  else {
    displacementlValue = 0;
  }

  this->lastChangeStateTime = now;
}
