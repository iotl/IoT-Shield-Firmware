#ifndef TASK_H
  #define TASK_H

class Scheduler;  

class Task
{
  public:
    Task(void) {}
    virtual ~Task() {}
    
    virtual void update(Scheduler * scheduler) = 0;
};

#endif TASK_H
