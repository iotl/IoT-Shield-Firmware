#ifdef SCHEDULER_H

//----------------------------------------------------------------------------------------------------
// Public
//----------------------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------------
// Private
//----------------------------------------------------------------------------------------------------

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
