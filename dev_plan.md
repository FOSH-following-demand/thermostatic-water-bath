# Development plan

| Week        | Activities               | Who           |
| ----------- | ------------------------ | ------------- |
| 1           | Research and firsts tests|  @juanstdio   |
| 2           | first version 0.0.1      |  @juanstdio   |
| 3           | create libraries         |  @juanstdio   |
| 4           | make schematics & BOM    |  @juanstdio   |
| 5           | update BOM & PCB 0.0.2   |  @juanstdio   |
| 6           |                          |               |
| 7           |                          |               |
| 8           |                          |               |


### Week 1: Research and first tests

We research about the peltier elements, the basis of how they work, and we found papers about this in the __IEEE xplore__ titled _"A low-cost temperature controlled system to test and characterize sensors"_
[LINK](https://ieeexplore.ieee.org/abstract/document/1406715).
```
Abstract:
Almost all parameters (physical and chemical) used for in-situ water quality monitoring of rivers and seas, are measured using sensors that have characteristics highly sensitive to temperature.
The objective of this paper is to present the project, design and implementation of a low cost testing bath with automated temperature control for environmental monitoring sensors characterization.
Besides the description of the overall testing system, the paper details the cooling and heating thermoelectric pump based on Peltier modules implemented for the temperature control of the liquid, the tests that were conducted in order to obtain its optimal performance, the set of sensors and their signal conditioning to measure the temperature and the digital proportional-integral-derivative (PID) algorithm implemented in LabVIEW to control the temperature of the bath.
The developed testing apparatus proved to be an efficient tool to test and characterize sensors for in-situ water quality monitoring
```

Also at [Researchgate](www.researchgate.net/) we found another example of the using of the peltier elements,_"Peltier based cabinet cooling system using heat pipe and liquid based heat sink"_ [LINK](https://www.researchgate.net/publication/271459963_Peltier_based_cabinet_cooling_system_using_heat_pipe_and_liquid_based_heat_sink)
```
Abstract:
This paper describes a peltier based cabinet cooling system using heat pipe and liquid based heat sink.
Two peltier devices are used for increasing cooling effect.
Heat transfer effectiveness through peltier device is increased by using heat pipe based heat sink attached with fan and liquid based heat sink.
The hot side of both the peltier device is attached to same liquid based heat sink and cold side is attached to heat pipe based heat sink.
The coolant (water) inside the liquid based heat sink absorbs the heat from the hot side of both the peltier devices and then circulated through radiator.
The fins inside the radiator absorb heat from the liquid and give it back at lower temperature to the container. Again the cold liquid from container pumped into the liquid based heat sink and same cycle repeats. The heat pipe based heat sink dissipates cold air inside the cabinet through fins.
Heat pipe and liquid based cooling is the most efficient method of heat removal, they are often 4 -5 times more efficient compared to a normal aluminium heat sink.
A controller circuit is designed and implemented for controlling the set temperature inside the cabinet.
Based on the temperature data sensed by the LM-35 sensor, the controller controls the power supply to the peltier device.
Experiments are conducted at different set temperatures and performance of peltier based cabinet cooling system is tested.
```

### Week 2: First version 0.0.1
link [here](https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/software/MCU)

With all purchased components (drivers, peltier elements, cables, power supply, sensors and protoboards)
the first implementation of the code began, following a trial and error path, a code version was reached which "worked" but was not very neat for a final version, therefore it was quickly replaced by a new version, although we learned a lot with that first version.

Also, in the research of the papers, there was some new paper about peltier elements in Driving high brightness LED applied in specral measurements, also find in the [IEEE xplore ](https://ieeexplore.ieee.org/document/7428639)
```
Abstract:
A double closed-loop control system for driving high brightness LED to keep the temperature and emission intensity of LED stable is presented. In one closed-loop control, a Peltier is used to control LED's temperature and its average power can be dynamically regulated as LED temperature changes. In another, sampling real emission intensity of LED and comparing with expected intensity is repeatedly operated to make the real intensity follow the expected intensity. Design of LED driving system is demonstrated, and the thermostatic control effect and stability of LED spectrum are tested. The test results show that the error of LED temperature control is about 0.1°C corresponding to a center wavelength shift of 0.015 nm for a red LED and the emission intensity error for the same LED is within 0.1%.
```


### Week 3: Create libraries

The peltier library and lcdScreen library was created, written and debugged.
in the final conclusion, the lcd Screen does not work correctly, so today is not implemented.
example of using the peltier library are [found here](https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/software/MCU/0.0.3)


### Week 4: Make schematics & BOM

Schematics were made to understand it, they are made in [Fritzing](https://fritzing.org/home/), a software to design in a simple way, and export the gerber files to do the BOM using the kitspace addon.

After that, it was uploaded to the repository [here](https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/hardware).


### Week 5: update BOM & PCB 0.0.2

the new PCB have been corrected, because in the last revision there was a missing resistor in the DS18B20 sensor used for amplify the signal of DQ pin.
New [Schematic](https://github.com/FOSH-following-demand/thermostatic-water-bath/blob/master/hardware/electronics/DesignVer0.1_esquemático.png)

After that, the PCB was corrected in order to make the new resistor in an SMD package fit in there. Also, new headers of FTDI programmer kit were added
