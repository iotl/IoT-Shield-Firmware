#include <Scheduler.h>
#include <DeviceArduino.h>


//----------------------------------------------------------------------------------------------------
// Helper
//----------------------------------------------------------------------------------------------------

/**
* @brief The TaskHelper class provides an interface that makes it possible
* @brief to only add function pointers to the scheduler (otherwise we would
* @brief need to inherit from the task object everytime, even if we only want
* @brief to task a simple function). Only the scheduler will use this class internally.
*/
class TaskHelper : public Task
{
	public:
		TaskHelper(func_ptr func) : _func(func) { setTasktype(TASKHELPER); }

		virtual void update(Scheduler & scheduler) const { _func(); }

	private:
		func_ptr const _func;
};

class TaskHelperScheduler : public Task
{
	public:
		TaskHelperScheduler(func_ptr_scheduler func) : _func(func) {}

		virtual void update(Scheduler & scheduler) const { _func(scheduler); }

	private:
		func_ptr_scheduler const _func;
};

class TaskHelperData : public Task
{
	public:
		TaskHelperData(func_ptr_data func, void * data) : _func(func), _data(data) {}

		virtual void update(Scheduler & scheduler) const { _func(_data); }

	private:
		func_ptr_data const _func;
		void * const _data;
};

class TaskHelperSchedulerData : public Task
{
	public:
		TaskHelperSchedulerData(func_ptr_scheduler_data func, void * data) : _func(func), _data(data) {}

		virtual void update(Scheduler & scheduler) const { _func(scheduler, _data); }

	private:
		func_ptr_scheduler_data const _func;
		void * const _data;
};

bool isTaskHelper(Task & task)
{
	if (task.tasktype() == Task::TASKHELPER)
		return true;

	return false;
}


//----------------------------------------------------------------------------------------------------
// Public
//----------------------------------------------------------------------------------------------------

Scheduler::Scheduler(void)
{
	for (unsigned char i = 0; i < MAX_TASKS; i++)
		setTask(i, 0, 0, 0, false);
}

bool Scheduler::addTask(Task * task, unsigned long int timer, bool reshot)
{
	// Search for a free slot to add the function.
	for (unsigned char i = 0; i < MAX_TASKS; i++)
  {
    if (tasks[i].task == 0)
    {
      setTask(i, task, timer, Device::milliseconds(), reshot);
      return true;
    }
  }
	return false;
}

bool Scheduler::taskExists(Task * task)
{
  for (unsigned char i = 0; i < MAX_TASKS; i++)
  {
    if (tasks[i].task == task)
      return true;
  }
  return false;
}

void Scheduler::removeTask(Task * task)
{
	for (unsigned char i = 0; i < MAX_TASKS; i++)
  {
		if (tasks[i].task == task)
		{
			removeTask(i);
			break;
		}
  }
}

void Scheduler::scheduleTasks(void)
{
	// Loop through all pending tasks.
	for (unsigned char i = 0; i < MAX_TASKS; i++)
	{
		// If we have a task in this slot ...
		if (tasks[i].task != 0)
		{
			if (Device::milliseconds() - tasks[i].timestamp >= tasks[i].timer)
			{
				// Execute it.
				tasks[i].task->update(*this);
				// If this is a periodically task, reset its timer.
				if (tasks[i].reshot)
          			tasks[i].timestamp = Device::milliseconds();
				// Else delete the task.
				else
				  	removeTask(i);
			}
		}
	}
}


//----------------------------------------------------------------------------------------------------
// Private
//----------------------------------------------------------------------------------------------------

void Scheduler::setTask(unsigned char index, Task * task, unsigned long int timer, unsigned long int timestamp, bool reshot)
{
	if (index >= 0 && index < MAX_TASKS)
	{
		tasks[index].task = task;
		tasks[index].timer = timer;
		tasks[index].timestamp = timestamp;
		tasks[index].reshot = reshot;
	}
}

void Scheduler::removeTask(unsigned long int index)
{
	setTask(index, 0, 0, 0, false);
}
