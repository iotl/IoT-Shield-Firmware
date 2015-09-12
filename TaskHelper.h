#ifndef TASKHELPER_H
#define TASKHELPER_H

#include <Task.h>

// Make use of function pointers comfortable.
typedef void (*func_ptr)(void);

/**
 * @brief The TaskHelper class provides an interface that makes it possible
 * @brief to only add function pointers to the scheduler (otherwise we would
 * @brief need to inherit from the task object everytime, even if we only want
 * @brief to task a simple function). Only the scheduler will use this class internally.
 * @author Marc Vester (XaserLE)
 * @author Jörn Hoffmann (jhoffmann)
 */
class TaskHelper : public Task
{
	public:
		/**
		 * @brief Constructor.
		 * @param func A function pointer that is be called whenever update() is called.
		 */
		TaskHelper(func_ptr func) : _func(func) {}

		/**
		 * @brief Overrides the pure virtual function of the base class.
		 * @brief Is called by the scheduler.
		 */
		virtual void update(void) { _func(); }

		/**
		 * @brief Compares the function pointer of this task with the given one.
		 * @param func The pointer to compare with the tasks one.
		 * @return True if pointers are equal, false otherwise.
		 */
		virtual bool funcEquals(func_ptr func) const { return func == _func; }

	protected:
		/**
		 * @brief This Constructor is protected cause we need a default constructor in subclasses that sets this _func to 0.
		 */
		TaskHelper(void) : _func(0) {}

	private:
		func_ptr const _func;
};

#endif // TASKHELPER_H
