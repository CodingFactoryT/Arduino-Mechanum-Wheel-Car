#include <Arduino.h>

byte temperature_symbol[] = {
  B00100,
  B01010,
  B01010,
  B01010,
  B01110,
  B11111,
  B11111,
  B01110
};

byte humidity_symbol[] = {
  B00100,
  B01010,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B01110
};

byte lightbulb_symbol[] = {
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
  B01110,
  B00000,
  B01110
};

byte car_symbol_top_left[] = {
  B00011,
  B00100,
  B01000,
  B11000,
  B11000,
  B11000,
  B01000,
  B01000
};

byte car_symbol_bottom_left[] = {
  B01000,
  B01000,
  B11000,
  B11000,
  B11000,
  B01000,
  B00100,
  B00011
};

byte car_symbol_top_right[] = {
  B11000,
  B00100,
  B00010,
  B00011,
  B00011,
  B00011,
  B00010,
  B00010
};

byte car_symbol_bottom_right[] = {
  B00010,
  B00010,
  B00011,
  B00011,
  B00011,
  B00010,
  B00100,
  B11000
};