#include <Scheduler.h>
#include <DeviceArduino.h>

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
				tasks[i].task->update(this);
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
