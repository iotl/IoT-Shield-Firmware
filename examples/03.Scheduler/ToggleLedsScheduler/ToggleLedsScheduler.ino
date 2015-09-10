#include <ParkingShield.h>
#include <Scheduler.h>

class LedFlash : public Task
{
  public:
  LedFlash(ParkingShield::led_t led, ParkingShield &shield) : _led(led), _shield(shield)
  {}
  
  void update(Scheduler &sched)
  {
    _shield.setLed(_led, _enable);
    _enable = !_enable;
  }

  private:
    ParkingShield::led_t _led;
    ParkingShield &_shield;
    bool _enable;
};


ParkingShield shield;
Scheduler sched;
LedFlash redFlash(ParkingShield::RED_LED, shield);
LedFlash yellowFlash(ParkingShield::YELLOW_LED, shield);

void setup() 
{
  sched.addTask(&redFlash, 1000, true);
  sched.addTask(&yellowFlash, 500, true);    
}

void loop()
{
  sched.scheduleTasks();  
}
