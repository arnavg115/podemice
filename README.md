# Podemice

## Setup

1. Clone repository
2. Open Arduino ide and select `podemice.ino`
3. Click on Sketch > Include Libraries > Add .ZIP library
4. In the file explorer window select the `I2C.zip` file located in `./lib`

## Add a new module

1. Create a new cpp file. Ex: `Gyro.cpp`
2. Create a header file with the same name. `Gyro.h`
3. Add the following to the cpp file to allow you to use native arduino functions

```cpp
#include "Arduino.h"

// -> Your code goes here <--
```

4. To use your functions in the arduino sketch add a line to `podemice.ino`

```cpp
#include "Gyro.h"
```

See `Gyro.cpp`/`Gyro.h` to see this in action. This is an example for how a sensor can be added.
