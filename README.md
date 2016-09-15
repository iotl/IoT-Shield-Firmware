# IoT-Shield Firmware

Arduino library to support the IoT shield used in workshops and hardware courses at Leipzig University.

## Features

* Typesafe abstractions of LEDs, buttons, sensors etc.
* Powerful scheduler for executing tasks at specific times
* Support for playing tones and melodies using a buzzer
* Read temperature and (averaged) brightness values
* Seven segment library with support for (selected) characters

## Installation

Copy the complete repository folder into your Arduino library path (eg. `$HOME/Arduino/libraries/`).

## Example

```cpp
#include <ParkingShield.h>
#include <Scheduler.h>

class RedAlert : public Task {
    public:
        RedAlert(ParkingShield& shield) : shield(shield) {}
        void update() {
            shield.setLed(ParkingShield::RED_LED, enabled);
            enabled = !enabled;
        }

    private:
        ParkingShield& shield;
        bool enabled;
};

Scheduler scheduler;
ParkingShield shield;
RedAlert alert(shield);

void setup() {
    shield.setRepeatInterval(0); // no button cooldown phase

    // toggle red led every half sec and play march after 8 secs
    scheduler.addTask(&alert, 500, true);
    scheduler.addTask([] { shield.playMarch(); }, 8000);
}

void loop() {
    scheduler.scheduleTasks();

    // light up the green led iff button 1 is pressed
    shield.setLed(ParkingShield::GREEN_LED, shield.buttonS1Pressed());
}
```

The `examples` folder contains more exmaples and also some small projects (like the [SmartParkinglot]).

[SmartParkinglot]: examples/04.FSM/SmartParkinglot/
