
# Open Source Thermostatic Water Bath 
<a href="https://github.com/FOSH-following-demand/thermostatic-wather-bath" title="Thermostatic wather Bath"><img src="https://img.shields.io/badge/Version-0.0.2-yellow"></a>
<a href="https://www.gnu.org/licenses/gpl-3.0.en.html" title="GNU V3 Licence"><img src="https://img.shields.io/badge/Licence-GNU%20V3-red.svg"></a>

### Welcome!
<a href="https://tecsci.com.ar/" title="Technology for Science"><img src="https://raw.githubusercontent.com/FOSH-following-demand/thermostatic-wather-bath/master/tecsciLogo.png"></a>

Thanks you for visiting this repository of this wonderful project!.

This document (The README file) is a hub to give you some guidance about all of what is happening here.

If you want to know more, please follow this quick links to jump to a specific section, or just scroll down to find out more!
  * [The problem involved](https://github.com/FOSH-following-demand/thermostatic-water-bath#the-problem)
  * [The solution we found](https://github.com/FOSH-following-demand/thermostatic-water-bath#the-solution)
  * [The idea behind the project](https://github.com/FOSH-following-demand/thermostatic-water-bath#the-idea)
  * [What we found interesting? ](https://github.com/FOSH-following-demand/thermostatic-water-bath#what-we-found)
  * [Find out more about](https://github.com/FOSH-following-demand/thermostatic-water-bath#get-involved)
  * [I don't understand something](https://github.com/FOSH-following-demand/thermostatic-water-bath#glossary)

## The problem:

In research and clinical laboratories, it is always useful to keep reagents or samples that are analyzed, at certain temperatures.
A _thermostatic bath_ is a device designed to maintain the temperature of the objects in contact with the fluid used.

In general, they are composed of electric heaters that heat the distilled water and, when they reach a certain temperature, they are automatically disconnected from the energy.


## The solution:

Our idea is to use efficiency and solidity as a basis, so we will use Peltier cells to take advantage of the Peltier effect, which is normally used as a thermoelectric coolant.

But, the advantage of using these cells, is that if we reverse the polarity, we could extract heat instead of generating it.

Therefore, we would have a thermostatic bath capable of generating heat or cold without modifying its design or changing any part.

The project will consist of a control circuit, the design of the same and the construction of the storage box.


### The idea

The microcontrollers based on the [ATMEGA328p](https://store.arduino.cc/usa/arduino-uno-rev3) will be used mainly for the first tests and the calibration of the sensors.

Once this is done (by the way, you can check the code [here](https://github.com/FOSH-following-demand/thermostatic-wather-bath/tree/master/software/MCU)), the objective will be to use a __"We Mos D1 Mini"__ [board](https://wiki.wemos.cc/products:d1:d1_mini) as the main controller and, as a complement, the ability to connect to [Cayenne web services](https://mydevices.com/) as a monitor and remote control through IoT technology.

The electric resistors if they do not have water are burned (if they do not have electronic protection circuits, as usual), with the design proposed in this project, we will try to avoid it by measuring the current that the cell consumes, so we can determine, without using another type of sensors, like a __DS18B20__ ([datasheet here](https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf)), if the container where the piece is located, has enough distilled water or refrigerant (in case you want to cool).

There is a lot of variety of Peltier cells, qualities and ways to get it (For example, Amazon, eBay or AliExpress), we have been guided by a Chinese manufacturer ([link here](https://peltiermodules.com/)) that poorly describes the characteristics of the product, but when we go to the tests, it performs correctly based on the datasheet.


## What we found

In our studies, we used a Peltier Cell [TEC-12705](https://peltiermodules.com/peltier.datasheet/TEC1-12705.pdf) to start, after many thorough tests, we realized that it would not be able to maintain and heat quickly the water.

therefore, after a week of continuous tests, we change to a _new cell_, in this case, the [TEC-12715](https://peltiermodules.com/peltier.datasheet/TEC1-12715.pdf), which may seem a little bigger than the 12705, but while the 12705 is __50W__, the 12715 is __150W__!

We had to get a more powerful 12v power supply, which are frequently used in DVR cameras, approximately 29A of peak current, to improve the power.

We have managed to stabilize the temperature adequately in the range of + - 0.1 ° C, which makes us proud for a prototype made practically of the study of the elements of peltier, of a limited knowledge and time for research! here are some [results](https://docs.google.com/spreadsheets/d/14x8ajXjDDJAvYHkvkYrGuCvhuu2BmfRY7JI32HTowtU/edit?usp=sharing).

[here](https://docs.google.com/spreadsheets/d/1heXNcq8TzLmtxA4aUKqf4gO-YtcK64AZdO5G_QmcZ0U/edit?usp=sharing) is the most complete example on the peltier usage.

<a href="Large Test" title="Sample image of the peltier element"><img src="https://raw.githubusercontent.com/FOSH-following-demand/thermostatic-wather-bath/master/largeTest.png"></a>

## Get involved

### Contribute
As we move forward, we will be contributing more and more things to the repository, if you like this project please contribute to it, after reading the [contributing](https://github.com/FOSH-following-demand/thermostatic-water-bath/blob/master/contributing.md) scheme.


### Development Plan

To follow the last changes made in the project, please follow this [link](https://github.com/FOSH-following-demand/thermostatic-water-bath/blob/master/dev_plan.md)


### Construction and Building

  To continue with the _Installation of Software_, please follow this [link](https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/software/MCU)

  To continue with the _Building of Electronics_, please follow this [link](https://github.com/FOSH-following-demand/thermostatic-water-bath/tree/master/documentation/building)

  To continue with the _Building of the Hardware_, please follow this another [link](https://github.com/FOSH-following-demand/thermostatic-water-bath/blob/master/hardware/BOM/BOM.md)

  To continue with the _Building of the frame_, please click [here](https://github.com/FOSH-following-demand/thermostatic-water-bath/blob/master/hardware/frame/frame.md#3d-design-files-are-here)

### Thank you

by [TECSCI](https://github.com/tecsci)

### Glossary

  * __README File__: a document that introduces an open project to the public and any potential contributors
  * __repository__ or __repo__:a collection of documents related to your project, in which you create and save new code or content
  * __Issue__: the GitHub term for tasks, enhancements, and bugs for your projects
