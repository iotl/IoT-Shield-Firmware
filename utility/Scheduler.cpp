#include <Scheduler.h>
#include <DeviceArduino.h>

Scheduler::Scheduler(void)
{
	for (unsigned char i = 0; i < MAX_TASKS; i++)
		setTask(i, 0, 0, 0, 0, false);
}

bool Scheduler::addTask(void (*func)(void *), unsigned long int timer, void * data, bool reshot)
{
	// Search for a free slot to add the function.
	for (unsigned char i = 0; i < MAX_TASKS; i++)
    {
		if (tasks[i].func == 0)
		{
      		setTask(i, func, timer, Device::milliseconds(), data, reshot);
			return true;
		}
    }
	return false;
}

bool Scheduler::taskExists(void (*func)(void *))
{
        for (unsigned char i = 0; i < MAX_TASKS; i++)
        {
			if (tasks[i].func == func)
                return true;
        }
        return false;
}

void Scheduler::removeTask(void (*func)(void *))
{
	for (unsigned char i = 0; i < MAX_TASKS; i++)
    {
		if (tasks[i].func == func)
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
		if (tasks[i].func != 0)
		{
			if (Device::milliseconds() - tasks[i].timestamp >= tasks[i].timer)
			{
				// Execute it.
				tasks[i].func(tasks[i].data);
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

void Scheduler::setTask(unsigned char index, void (*func)(void *), unsigned long int timer, unsigned long int timestamp, void * data, bool reshot)
{
	if (index >= 0 && index < MAX_TASKS)
	{
		tasks[index].func = func;
		tasks[index].timer = timer;
		tasks[index].data = data;
		tasks[index].timestamp = timestamp;
		tasks[index].reshot = reshot;
	}
}

void Scheduler::removeTask(unsigned long int index)
{
	setTask(index, 0, 0, 0, 0, false);
}
