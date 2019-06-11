
# Open Source thermostatic wather bath 
In testing laboratories, it is always useful to keep reagents or tests that are analyzed at certain temperatures.
A thermostatic bath is a device designed to maintain and stabilize the temperature of the objects that enter it.
In general, the thermostatic baths are composed of electric heaters that heat the distilled water and, when they reach a certain temperature, they are automatically disconnected from the energy.
Our idea is to use efficiency and solidity as a basis, so we will use Peltier cells to take advantage of the Peltier effect, which is normally used as a thermoelectric coolant.
But, the advantage of using these cells, is that if we reverse the polarity, we could extract heat instead of generating it.
Therefore, we would have a thermostatic bath capable of generating heat or cold without modifying its design or changing any part.
The project will consist of a control circuit, the design of the same and the construction of the storage box.
The microcontrollers based on the ATMEGA328p will be used mainly for the first tests and the calibration of the sensors.
Once this is done, the objective will be to use a "We Mos D1 Mini" board as the main controller and, as a complement, the ability to connect to Cayenne web services as a monitor and remote control through IoT technology.

The electric resistors if they do not have water are burned (if they do not have electronic protection circuits, as usual), with the design proposed in this project, we will try to avoid it by measuring the current that the cell consumes, so we can determine, without using another type of sensors, if the container where the piece is located, has enough distilled water or refrigerant (in case you want to cool)
