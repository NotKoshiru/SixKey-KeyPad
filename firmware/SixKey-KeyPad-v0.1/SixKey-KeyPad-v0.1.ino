//Подключение библиотек
#include <microDS3231.h>
#include <GyverOLED.h>
#include <FastLED.h>
#include <EncButton.h>
#include <EEPROM.h>
#include <EasyHID.h>

//Что и куда подключено


#ifdef __AVR_ATmega328P__
  #define EcnS1 5
  #define EncS2 6
  #define EncKey 7
  #define BTN1 8
  #define BTN2 9
  #define BTN3 14
  #define BTN4 15
  #define BTN5 16
  #define BTN6 17
  #define addressLED 10
  #define LED_NUM 14
#else
  #define EcnS1 5
  #define EncS2 6
  #define EncKey 4
  #define BTN1 15
  #define BTN2 16
  #define BTN3 17
  #define BTN4 18
  #define BTN5 19
  #define BTN6 20
  #define addressLED 5
  #define LED_NUM 14
#endif

//Инициализация всякого

GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;
EncButton Enc(EncKey, EcnS1, EncS2);
MicroDS3231 rtc;

//Объявление переменных

CRGB leds[LED_NUM];
struct {
  int M1 = 0;
  int M2 = 0;
  int M3 = 0;
  int M4 = 0;
  int M5 = 0;
  int M6 = 0;
  int Brightness = 128;
} settings;


void setup() {
  FastLED.addLeds<WS2812, addressLED, GRB>(leds, LED_NUM);
  FastLED.setBrightness(2);
  oled.init();
  oled.clear();
  oled.setScale(3);
  oled.home();
  leds[0].setRGB(255, 255, 255);
  FastLED.show();
  if (EEPROM.read(0) != 'k') {  //Если включение первое, то:
    leds[1].setRGB(255, 10, 10);
    FastLED.show();
    for (int i = 0 ; i < EEPROM.length() ; i++) {   //Очистка энергонезависимой памяти
      EEPROM.write(i, 0);
    }
    leds[2].setRGB(255, 255, 10);
    FastLED.show();
    EEPROM.put(1, settings);  //
    EEPROM.write(0, 'k');
    leds[3].setRGB(10, 255, 10);
  } else {  //Иначе:
    EEPROM.get(1, settings);  //Прочитать настройки
    leds[1].setRGB(10, 255, 10);
  }
  FastLED.show();
  delay(300);
  FastLED.clear();
  HID.begin();
  pinMode(BTN1,  INPUT_PULLUP);
  pinMode(BTN2,  INPUT_PULLUP);
  pinMode(BTN3,  INPUT_PULLUP);
  pinMode(BTN4,  INPUT_PULLUP);
  pinMode(BTN5,  INPUT_PULLUP);
  pinMode(BTN6,  INPUT_PULLUP);
  
}

void loop() {
  if (digitalRead(BTN1) == 0) {
    Keyboard.press(KEY_1);
  } else {
    Keyboard.release(KEY_1);
  }
  HID.tick();
}
