//
//
//

#include <Keyboard.h>
#include <Mouse.h>
#include "KeyboardButton.h"
#include "KeyboardManager.h"

KeyboardManager::KeyboardManager(MouseManager *mouseManager)
{
  int8_t bounceTime = 1;

  this->keyboardButtons[0] = KeyboardButton(bounceTime, '-', KeyboardType);
  this->keyboardButtons[1] = KeyboardButton(bounceTime, '=', KeyboardType);
  this->keyboardButtons[2] = KeyboardButton(bounceTime, '[', KeyboardType);
  this->keyboardButtons[3] = KeyboardButton(bounceTime, ']', KeyboardType);
  this->keyboardButtons[4] = KeyboardButton(bounceTime, '\'', KeyboardType);

  this->keyboardButtons[5] = KeyboardButton(bounceTime, '0', KeyboardType);
  this->keyboardButtons[6] = KeyboardButton(bounceTime, 'p', KeyboardType);
  this->keyboardButtons[7] = KeyboardButton(bounceTime, ';', KeyboardType);
  this->keyboardButtons[8] = KeyboardButton(bounceTime, '/', KeyboardType);
  this->keyboardButtons[9] = KeyboardButton(bounceTime, KEY_PAGE_DOWN, KeyboardType);

  this->keyboardButtons[10] = KeyboardButton(bounceTime, '9', KeyboardType);
  this->keyboardButtons[11] = KeyboardButton(bounceTime, 'o', KeyboardType);
  this->keyboardButtons[12] = KeyboardButton(bounceTime, 'l', KeyboardType);
  this->keyboardButtons[13] = KeyboardButton(bounceTime, '.', KeyboardType);
  this->keyboardButtons[14] = KeyboardButton(bounceTime, KEY_PAGE_UP, KeyboardType);

  this->keyboardButtons[15] = KeyboardButton(bounceTime, '8', KeyboardType);
  this->keyboardButtons[16] = KeyboardButton(bounceTime, 'i', KeyboardType);
  this->keyboardButtons[17] = KeyboardButton(bounceTime, 'k', KeyboardType);
  this->keyboardButtons[18] = KeyboardButton(bounceTime, ',', KeyboardType);
  this->keyboardButtons[19] = KeyboardButton(bounceTime, KEY_DELETE, KeyboardType);

  this->keyboardButtons[20] = KeyboardButton(bounceTime, '7', KeyboardType);
  this->keyboardButtons[21] = KeyboardButton(bounceTime, 'u', KeyboardType);
  this->keyboardButtons[22] = KeyboardButton(bounceTime, 'j', KeyboardType);
  this->keyboardButtons[23] = KeyboardButton(bounceTime, 'm', KeyboardType);
  this->keyboardButtons[24] = KeyboardButton(bounceTime, KEY_INSERT, KeyboardType);

  this->keyboardButtons[25] = KeyboardButton(bounceTime, '6', KeyboardType);
  this->keyboardButtons[26] = KeyboardButton(bounceTime, 'y', KeyboardType);
  this->keyboardButtons[27] = KeyboardButton(bounceTime, 'h', KeyboardType);
  this->keyboardButtons[28] = KeyboardButton(bounceTime, 'n', KeyboardType);

  this->keyboardButtons[29] = KeyboardButton(bounceTime, '\\', KeyboardType);
  this->keyboardButtons[30] = KeyboardButton(bounceTime, 70 + 136, KeyboardType);
  this->keyboardButtons[31] = KeyboardButton(bounceTime, 2, FunctionType); // 滑鼠滾輪

  this->keyboardButtons[32] = KeyboardButton(bounceTime, 3, FunctionType); // 滑鼠上
  this->keyboardButtons[33] = KeyboardButton();
  this->keyboardButtons[34] = KeyboardButton();
  this->keyboardButtons[35] = KeyboardButton(bounceTime, 6, FunctionType); // 滑鼠下
  this->keyboardButtons[36] = KeyboardButton(bounceTime, 7, FunctionType); // 滑鼠左
  this->keyboardButtons[37] = KeyboardButton(bounceTime, 8, FunctionType); // 滑鼠右

  this->keyboardButtons[38] = KeyboardButton();

  mouseManager->MouseButtons[0] = &this->keyboardButtons[32];
  mouseManager->MouseButtons[1] = &this->keyboardButtons[35];
  mouseManager->MouseButtons[2] = &this->keyboardButtons[36];
  mouseManager->MouseButtons[3] = &this->keyboardButtons[37];
  mouseManager->MouseButtons[4] = &this->keyboardButtons[31];
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
  }
}

