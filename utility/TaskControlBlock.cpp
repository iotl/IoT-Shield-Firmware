#include <TaskControlBlock.h>
#include <TaskHelper.h>
#include <TaskHelperWithData.h>
#include <DeviceArduino.h>

//----------------------------------------------------------------------------------------------------
// Public
//----------------------------------------------------------------------------------------------------

TaskControlBlock::TaskControlBlock(void)
{
	reset();
}

bool TaskControlBlock::set(Task * task_, unsigned long timer_, bool reshot_, bool isTaskHelper_, bool isTaskHelperWithData_)
{
  if (isFree() && task_ != 0)
  {
    setTask(task_);
    setTimer(timer_);
    setActualTimestamp();
    setReshot(reshot_);
    setIsTaskHelper(isTaskHelper_);
    setIsTaskHelperWithData(isTaskHelperWithData_);
    setIsFree(false);
  }

  return isUsed();
}

TaskControlBlock::~TaskControlBlock()
{
	remove();
}

void TaskControlBlock::run(void)
{
  if (isUsed())
  {
    task()->update();

    // If this is a periodically task, reset its timer.
    if (reshot())
	  setActualTimestamp();
    // Else delete the task.
    else
  	  remove();
  }
}

bool TaskControlBlock::isTaskHelper(void) const
{
	return _isTaskHelper;
}

bool TaskControlBlock::isTaskHelperWithData(void) const
{
	return _isTaskHelperWithData;
}

bool TaskControlBlock::isFree(void) const
{
	return _isFree;
}

bool TaskControlBlock::isUsed(void) const
{
	return !isFree();
}

void TaskControlBlock::reset(void)
{
	setTask(0);
	setTimer(0);
	setTimestamp(0);
	setReshot(false);
	setIsTaskHelper(false);
	setIsTaskHelperWithData(false);
	setIsFree(true);
}

void TaskControlBlock::remove(void)
{
	if (isTaskHelper() || isTaskHelperWithData())
		delete task();
	reset();
}

bool TaskControlBlock::compare(Task * task_) const
{
	if (isUsed())
		return task_ == task();

	return false;
}

bool TaskControlBlock::compare(void (*func_)(void)) const
{
	if (isUsed() && isTaskHelper())
	{
		TaskHelper * helper =  static_cast<TaskHelper *>(const_cast<Task *>(task()));
		return helper->funcEquals(func_);
	}

	return false;
}

bool TaskControlBlock::compare(void (*func_)(void *)) const
{
	if (isUsed() && isTaskHelperWithData())
	{
		TaskHelperWithData * helper =  static_cast<TaskHelperWithData *>(const_cast<Task *>(task()));
		return helper->funcEquals(func_);
	}

	return false;
}

Task const * TaskControlBlock::task(void) const
{
	return _task;
}

unsigned long TaskControlBlock::timer(void) const
{
  return _timer;
}

unsigned long TaskControlBlock::timestamp(void) const
{
  return _timestamp;
}

bool TaskControlBlock::reshot(void) const
{
  return _reshot;
}

bool TaskControlBlock::ready(void) const
{
  return Device::milliseconds() - timestamp() >= timer();
}

//----------------------------------------------------------------------------------------------------
// Private
//----------------------------------------------------------------------------------------------------

Task * TaskControlBlock::task(void)
{
  return _task;
}

void TaskControlBlock::setTask(Task * task_)
{
  _task = task_;
}

void TaskControlBlock::setTimer(unsigned long timer_)
{
  _timer = timer_;
}

void TaskControlBlock::setReshot(bool reshot_)
{
  _reshot = reshot_;
}

void TaskControlBlock::setIsTaskHelper(bool isTaskHelper_)
{
  _isTaskHelper = isTaskHelper_;

  if (_isTaskHelper)
  	setIsTaskHelperWithData(false);
}

void TaskControlBlock::setIsTaskHelperWithData(bool isTaskHelperWithData_)
{
  _isTaskHelperWithData = isTaskHelperWithData_;

  if (_isTaskHelperWithData)
    setIsTaskHelper(false);
}

void TaskControlBlock::setTimestamp(unsigned long timestamp_)
{
  _timestamp = timestamp_;
}

void TaskControlBlock::setActualTimestamp(void)
{
  _timestamp = Device::milliseconds();
}

void TaskControlBlock::setIsFree(bool isFreeValue_)
{
  _isFree = isFreeValue_;
}
