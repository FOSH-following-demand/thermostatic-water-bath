
***Building instructions:***

<br>

### 1. __Getting started__

#_How to upload the code to the arduino?_
  First, after downloading the arduino IDE for different [plataforms](https://www.arduino.cc/) and Configuring it as is showned [here](https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/software/MCU) we need to upload the code.

  After cloning or downloading all the package, you'll download the last version of the code on the __/master/software/MCU__ directory (_actually is 0.0.2_).

  Now, you will open the arduino IDE, and an empty sketch will be loaded
  <a href="https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/software/MCU" title="scr0"><img src="https://github.com/FOSH-following-demand/thermostatic-water-bath/blob/master/documentation/building/pictures/scr0.png?raw=true"></a>

  __To load a program__ you need to open the file called _0.0.2_ (the last version of the software)
  <a href="https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/software/MCU" title="scr0"><img src="https://github.com/FOSH-following-demand/thermostatic-water-bath/blob/master/documentation/building/pictures/scr1.png?raw=true"></a>

  Click __Open__
  <a href="https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/software/MCU" title="scr0"><img src="https://github.com/FOSH-following-demand/thermostatic-water-bath/blob/master/documentation/building/pictures/scr2.png?raw=true"></a>

  Once the program is loaded, you'll need to verify it using the Check button :heavy_check_mark: .

  if everything is correct, and the arduino is correcly connected based on the schematics, you can upload the code using the right arrow :arrow_right:

  __WARNING:__  Make sure than you selected the correct _microcontroller_ in the selection menu, as showned here
  <a href="https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/software/MCU" title="scr0"><img src="https://github.com/FOSH-following-demand/thermostatic-water-bath/blob/master/documentation/building/pictures/scr3.png?raw=true"></a>

  After that, you'll see the current temperature in the monitor of the Arduino Serial Monitor (you can use _crtl + shift + m_ as direct access) as showned on the end of the video.

![Video](https://github.com/FOSH-following-demand/thermostatic-water-bath/blob/master/documentation/building/out.gif)


### 2. List of materials needed:
  for the main electronics, We'll need the follwoing, as described [here](https://github.com/FOSH-following-demand/thermostatic-water-bath/blob/master/hardware/datasheets/datasheets.md) in the electronics datasheets files.

  * VNH3SP30 Motor Driver

  * TEC1-12715 Peltier Cell

  * Power Supply 12v 29A Pronext or equivalent.

  * Arduino UNO Rev 3

  * Heat Sink Grease

### 3. build steps:
  * 3.a : Connect the OUT1A of the VNH3SP30 Driver to the _Black_ wire of the Peltier element.

  * 3.b : Connect the OUT1B of the VNH3SP30 Driver to the _Red_ wire of the Peltier element.

  * 3.c : Connect the EN of the VNH3SP30 Driver to the _Digital Pin 6_ wire of the Arduino UNO.

  * 3.d : Connect the INA of the VNH3SP30 Driver to the _Digital Pin 4_ wire of the Arduino UNO.

  * 3.e : Connect the INB of the VNH3SP30 Driver to the _Digital Pin 7_ wire of the Arduino UNO.

  * 3.f : Connect the PWM of the VNH3SP30 Driver to the _Digital Pin 5_ wire of the Arduino UNO.

  * 3.g : Connect the SDA of the lcdScreen to the _Analog input 4_ wire of the Arduino UNO.

  * 3.h : Connect the SCL of the lcdScreen to the _Analog input 5_ wire of the Arduino UNO.

  * 3.i : Connect the DQ of the DS18B20 to the _Digital Pin 9_ wire of the Arduino UNO.

  * 3.j : __Connect all the Ground pins of the lcdScreen and the DS18B20, and from the VNH3SP30__

  * 3.k : Connect all the 5v rails of the lcdScreen, the __DS18B20 with the 4,7K in parallel with DQ and VDD__ and the VNH3SP30, as shown in the schematic.

  * 3.l : Plug in the arduino uno and proceed to upload the sketch as showed below.

<br>

### 4. Last checks before powering up/using for the first time:
  __DO NOT POWER WITH 12v the peltier module without Heatsink !! it may burn you or cause damage to the driver.__
