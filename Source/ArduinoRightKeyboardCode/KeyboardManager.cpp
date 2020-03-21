//
//
//

#include <Keyboard.h>
#include <Mouse.h>
#include "KeyboardButton.h"
#include "KeyboardManager.h"

KeyboardManager::KeyboardManager(LiquidCrystal_I2C *liquidCrystalI2C)
{
  int8_t bounceTime = 1;

  this->liquidCrystalI2C = liquidCrystalI2C;

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
  this->keyboardButtons[30] = KeyboardButton(bounceTime, 2, FunctionType); // 右手把滑鼠滾動事件
  this->keyboardButtons[31] = KeyboardButton(bounceTime, 70+136, KeyboardType);

  this->keyboardButtons[32] = KeyboardButton();
}

KeyboardButton *KeyboardManager::GetMiddleScrollButton() {
  return &this->keyboardButtons[30];
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
  for (int8_t i = 0; i < 32; i++)
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
  this->liquidCrystalI2C->clear();
  this->liquidCrystalI2C->setCursor(0, 0);
  this->liquidCrystalI2C->print("Mapping Mode :");
  this->liquidCrystalI2C->setCursor(0, 1);
  this->liquidCrystalI2C->print(" Basic Keyboard");
}

KeyboardButton *KeyboardManager::getBasicMapping(int8_t rowPin, int8_t columnPin)
{
  // 1
  if (rowPin == 21 && columnPin == 6)
    return &this->keyboardButtons[0]; // -
  else if (rowPin == 21 && columnPin == 5)
    return &this->keyboardButtons[1]; // =
  else if (rowPin == 21 && columnPin == 8)
    return &this->keyboardButtons[2]; // [
  else if (rowPin == 21 && columnPin == 7)
    return &this->keyboardButtons[3]; // ]
  else if (rowPin == 21 && columnPin == 9)
    return &this->keyboardButtons[4]; // \

  // 2
  if (rowPin == 20 && columnPin == 6)
    return &this->keyboardButtons[5]; // 0
  else if (rowPin == 20 && columnPin == 5)
    return &this->keyboardButtons[6]; // P
  else if (rowPin == 20 && columnPin == 8)
    return &this->keyboardButtons[7]; // ;
  else if (rowPin == 20 && columnPin == 7)
    return &this->keyboardButtons[8]; // /
  else if (rowPin == 20 && columnPin == 9)
    return &this->keyboardButtons[9]; // F12

  // 3
  if (rowPin == 19 && columnPin == 6)
    return &this->keyboardButtons[10]; // 9
  else if (rowPin == 19 && columnPin == 5)
    return &this->keyboardButtons[11]; // O
  else if (rowPin == 19 && columnPin == 8)
    return &this->keyboardButtons[12]; // L
  else if (rowPin == 19 && columnPin == 7)
    return &this->keyboardButtons[13]; // .
  else if (rowPin == 19 && columnPin == 9)
    return &this->keyboardButtons[14]; // F11

  // 4
  if (rowPin == 16 && columnPin == 6)
    return &this->keyboardButtons[15]; // 8
  else if (rowPin == 16 && columnPin == 5)
    return &this->keyboardButtons[16]; // I
  else if (rowPin == 16 && columnPin == 8)
    return &this->keyboardButtons[17]; // K
  else if (rowPin == 16 && columnPin == 7)
    return &this->keyboardButtons[18]; // ,
  else if (rowPin == 16 && columnPin == 9)
    return &this->keyboardButtons[19]; // F10

  // 5
  if (rowPin == 10 && columnPin == 6)
    return &this->keyboardButtons[20]; // 7
  else if (rowPin == 10 && columnPin == 5)
    return &this->keyboardButtons[21]; // U
  else if (rowPin == 10 && columnPin == 8)
    return &this->keyboardButtons[22]; // J
  else if (rowPin == 10 && columnPin == 7)
    return &this->keyboardButtons[23]; // M
  else if (rowPin == 10 && columnPin == 9)
    return &this->keyboardButtons[24]; // F9

  // 6
  if (rowPin == 14 && columnPin == 6)
    return &this->keyboardButtons[25]; // 6
  else if (rowPin == 14 && columnPin == 5)
    return &this->keyboardButtons[26]; // Y
  else if (rowPin == 14 && columnPin == 8)
    return &this->keyboardButtons[27]; // H
  else if (rowPin == 14 && columnPin == 7)
    return &this->keyboardButtons[28]; // N

  // 7
  if (rowPin == 15 && columnPin == 6)
    return &this->keyboardButtons[29]; //
  else if (rowPin == 15 && columnPin == 5)
    return &this->keyboardButtons[30]; // 滑鼠滾輪滾動
  else if (rowPin == 15 && columnPin == 8)
    return &this->keyboardButtons[31]; // F7

  return &this->keyboardButtons[32];
}
