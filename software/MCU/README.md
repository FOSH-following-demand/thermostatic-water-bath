# Version history

<a href="First Version" title="First Version"><img src="https://img.shields.io/badge/first%20version-0.0.1-brightgreen"></a>

<a href="Actual Version" title="Actual Version"><img src="https://img.shields.io/badge/Actual%20Version-0.0.2-green"></a>


### Program 0.0.1
  First version of the software
  * it uses the most crude code as possible
  * all the sensors and current measuring
  * the kp, ki and kd was not set in the code.

### Program 0.0.2
  First stable program
  * Added new custom characters to the lcd screen.
  * the Current sensor was eliminated
  * the kp and kd where set in function with the experiment
  * It uses P-D control to stabilze the temperature, while trying to get the set temp as fast as possible, it includes all the functions in the main sketch.

### Program 0.0.3
  First program to include the custom libraries to test it by __ONLY HEATING__
  * peltier library was _included_ in the folder, and updated in the __library__ folder
  * First program to use object-orientated peltier functions.

### Program 0.0.4
  Last program to use the Arduino UNO Architecture, (microcontroller ATMEGA328-P)
  * This is the first program that can use the basic PID control, not only PD
  * kp, ki, and kd were set in two different ways, one in _aggresive mode_ and the other in _conservative mode_ ([What is this?](link))
  * new routines for interrupts, they are used to change the setpoint, every turn makes +.1 °C in clockwise rotation and -.1°C in counterclockwise. [how to connect?](link)
  * The peltier library is located [here](https://github.com/br3ttb/Arduino-PID-Library/), [how to use it?](https://playground.arduino.cc/Code/PIDLibrary/)

  You'll need to install __Adafruit_BME280__ and __Adafruit_Sensor__ in order to try this sketch, refer to [0.0.5](https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/software/MCU#program-005) to learn how to.

### Program 0.0.5
  __NEW Architecture__: Now we're using the _NODEMCU-32S_ for the project, the peltier library was converted (But is in testing) to use
  analogWrite function (because ESP32 doesn't have the function to do that)
  * It uses the PID Control used in [0.0.4](https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/software/MCU#program-004), with the kp,ki and kd tunned for the main construction.
  * There was added a BMP280 sensor to check the ambient temperature, so we can calculate the maximum and minimum temperature of the equipment, [How to connect ?](link)
  * The interrupts routines were eliminated, because in the new architecture this is not mandatory.
  * The peltier library is located [here](https://github.com/br3ttb/Arduino-PID-Library/), [how to use it?](https://playground.arduino.cc/Code/PIDLibrary/)

  You'll need to install __Adafruit_BME280__ and __Adafruit_Sensor__ in order to try this sketch.
  * [How to install Adafruit_Sensor in Arduino IDE?](https://www.arduinolibraries.info/libraries/adafruit-unified-sensor)
  * [How to install Adafruit_BME280 in Arduino IDE?](https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout/arduino-test#install-adafruit-bme280-library-4-7)

# How to work with this programs?

To test this sketch's, you must install the library included in the arduino database.

in order to do this, let's go to Library Manager of the __Arduino IDE__, located in

_Program --> Include library --> Library Manager_

![1](https://github.com/FOSH-following-demand/thermostatic-wather-bath/blob/master/software/img/1.png)


then, you can install the lastest version of the _dallasTemperature_ after searching for it
![2](https://github.com/FOSH-following-demand/thermostatic-wather-bath/blob/master/software/img/dallas.png)


In order to setup the LCD, you __must__ install the _LiquidCrystal_I2C_ library, __NOT__ the LiquidCrystal
![3](https://github.com/FOSH-following-demand/thermostatic-wather-bath/blob/master/software/img/liquid.png)


The last remaining item, is the __oneWire__ library to control the _DS18B20_ sensor.
![4](https://github.com/FOSH-following-demand/thermostatic-wather-bath/blob/master/software/img/onew.png)
