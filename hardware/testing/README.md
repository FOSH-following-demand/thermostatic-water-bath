# Testing example

### This construction is used to test the peltier element and the driver at the same time, without using microcontrollers.

:hotsprings::hotsprings:__Please note that the peltier element must be crushed with heat sinks in both sides to prevent overheating__ :hotsprings::hotsprings:
### List of materials:

* VNH3SP30 Motor Driver

* TEC1-12715 Peltier Cell

* Power Supply 12v 29A Pronext or equivalent.

* Heat Sink Grease

### Build steps:
  * 1.a : Connect the OUT1A of the VNH3SP30 Driver to the _Black_ wire of the Peltier element. :heavy_check_mark:

  * 1.b : Connect the OUT1B of the VNH3SP30 Driver to the _Red_ wire of the Peltier element. :heavy_check_mark:

  * 1.c : Connect the EN of the VNH3SP30 Driver to 5v rails :heavy_check_mark:

  * 1.d : Connect the INA of the VNH3SP30 Driver to 5v rails :heavy_check_mark:

  * 1.e : Connect the INB of the VNH3SP30 Driver to GND rails :heavy_check_mark:

  * 1.f : Connect the PWM of the VNH3SP30 Driver to 5v rails :heavy_check_mark:

  * 2.a : power up the circuit with __12v__ from the plug, remember that the center is __Positive__ (VCC), and the outside is _negative_ (GND)

<a href="Testingtools" title="Test module schematics"><img src="https://github.com/FOSH-following-demand/thermostatic-water-bath/blob/master/hardware/testing/schDriverTest.png?raw=true"></a>
