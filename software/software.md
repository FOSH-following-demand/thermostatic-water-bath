Two libraries are currently being used, possibly 2 more would be missing, to improve the code.
one is called "Peltier" and the other is called "lcdScreen"
Both are designed to simplify the Arduino code and not make it so tedious to read and understand in order to modify it.

In effect, the libraries have given more work time since they needed a lot of testing and debugging,

With the PID control, most of the incidents have occurred, since although our setup was within the parameters taught in the code, their behavior was not very desirable and what was called an overshooting above the setpoint occurred, This led to a hunting and debouncing very frequently seen in these types of cells.

In addition to the challenge of using peltier cells for the thermostatic bath, we can say that the interest aroused by the use of them has generated more than one query in our group of nearby people.

Now we continue with the description of the libraries

# Available Commands:
- Peltier Library

```
void createPeltier(uint8_t A,uint8_t B,uint8_t E, uint8_t pwm);

void coolFast();

void heatFast();

bool cool(bool activate, uint8_t pwmValue);

bool heat(bool activate, uint8_t pwmValue);

bool powerOff(bool confirm);

```
You have two options, one is to use a Driver as we will suggest later, although the other most frequently used is to use a Relay connected to one of the pins (In this case it would be the "Enable" pin you have defined), while that with the other system using a driver, you will not only be able to cool and heat without moving any electrical connection, but you will also have the possibility of using a PID control in your setup for temperature control.

- LCD Screen Library
```
  bool initThis(char addr, int rows);
  
  bool turnOff();
  
  bool setActualTemp(float num);
  
  bool setCurrent(float amps);
  
  bool setEndTemp(float set);
```
This library facilitates the assembly of the user interface on the LCD screen (small GUI), it can be 16x02 or 20x4, both can be set in the library and thus automatically accommodate the parameters on the screen.

The connections and lcdScreen library will be put shortly
