#ifndef _mpu9250_H_
#define _mpu9250_H_

#include "quaternionFilters.h"
#include <RemoteDebug.h>
#include "MPU9250.h"
#include "sensor.h"
#include <SPI.h>
#include <Wire.h>   

/*
PU9250 Basic Example Code
 by: Kris Winer
 date: April 1, 2014
 license: Beerware - Use this code however you'd like. If you
 find it useful you can buy me a beer some time.
 Modified by Brent Wilkins July 19, 2016

 Demonstrate basic MPU-9250 functionality including parameterizing the register
 addresses, initializing the sensor, getting properly scaled accelerometer,
 gyroscope, and magnetometer data out. Added display functions to allow display
 to on breadboard monitor. Addition of 9 DoF sensor fusion using open source
 Madgwick and Mahony filter algorithms. Sketch runs on the 3.3 V 8 MHz Pro Mini
 and the Teensy 3.1.

 SDA and SCL should have external pull-up resistors (to 3.3V).
 10k resistors are on the EMSENSR-9250 breakout board.

 Hardware setup:
 MPU9250 Breakout --------- Arduino
 VDD ---------------------- 3.3V
 VDDI --------------------- 3.3V
 SDA ----------------------- A4
 SCL ----------------------- A5
 GND ---------------------- GND
 */

class mpu9250 : public Sensor {
  public:
    mpu9250(uint8_t addr = 0x68, String config_path = "");
    //mpu9250* pMPU9250;
    MPU9250 myIMU;
  private:
    uint8_t addr;
    void check_status();
};


// Pass one of these in the constructor to MPU9250value() to tell which type of value you want to output
enum mpu9250ValType { temperature, pressure, humidity };

// MPU9250value reads and outputs the specified value of a MPU9250 sensor.
class mpu9250value : public NumericSensor {
  public:

  private:
    

};
#endif
