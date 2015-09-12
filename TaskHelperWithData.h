#ifndef TASKHELPERWITHDATA_H
#define TASKHELPERWITHDATA_H

#include <TaskHelper.h>

// Make use of function pointers comfortable.
typedef void (*func_ptr)(void);
typedef void (*func_ptr_with_data)(void *);

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
		 * @brief Access to the function pointer of this task.
		 * @return A pointer to the function of this task.
		 */
		//virtual func_ptr_with_data func(void) const { return _func; }
		virtual bool funcEquals(func_ptr_with_data func) const { return func == _func; }

	private:
		func_ptr_with_data const _func;
		void * const _data;
};

#endif // TASKHELPER_H
