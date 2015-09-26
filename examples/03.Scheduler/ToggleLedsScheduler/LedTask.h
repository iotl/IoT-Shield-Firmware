#include <Task.h>
#include <ParkingShield.h>

class LedTask : public Task
{
  public:
  LedTask(ParkingShield::led_t led, ParkingShield &shield) : _led(led), _shield(shield)
  {}

  void update(void)
  {
    _shield.setLed(_led, _enable);
    _enable = !_enable;
  }

  private:
    ParkingShield::led_t _led;
    ParkingShield &_shield;
    bool _enable;
};
