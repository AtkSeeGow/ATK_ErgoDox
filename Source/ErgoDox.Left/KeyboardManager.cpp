//
//
//

#include <Keyboard.h>
#include <Mouse.h>
#include "KeyboardButton.h"
#include "KeyboardManager.h"

KeyboardManager::KeyboardManager(LiquidCrystal_I2C *liquidCrystalI2C)
{
  int8_t bounceTime = 5;

  this->noneButton = KeyboardButton();

  this->liquidCrystalI2C = liquidCrystalI2C;

  this->keyboardButtons[0] = KeyboardButton(bounceTime, '`', KeyboardType);
  this->keyboardButtons[1] = KeyboardButton(bounceTime, KEY_TAB, KeyboardType);
  this->keyboardButtons[2] = KeyboardButton(bounceTime, KEY_CAPS_LOCK, KeyboardType);
  this->keyboardButtons[3] = KeyboardButton(bounceTime, KEY_LEFT_SHIFT, KeyboardType);
  this->keyboardButtons[4] = KeyboardButton(bounceTime, KEY_LEFT_GUI, KeyboardType);

  this->keyboardButtons[5] = KeyboardButton(bounceTime, '1', KeyboardType);
  this->keyboardButtons[6] = KeyboardButton(bounceTime, 'q', KeyboardType);
  this->keyboardButtons[7] = KeyboardButton(bounceTime, 'a', KeyboardType);
  this->keyboardButtons[8] = KeyboardButton(bounceTime, 'z', KeyboardType);
  this->keyboardButtons[9] = KeyboardButton(bounceTime, KEY_F1, KeyboardType);

  this->keyboardButtons[10] = KeyboardButton(bounceTime, '2', KeyboardType);
  this->keyboardButtons[11] = KeyboardButton(bounceTime, 'w', KeyboardType);
  this->keyboardButtons[12] = KeyboardButton(bounceTime, 's', KeyboardType);
  this->keyboardButtons[13] = KeyboardButton(bounceTime, 'x', KeyboardType);
  this->keyboardButtons[14] = KeyboardButton(bounceTime, KEY_F2, KeyboardType);

  this->keyboardButtons[15] = KeyboardButton(bounceTime, '3', KeyboardType);
  this->keyboardButtons[16] = KeyboardButton(bounceTime, 'e', KeyboardType);
  this->keyboardButtons[17] = KeyboardButton(bounceTime, 'd', KeyboardType);
  this->keyboardButtons[18] = KeyboardButton(bounceTime, 'c', KeyboardType);
  this->keyboardButtons[19] = KeyboardButton(bounceTime, KEY_F3, KeyboardType);

  this->keyboardButtons[20] = KeyboardButton(bounceTime, '4', KeyboardType);
  this->keyboardButtons[21] = KeyboardButton(bounceTime, 'r', KeyboardType);
  this->keyboardButtons[22] = KeyboardButton(bounceTime, 'f', KeyboardType);
  this->keyboardButtons[23] = KeyboardButton(bounceTime, 'v', KeyboardType);
  this->keyboardButtons[24] = KeyboardButton(bounceTime, KEY_F4, KeyboardType);

  this->keyboardButtons[25] = KeyboardButton(bounceTime, '5', KeyboardType);
  this->keyboardButtons[26] = KeyboardButton(bounceTime, 't', KeyboardType);
  this->keyboardButtons[27] = KeyboardButton(bounceTime, 'g', KeyboardType);
  this->keyboardButtons[28] = KeyboardButton(bounceTime, 'b', KeyboardType);

  this->keyboardButtons[29] = KeyboardButton(bounceTime, KEY_ESC, KeyboardType);
  this->keyboardButtons[30] = KeyboardButton(bounceTime, KEY_F6, KeyboardType);
  this->keyboardButtons[31] = KeyboardButton(bounceTime, KEY_F5, KeyboardType);

  this->keyboardButtons[32] = KeyboardButton(bounceTime, ' ', KeyboardType);
  this->keyboardButtons[33] = KeyboardButton(bounceTime, KEY_LEFT_CTRL, KeyboardType);
  this->keyboardButtons[34] = KeyboardButton(bounceTime, 1, FunctionType);
  this->keyboardButtons[35] = KeyboardButton(bounceTime, 2, FunctionType);
  this->keyboardButtons[36] = KeyboardButton(bounceTime, 3, FunctionType);
  this->keyboardButtons[37] = KeyboardButton(bounceTime, KEY_LEFT_ALT, KeyboardType);

  this->keyboardButtons[38] = KeyboardButton(bounceTime, KEY_F7, KeyboardType);
  this->keyboardButtons[39] = KeyboardButton(bounceTime, KEY_F8, KeyboardType);
  this->keyboardButtons[40] = KeyboardButton(bounceTime, KEY_F9, KeyboardType);
  this->keyboardButtons[41] = KeyboardButton(bounceTime, KEY_F10, KeyboardType);
  this->keyboardButtons[42] = KeyboardButton(bounceTime, KEY_F11, KeyboardType);
  this->keyboardButtons[43] = KeyboardButton(bounceTime, KEY_F12, KeyboardType);

  this->keyboardButtons[44] = KeyboardButton(bounceTime, KEY_UP_ARROW, KeyboardType);
  this->keyboardButtons[45] = KeyboardButton(bounceTime, KEY_DOWN_ARROW, KeyboardType);
  this->keyboardButtons[46] = KeyboardButton(bounceTime, KEY_LEFT_ARROW, KeyboardType);
  this->keyboardButtons[47] = KeyboardButton(bounceTime, KEY_RIGHT_ARROW, KeyboardType);

  this->keyboardButtons[48] = KeyboardButton(bounceTime, KEY_BACKSPACE, KeyboardType);
  this->keyboardButtons[49] = KeyboardButton(bounceTime, KEY_RETURN, KeyboardType);

  this->keyboardButtons[50] = KeyboardButton(bounceTime, MOUSE_LEFT, MouseType);
  this->keyboardButtons[51] = KeyboardButton(bounceTime, MOUSE_RIGHT, MouseType);
  this->keyboardButtons[52] = KeyboardButton(bounceTime, MOUSE_MIDDLE, MouseType);
}

