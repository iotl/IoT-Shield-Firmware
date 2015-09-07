#include <Scheduler.h>
#include <Arduino.h>

Scheduler::Task Scheduler::tasks[MAX_TASKS];

void Scheduler::init(void)
{
	for (unsigned char i = 0; i < MAX_TASKS; i++)
		setTask(i, NULL, 0, 0, false);
}

bool Scheduler::addTask(void (*func)(void), unsigned long int timer, bool reshot)
{
	// Search for a free slot to add the function.
	for (unsigned char i = 0; i < MAX_TASKS; i++)
    {
		if (tasks[i].func == NULL)
		{
      		setTask(i, func, timer, millis(), reshot);
			return true;
		}
    }
	return false;
}

bool Scheduler::taskExists(void (*func)(void))
{
        for (unsigned char i = 0; i < MAX_TASKS; i++)
        {
			if (tasks[i].func == func)
                return true;
        }
        return false;
}

void Scheduler::removeTask(void (*func)(void))
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
		if (tasks[i].func != NULL)
		{
			if (millis() - tasks[i].timestamp >= tasks[i].timer)
			{
				// Execute it.
				tasks[i].func();
				// If this is a periodically task, reset its timer.
				if (tasks[i].reshot)
          			tasks[i].timestamp = millis();
				// Else delete the task.
				else
				  removeTask(i);
			}
		}
	}
}

void Scheduler::setTask(unsigned char index, void (*func)(void), unsigned long int timer, unsigned long int timestamp, bool reshot)
{
	if (index >= 0 && index < MAX_TASKS)
	{
		tasks[index].func = func;
		tasks[index].timer = timer;
		tasks[index].timestamp = timestamp;
		tasks[index].reshot = reshot;
	}
}

void Scheduler::removeTask(unsigned long int index)
{
	setTask(index, NULL, 0, 0, false);
}

