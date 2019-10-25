# Version history

<a href="First Version" title="First Version"><img src="https://img.shields.io/badge/first%20version-0.0.1-brightgreen"></a>

<a href="Actual Version" title="Actual Version"><img src="https://img.shields.io/badge/Version-0.0.8-red"></a>

<a href="Beta Version" title="Beta Version"><img src="https://img.shields.io/badge/Beta-0.0.9-green"></a>

### Program 0.0.1 (Alpha)
  First version of the software
  * it uses the most crude code as possible
  * all the sensors and current measuring
  * the kp, ki and kd was not set in the code.
  * Baud-rate set to 9600

### Program 0.0.2 (Squeeze)
  First stable program
  * Added new custom characters to the lcd screen.
  * the Current sensor was eliminated
  * the kp and kd where set in function with the experiment
  * Baud-rate set to 19200
  * It uses P-D control to stabilze the temperature, while trying to get the set temp as fast as possible, it includes all the functions in the main sketch.

### Program 0.0.3 (Buster)
  First program to include the custom libraries to test it by __ONLY HEATING__
  * peltier library was _included_ in the folder, and updated in the __library__ folder
  * First program to use object-orientated peltier functions.

### Program 0.0.4 (Woddy)
  Last program to use the Arduino UNO Architecture, (microcontroller ATMEGA328-P)
  * This is the first program that can use the basic PID control, not only PD
  * kp, ki, and kd were set in two different ways, one in _aggresive mode_ and the other in _conservative mode_ ([What is this?](https://github.com/FOSH-following-demand/thermostatic-water-bath/blob/master/documentation/using/PID_Tunning%20Guide_Rice.pdf))
  * new routines for interrupts, they are used to change the setpoint, every turn makes +.1 °C in clockwise rotation and -.1°C in counterclockwise. [how to connect?](link)
  * The peltier library is located [here](https://github.com/br3ttb/Arduino-PID-Library/), [how to use it?](https://playground.arduino.cc/Code/PIDLibrary/)

  You'll need to install __Adafruit_BME280__ and __Adafruit_Sensor__ in order to try this sketch, refer to [0.0.5](https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/software/MCU#program-005) to learn how to.

### Program 0.0.5 (Buzz)
  __NEW Architecture__: Now we're using the _NODEMCU-32S_ for the project, the peltier library was converted (But is in testing) to use
  analogWrite function (because ESP32 doesn't have the function to do that)
  * It uses the PID Control used in [0.0.4](https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/software/MCU#program-004), with the kp,ki and kd tunned for the main construction.
  * There was added a BMP280 sensor to check the ambient temperature, so we can calculate the maximum and minimum temperature of the equipment, [How to connect ?](link)
  * The interrupts routines were eliminated, because in the new architecture this is not mandatory.
  * The peltier library is located [here](https://github.com/br3ttb/Arduino-PID-Library/), [how to use it?](https://playground.arduino.cc/Code/PIDLibrary/)

  You'll need to install __Adafruit_BME280__ and __Adafruit_Sensor__ in order to try this sketch.
  * [How to install Adafruit_Sensor in Arduino IDE?](https://www.arduinolibraries.info/libraries/adafruit-unified-sensor)
  * [How to install Adafruit_BME280 in Arduino IDE?](https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout/arduino-test#install-adafruit-bme280-library-4-7)

### Program 0.0.5 (Lenny)

  * __Using the _NODEMCU-32s__: First version to include Tasks and multi-core processing of them.
  * It uses the PID Control used in [0.0.5](https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/software/MCU#program-005), with the kp,ki and kd tunned for the main construction.
  * The Peltier library was a bit modified to work with the new architecture
  * This program __IS NOT STABLE__ because has a lot of _crude code_, the tests aren't done yet for this program.
  * WIP : The interrupt routines and the connection between the tasks using global variables.
  * the BMP280 was eliminated, the funcion was very expendable.

### Program 0.0.6 (Sarge)
* __Using the _NODEMCU-32s__: Second version: Tasks and multi-core processing.
* _Queue_ testing, FREERTOS in Arduino IDE__
* This program __Might not work__
* Updated the tasks for managing the data.

### Program 0.0.7 (Mike)
* __Using the _NODEMCU-32s__: Third version: Tasks and multi-core processing.
* Baud-rate set to 115200
* Hard-coded HTML code to show data in the browser. (Requieres internet connection for showing some symbols)
* Added landed (crude) web page to set the _setpoint_
* Problem solved with the Global variables and the share between tasks: Only one archive _(.ino)__ for all and _no queues_

### Program 0.0.8 (Tango)
* __Using the _NODEMCU-32s__: Last version in the Arduino IDE.
* Final assambly without the [Mozilla IoT WebThings Framework](https://iot.mozilla.org/)
* Baud-rate set to 115200
* This code is marked as STABLE but with no release.

### Program 0.0.9 (Slinky)
* __Using the _NODEMCU-32s and PlatformIO Framework__ --> [how to install PlatformIO?](https://platformio.org/install/ide?install=atom)
* _We need ATOM enviorment_ --> [how to install the last version of Atom?](https://atom.io/)
* In the source code located in /src/main.cpp you have to mannualy __set the SSID and the password of your WiFi Network__
* This program __only reads the temperature of the ds18b20 sensor and then send it to the WebThings Server__  --> [How to build one on a Raspberry Pi 3?](https://iot.mozilla.org/docs/gateway-getting-started-guide.html)
* Project name _webthing demo_, no screen, no PID Control, no setpoint.
* Baud-rate set to 115200
* __Very important!__: specific version of libraries are required to compile and run in the , _webthing-arduino 0.0.9_ , _PageBuilder 1.3.4_ and _arduinoJson 5.13.4_. the last one took a lot to catch...



# How to work with this programs? (from Version 0.0.1 to 0.0.7)

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
