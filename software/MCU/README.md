# Code of the Arduino UNO
<a href="First Version" title="First Version"><img src="https://img.shields.io/badge/first%20version-0.0.1-brightgreen"></a>

<a href="Actual Version" title="Actual Version"><img src="https://img.shields.io/badge/Actual%20Version-0.0.2-green"></a>

# Version history

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
