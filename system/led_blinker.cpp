
#include "led_blinker.h"
#include "sensesp.h"

#ifndef LED_PIN
// #define LED_PIN LED_BUILTIN  // If your board doesn't have a defined LED_BUILTIN, comment this line out...
#define LED_PIN 15        // ... and uncomment this line, and change 13 to any LED pin you have. If you have none, leave it at 13.
#endif

LedBlinker::LedBlinker() {
  pinMode(LED_PIN, OUTPUT);
  this->led_off();
}

void LedBlinker::led_off() {
  digitalWrite(LED_PIN,LOW);
}

void LedBlinker::led_on() {
  digitalWrite(LED_PIN,HIGH);
}

void LedBlinker::remove_blinker() {
  if (this->blinker != nullptr) {
    this->blinker->remove();
  }
}

void LedBlinker::set_state(int new_state) {
  if (new_state) {
    this->led_on();
  }
  else {
    this->led_off();
  }
}

void LedBlinker::flip() {
  if (digitalRead(LED_PIN)==HIGH) {
    this->led_off();
    // Serial.print("Flip: Currently on");
  }
  else {
    this->led_on();
    // Serial.print("Flip: Currently off");
  }
}

void LedBlinker::set_wifi_disconnected() {
  this->remove_blinker();
  this->blinker = app.onRepeat(1000, [this] () {
    this->led_on();
    app.onDelay(100, [this] () {
      this->led_off();
    });
  });
}

void LedBlinker::set_wifi_connected() {
  this->remove_blinker();
  this->blinker = app.onRepeat(1000, [this] () {
    this->flip();
  });
}

int b = 0;
void LedBlinker::set_server_connected() {
  this->remove_blinker();
  this->blinker = app.onRepeat(100, [this] () {
    if (b==0) {
      this->led_on();
    }
    else {
      this->led_off();
    }
    b++;
    if (b==200) {
      b=0;
    }
  });
}
