#ifndef TESTTASK_H
  #define TESTTASK_H

#include <Task.h>
#include <Arduino.h>

class TestTask : public Task
{
  public:
    TestTask(void) {}
    virtual ~TestTask() {}

    virtual void update(void) { Serial.println("TestTask executed."); }
};

#endif TESTTASK_H
