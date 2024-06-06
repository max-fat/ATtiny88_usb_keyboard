/*
   Пример эмуляции клавиатуры EasyHID
   Можно нажимать, отжимать и кликать одновременно до 5ти клавиш
   Нажатые клавиши буфферизируются, клавиши модификаторы (ALT,CTRL...) так же
   работают Список всех доступных клавиш см. в файле Codekeys.h
*/

#include <EasyHID.h>
// Либа HID
#include <Keypad.h>

const byte ROWS = 2;  // four rows
const byte COLS = 3;  // four columns
// define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
    {166, 0x01, 0x06},
    {0x24, 0x25, 0x26}
};
byte rowPins[ROWS] = {9, 8};      // connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 7, 6};  // connect to the column pinouts of the keypad

uint32_t tmr1;
byte button;

// initialize an instance of class NewKeypad
Keypad customKeypad =
    Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  // customKeypad.addEventListener(keypadEvent);
  // Add an event listener for this keypad
  HID.begin();  // Инициализация USB
}

void loop() {
  char customKey = customKeypad.getKey();
  if (customKey) {
    Keyboard.clickMultimediaKey(customKey);
    // Keyboard.click(customKey);
    // Keyboard.press(customKey);
    // Keyboard.release(customKey);
    // Keyboard.clickSystemKey(customKey);
  }
  HID.tick();  // Вызываем тикер не реже чем каждые 10 мс!

  if (millis() - tmr1 >= 500) {  // ищем разницу
    tmr1 = millis();             // сброс таймера
    button++;
    // if (button == 0x46 ){button++;};
    // if (button < 0x04 ){button=4;};
    // Keyboard.clickMultimediaKey(button);
  }
}

// Taking care of some special events.
void keypadEvent(KeypadEvent key) {
  switch (customKeypad.getState()) {
    case PRESSED:
      Keyboard.press(key);
      break;

    case RELEASED:
      Keyboard.release(key);
      break;
  }
}
