#ifdef SCHEDULER_H

#include <TaskHelper.h>
#include <TaskHelperWithData.h>
#include <new.h>

//----------------------------------------------------------------------------------------------------
// Public
//----------------------------------------------------------------------------------------------------

bool Scheduler::addTask(Task * task, unsigned long int timer, bool reshot)
{
	return addTask(task, timer, reshot, false, false);
}

bool Scheduler::addTask(void (* func)(void), unsigned long timer, bool reshot)
{
	Task * task = new TaskHelper(func);
	return addTask(task, timer, reshot, true, false);
}

bool Scheduler::addTask(void (* func)(void *), void * data, unsigned long timer, bool reshot)
{
	Task * task = new TaskHelperWithData(func, data);
	return addTask(task, timer, reshot, true, true);
}

template<typename T>
bool Scheduler::taskExists(T task) const
{
  if (indexOf(task) >= 0)
    return true;

  return false;
}

template<typename T>
void Scheduler::removeTask(T task)
{
  char index = indexOf(task);

  if (index >= 0)
    removeTaskPerIndex(index);
}

void Scheduler::scheduleTasks(void)
{
	for (unsigned char i = 0; i < MAX_TASKS; i++)
	{
		if (tasks[i].isUsed())
		{
			if (tasks[i].ready())
				tasks[i].run();
		}
	}
}


//----------------------------------------------------------------------------------------------------
// Private
//----------------------------------------------------------------------------------------------------

bool Scheduler::addTask(Task * task, unsigned long timer, bool reshot, bool isTaskHelper, bool isTaskHelperWithData)
{
  for (unsigned char i = 0; i < MAX_TASKS; i++)
  {
    if (tasks[i].isFree())
      return tasks[i].set(task, timer, reshot, isTaskHelper, isTaskHelperWithData);
  }

  return false;
}

void Scheduler::removeTaskPerIndex(unsigned long index)
{
	tasks[index].remove();
}

template<typename T>
char Scheduler::indexOf(T task) const
{
  for (unsigned char i = 0; i < MAX_TASKS; i++)
  {
    if (tasks[i].compare(task))
      return i;
  }

  return -1;
}

#endif // SCHEDULER_H
