// ina226_example_main_cpp.txt

#include <Arduino.h>

//#define SERIAL_DEBUG_DISABLED

#define USE_LIB_WEBSOCKET true

#include "sensesp_app.h"
#include "signalk/signalk_output.h"
#include "sensors/ina226value.h"

ReactESP app([] () {
  #ifndef SERIAL_DEBUG_DISABLED
  Serial.begin(115200);

  // A small arbitrary delay is required to let the
  // serial port catch up

  delay(100);
  Debug.setSerialEnabled(true);
  #endif

  // Create the SensESPApp with whatever "standard sensors" you want: noStdSensors, allStdSensors, or uptimeOnly.
  // The default is allStdSensors.
  sensesp_app = new SensESPApp(uptimeOnly);

  // Create a pointer to an INA226, which represents the physical sensor.
  // 0x40 is the default address. Chips can be modified to use 0x41 (shown here), 0x44, or 0x45.
  // It's up to you to provide the proper values for begin(), configure(), and calibrate() - see
  // https://github.com/jarzebski/Arduino-INA226.
  auto* pINA226 = new INA226();
  pINA226->begin();  // uses the default address of 0x40
  pINA226->configure();  // uses the default values
  pINA226->calibrate();  // uses the default values
  // Now the INA226 is ready for reading, which will be done by the INA226value class.

  // Define the read_delay you're going to use, if other than the default of 500 ms.
  const uint read_delay = 1000; // once per second

  // Create an INA226value, which is used to read a specific value from the INA226, and send its output
  // to SignalK as a number (float). This one is for the bus voltage.
  auto* pINA226busVoltage = new INA226value(pINA226, bus_voltage, read_delay, "/someElectricDevice/busVoltage");
      
      pINA226busVoltage->connectTo(new SKOutputNumber("electrical.someelectricdevice.busVoltage"));

  // Here you can add as many INA226value's as you need to read all the values you want. See the INA219
  // example for details.    

  sensesp_app->enable();
});