void KeyboardManager::OperationState(int8_t rowPin, int8_t columnPin, bool currentState)
{
  unsigned long now = millis();

  KeyboardButton *keyboardButton = this->GetMapping(rowPin, columnPin);

  if (!keyboardButton->IsMoreBounceTime())
    return;

  if (keyboardButton->CurrentState != currentState)
  {
    keyboardButton->LastChangeStateTime = now;
    keyboardButton->CurrentState = currentState;
    this->DisplayMappingModeName();

    if (keyboardButton->KeyType == FunctionType && keyboardButton->CurrentState == HIGH)
      for (int8_t i = 0; i < 53; i++)
        this->keyboardButtons[i].CurrentState = HIGH;
  }
}

void KeyboardManager::Execution()
{
  for (int8_t i = 0; i < 53; i++)
  {
    KeyboardButton keyboardButton = this->keyboardButtons[i];
    keyboardButton.OperationPress();
    keyboardButton.OperationRelease();
  }
}

KeyboardButton *KeyboardManager::GetMapping(int8_t rowPin, int8_t columnPin)
{
  if (this->keyboardButtons[34].CurrentState == LOW) {
    KeyboardButton *keyboardButton = this->getExtendMapping(rowPin, columnPin);
    return keyboardButton;
  }
  else {
    KeyboardButton *keyboardButton = this->getBasicMapping(rowPin, columnPin);
    return keyboardButton;
  }
}

void KeyboardManager::DisplayMappingModeName() {
  
}

KeyboardButton *KeyboardManager::getBasicMapping(int8_t rowPin, int8_t columnPin)
{
  switch (rowPin) {
    case 21:
      switch (columnPin) {
        case 4:
          return &this->keyboardButtons[0]; //
          break;
        case 5:
          return &this->keyboardButtons[1]; // TAB
          break;
        case 6:
          return &this->keyboardButtons[2]; // CAPS_LOCK
          break;
        case 7:
          return &this->keyboardButtons[3]; // SHIFT
          break;
        case 8:
          return &this->keyboardButtons[4]; // GUI
          break;
      }
      break;
    case 20:
      switch (columnPin) {
        case 4:
          return &this->keyboardButtons[5]; // 1
          break;
        case 5:
          return &this->keyboardButtons[6]; // Q
          break;
        case 6:
          return &this->keyboardButtons[7]; // A
          break;
        case 7:
          return &this->keyboardButtons[8]; // Z
          break;
        case 8:
          return &this->keyboardButtons[9]; // F1
          break;
      }
      break;
    case 19:
      switch (columnPin) {
        case 4:
          return &this->keyboardButtons[10]; // 2
          break;
        case 5:
          return &this->keyboardButtons[11]; // W
          break;
        case 6:
          return &this->keyboardButtons[12]; // S
          break;
        case 7:
          return &this->keyboardButtons[13]; // X
          break;
        case 8:
          return &this->keyboardButtons[14]; // F2
          break;
      }
      break;
    case 18:
      switch (columnPin) {
        case 4:
          return &this->keyboardButtons[15]; // 3
          break;
        case 5:
          return &this->keyboardButtons[16]; // E
          break;
        case 6:
          return &this->keyboardButtons[17]; // D
          break;
        case 7:
          return &this->keyboardButtons[18]; // C
          break;
        case 8:
          return &this->keyboardButtons[19]; // F3
          break;
      }
      break;
    case 15:
      switch (columnPin) {
        case 4:
          return &this->keyboardButtons[20]; // 4
          break;
        case 5:
          return &this->keyboardButtons[21]; // R
          break;
        case 6:
          return &this->keyboardButtons[22]; // F
          break;
        case 7:
          return &this->keyboardButtons[23]; // V
          break;
        case 8:
          return &this->keyboardButtons[24]; // F4
          break;
      }
      break;
    case 14:
      switch (columnPin) {
        case 4:
          return &this->keyboardButtons[25]; // 5
          break;
        case 5:
          return &this->keyboardButtons[26]; // T
          break;
        case 6:
          return &this->keyboardButtons[27]; // G
          break;
        case 7:
          return &this->keyboardButtons[28]; // B
          break;
        case 8:
          return &this->keyboardButtons[32]; // ' '
          break;
      }
      break;
    case 16:
      switch (columnPin) {
        case 4:
          return &this->keyboardButtons[29]; // ESC
          break;
        case 5:
          return &this->keyboardButtons[30]; // F6
          break;
        case 6:
          return &this->keyboardButtons[31]; // F5
          break;
        case 7:
          return &this->keyboardButtons[37]; // ALT
          break;
        case 8:
          return &this->keyboardButtons[33]; // CTRL
          break;
      }
      break;
    case 10:
      switch (columnPin) {
        case 6:
          return &this->keyboardButtons[34]; // FN
          break;
        case 7:
          return &this->keyboardButtons[36];
          break;
        case 8:
          return &this->keyboardButtons[35];
          break;
      }
      break;
  }
  return &this->noneButton;
}

