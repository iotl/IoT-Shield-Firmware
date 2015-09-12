#include <Scheduler.h>
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

bool Scheduler::taskExists(Task * task) const
{
  if (indexOf(task) >= 0)
  	return true;

  return false;
}

bool Scheduler::taskExists(void (* func)(void)) const
{
  if (indexOf(func) >= 0)
  	return true;

  return false;
}

bool Scheduler::taskExists(void (* func)(void *)) const
{
  if (indexOf(func) >= 0)
  	return true;

  return false;
}

void Scheduler::removeTask(Task * task)
{
  char index = indexOf(task);

  if (index >= 0)
    removeTask(index);
}

void Scheduler::removeTask(void (* func)(void))
{
  char index = indexOf(func);

  if (index >= 0)
  	removeTask(index);
}

void Scheduler::removeTask(void (* func)(void *))
{
  char index = indexOf(func);

  if (index >= 0)
  	removeTask(index);
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

void Scheduler::removeTask(unsigned long index)
{
	tasks[index].remove();
}

char Scheduler::indexOf(Task * task) const
{
  for (unsigned char i = 0; i < MAX_TASKS; i++)
  {
    if (tasks[i].compare(task))
      return i;
  }

  return -1;
}

char Scheduler::indexOf(void (* func)(void)) const
{
  for (unsigned char i = 0; i < MAX_TASKS; i++)
  {
    if (tasks[i].compare(func))
      return i;
  }

  return -1;
}

char Scheduler::indexOf(void (* func)(void *)) const
{
  for (unsigned char i = 0; i < MAX_TASKS; i++)
  {
    if (tasks[i].compare(func))
      return i;
  }

  return -1;
}
