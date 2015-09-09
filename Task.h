#ifndef TASK_H
  #define TASK_H

class Scheduler;  

class Task
{
  public:
    virtual ~Task() {}
    
    virtual void update(Scheduler * scheduler) = 0;
};

#endif TASK_H
