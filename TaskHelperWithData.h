#ifndef TASKHELPERWITHDATA_H
#define TASKHELPERWITHDATA_H

#include <TaskHelper.h>

// Make use of function pointers comfortable.
typedef void (*func_ptr)(void);
typedef void (*func_ptr_with_data)(void *);

/**
 * The TaskHelperWithData class is a subclass of TaskHelper that has data to forward to its function pointer.
 * Therefore the function pointer is of different type as in TaskHelper.
 * @author Marc Vester (XaserLE)
 */
class TaskHelperWithData : public TaskHelper
{
	public:
		/**
		 * @brief Constructor.
		 * @param func A function pointer that is be called whenever update() is called.
		 */
		TaskHelperWithData(func_ptr_with_data func, void * data) : _func(func), _data(data) {}

		/**
		 * @brief Overrides the pure virtual function of the base class.
		 * @brief Is called by the scheduler.
		 */
		virtual void update(void) { _func(_data); }

		/**
		 * @brief Compares the function pointer of this task with the given one.
		 * @param func The pointer to compare with the tasks one.
		 * @return True if pointers are equal, false otherwise.
		 */
		virtual bool funcEquals(func_ptr_with_data func) const { return func == _func; }

	private:
		func_ptr_with_data const _func;
		void * const _data;
};

#endif // TASKHELPER_H
