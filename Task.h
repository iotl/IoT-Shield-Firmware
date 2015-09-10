#ifndef TASK_H
  #define TASK_H

/// Forward declaration cause the Scheduler uses Task objects, but Task objects will call their function with a Scheduler instance.
class Scheduler;  

/**
 * @brief The Task class provides a base class (pure virtual) to inherit and implement an user defined function
 * @brief the scheduler can call.
 */
class Task
{
  public:
    typedef enum
    {
        TASK,
        TASKHELPER
    } task_t;

    Task(void) : _tasktype(TASK) {}
    /**
     * @brief Destructor.
     */
    virtual ~Task() {}
    
    /**
     * @brief The update function is called by the scheduler.
     * @param The scheduler that called this function (cause maybe we want to unregister ourself).
     */
    virtual void update(Scheduler & scheduler) = 0;

    task_t tasktype(void) const { return _tasktype; }

    protected:
        void setTasktype(task_t newTasktype) { _tasktype = newTasktype; }

    private:
        task_t _tasktype;
};

#endif TASK_H