KeyboardButton *KeyboardManager::getExtendMapping(int8_t rowPin, int8_t columnPin)
{
  switch (rowPin) {
    case 21:
      switch (columnPin) {
        case 4:
          return &this->keyboardButtons[0]; //
          break;
        case 5:
          return &this->keyboardButtons[1]; // TAB
          break;
        case 6:
          return &this->keyboardButtons[2]; // CAPS_LOCK
          break;
        case 7:
          return &this->keyboardButtons[3]; // SHIFT
          break;
        case 8:
          return &this->keyboardButtons[4]; // GUI
          break;
      }
      break;
    case 20:
      switch (columnPin) {
        case 4:
          return &this->noneButton;
          break;
        case 5:
          return &this->noneButton;
          break;
        case 6:
          return &this->noneButton;
          break;
        case 7:
          return &this->noneButton;
          break;
        case 8:
          return &this->keyboardButtons[43]; // F12
          break;
      }
      break;
    case 19:
      switch (columnPin) {
        case 4:
          return &this->noneButton;
          break;
        case 5:
          return &this->keyboardButtons[50];
          break;
        case 6:
          return &this->noneButton;
          break;
        case 7:
          return &this->noneButton;
          break;
        case 8:
          return &this->keyboardButtons[42]; // F11
          break;
      }
      break;
    case 18:
      switch (columnPin) {
        case 4:
          return &this->noneButton;
          break;
        case 5:
          return &this->keyboardButtons[52];
          break;
        case 6:
          return &this->noneButton;
          break;
        case 7:
          return &this->keyboardButtons[46];
          break;
        case 8:
          return &this->keyboardButtons[41]; // F10
          break;
      }
      break;
    case 15:
      switch (columnPin) {
        case 4:
          return &this->noneButton;
          break;
        case 5:
          return &this->keyboardButtons[51];
          break;
        case 6:
          return &this->keyboardButtons[44];
          break;
        case 7:
          return &this->keyboardButtons[45];
          break;
        case 8:
          return &this->keyboardButtons[40]; // F9
          break;
      }
      break;
    case 14:
      switch (columnPin) {
        case 4:
          return &this->noneButton;
          break;
        case 5:
          return &this->keyboardButtons[48]; // BACK
          break;
        case 6:
          return &this->keyboardButtons[49]; // RETURN
          break;
        case 7:
          return &this->keyboardButtons[47];
          break;
        case 8:
          return &this->keyboardButtons[32]; // ' '
          break;
      }
      break;
    case 16:
      switch (columnPin) {
        case 4:
          return &this->noneButton;
          break;
        case 5:
          return &this->keyboardButtons[38]; // F7
          break;
        case 6:
          return &this->keyboardButtons[39]; // F8
          break;
        case 7:
          return &this->keyboardButtons[37]; // ALT
          break;
        case 8:
          return &this->keyboardButtons[33]; // CTRL
          break;
      }
      break;
    case 10:
      switch (columnPin) {
        case 6:
          return &this->keyboardButtons[34]; // FN
          break;
        case 7:
          return &this->keyboardButtons[36];
          break;
        case 8:
          return &this->keyboardButtons[35];
          break;
      }
      break;
  }
  return &this->noneButton;
}
