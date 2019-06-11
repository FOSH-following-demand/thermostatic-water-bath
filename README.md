# equipment_repository_template

This is a template repository. should be used as a guideline by people/groups developing equipment in this project

Readme can have a link to all the relevant files/documents and can/should be used to give examples of data collected with the device as well as the rational behind its construction.

Should also have mentions to code of conduct and contributing guidelines.

# Open Source thermostatic wather bath 
In testing laboratories, it is always useful to keep reagents or tests that are for analysis at certain temperatures.
A thermostatic bath is an equipment designed to maintain and stabilize the temperature of objects that are introduced into it.
Typically, thermostatic baths are composed of electric heaters that heat distilled water, and when they reach a certain temperature, they are automatically disconnected from the power.
Our idea is to use efficiency and robustness as a basis, which is why we will use Peltier cells to take advantage of the Peltier effect, normally used as thermoelectric coolant.
But, the advantage of using these cells, is that if we reverse the polarity, we could extract heat instead of generating it.
Therefore, we would have a thermostatic bath capable of generating heat or cold without modifying its design or changing any part.
The project will consist of a control circuit, the design of the same and the construction of the storage box.
Microcontrollers based on the ATMEGA328p will be used primarily for first tests and calibration of the sensors.
After that is made, the goal will be to use one "We Mos D1 Mini" board as the main controller, and as a addon, the capable of connecting to cayenne web services as monitor and remote controller using MQTT and IoT Technology.
 

The electrical resistances if they do not have water are burned (If they do not have electronic protection circuits, which is usual)