void KeyboardManager::Execution()
{
  for (int8_t i = 0; i < 40; i++)
  {
    KeyboardButton keyboardButton = this->keyboardButtons[i];
    keyboardButton.OperationPress();
    keyboardButton.OperationRelease();
  }
}

KeyboardButton *KeyboardManager::GetMapping(int8_t rowPin, int8_t columnPin)
{
  KeyboardButton *keyboardButton = this->getBasicMapping(rowPin, columnPin);
  return keyboardButton;
}

void KeyboardManager::DisplayMappingModeName() {
}

KeyboardButton *KeyboardManager::getBasicMapping(int8_t rowPin, int8_t columnPin)
{
  switch (rowPin) {
    case 21:
      switch (columnPin) {
        case 6:
          return &this->keyboardButtons[0]; // -
          break;
        case 5:
          return &this->keyboardButtons[1]; // =
          break;
        case 8:
          return &this->keyboardButtons[2]; // [
          break;
        case 7:
          return &this->keyboardButtons[3]; // ]
          break;
        case 9:
          return &this->keyboardButtons[4]; // \
          break;
      }
      break;
    case 20:
      switch (columnPin) {
        case 6:
          return &this->keyboardButtons[5]; // 0
          break;
        case 5:
          return &this->keyboardButtons[6]; // P
          break;
        case 8:
          return &this->keyboardButtons[7]; // ;
          break;
        case 7:
          return &this->keyboardButtons[8]; // /
          break;
        case 9:
          return &this->keyboardButtons[9]; // Print
          break;
      }
      break;
    case 19:
      switch (columnPin) {
        case 6:
          return &this->keyboardButtons[10]; // 9
          break;
        case 5:
          return &this->keyboardButtons[11]; // O
          break;
        case 8:
          return &this->keyboardButtons[12]; // L
          break;
        case 7:
          return &this->keyboardButtons[13]; // .
          break;
        case 9:
          return &this->keyboardButtons[14]; // F11
          break;
      }
      break;
    case 18:
      switch (columnPin) {
        case 6:
          return &this->keyboardButtons[15]; // 8
          break;
        case 5:
          return &this->keyboardButtons[16]; // I
          break;
        case 8:
          return &this->keyboardButtons[17]; // K
          break;
        case 7:
          return &this->keyboardButtons[18]; // ,
          break;
        case 9:
          return &this->keyboardButtons[19]; // F10
          break;
      }
      break;
    case 10:
      switch (columnPin) {
        case 6:
          return &this->keyboardButtons[20]; // 7
          break;
        case 5:
          return &this->keyboardButtons[21]; // U
          break;
        case 8:
          return &this->keyboardButtons[22]; // J
          break;
        case 7:
          return &this->keyboardButtons[23]; // M
          break;
        case 9:
          return &this->keyboardButtons[24]; // F9
          break;
      }
      break;
    case 16:
      switch (columnPin) {
        case 6:
          return &this->keyboardButtons[25]; // 6
          break;
        case 5:
          return &this->keyboardButtons[26]; // Y
          break;
        case 8:
          return &this->keyboardButtons[27]; // H
          break;
        case 7:
          return &this->keyboardButtons[28]; // N
          break;
          
        case 9:
          return &this->keyboardButtons[37]; // N
          break;
      }
      break;
    case 14:
      switch (columnPin) {
        case 6:
          return &this->keyboardButtons[29]; //
          break;
        case 5:
          return &this->keyboardButtons[30]; //
          break;
        case 8:
          return &this->keyboardButtons[31]; //
          break;

        case 7:
          return &this->keyboardButtons[32]; //
          break;
        case 9:
          return &this->keyboardButtons[36]; //
          break;
      }
      break;
     case 15:
      switch (columnPin) {
        case 7:
          return &this->keyboardButtons[33]; //
          break;
        case 9:
          return &this->keyboardButtons[34]; //
          break;
        case 8:
          return &this->keyboardButtons[35]; //
          break;
      }
      break;
  }

  return &this->keyboardButtons[38];
}
