#ifndef TASK_H
  #define TASK_H

/**
 * @brief The Task class provides a base class (pure virtual) to inherit and implement an user defined function
 * @brief the scheduler can call.
 * @author Marc Vester (XaserLE)
 */
class Task
{
  public:
    /**
     * @brief Destructor.
     */
    virtual ~Task() {}
    
    /**
     * @brief The update function is called by the scheduler.
     */
    virtual void update(void) = 0;
};

#endif // TASK_H
