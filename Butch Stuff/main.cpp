// BME280_example.cpp

#include <Arduino.h>

//#define SERIAL_DEBUG_DISABLED

#define USE_LIB_WEBSOCKET true

#include "sensesp_app.h"
#include "signalk/signalk_output.h"
#include "sensors/bme280.h"

ReactESP app([] () {
  #ifndef SERIAL_DEBUG_DISABLED
  Serial.begin(115200);

  // A small arbitrary delay is required to let the
  // serial port catch up

  delay(100);
  Debug.setSerialEnabled(true);
  #endif

  // true will disable systemHz, freemem, uptime, and ipaddress "sensors"
  bool disableStandardSensors = false;

  sensesp_app = new SensESPApp(disableStandardSensors);

// Create a BME280, which represents the physical sensor.
// 0x77 is the default address. Some chips use 0x76, which is shown here.
auto* pBME280 = new BME280(0x76);


const uint read_delay = 1000;
const uint pressure_read_delay = 5000;

// Create a BME280value, which is used to read a specific value from the BME280, and send its output
// to SignalK as a number (float). This one is for the temperature reading.
auto* pBMEtemperature = new BME280value(pBME280, temperature,  read_delay, "/Temperature");
      
      pBMEtemperature->connectTo(new SKOutputNumber());


// Do the same for the barometric pressure value.
auto* pBMEpressure = new BME280value(pBME280, pressure,  pressure_read_delay, "/Pressure");
      
      pBMEpressure->connectTo(new SKOutputNumber());


// Do the same for the humidity value.
auto* pBMEhumidity = new BME280value(pBME280, humidity,  read_delay, "/Humidity");
      
      pBMEhumidity->connectTo(new SKOutputNumber());      


  sensesp_app->enable();
});
