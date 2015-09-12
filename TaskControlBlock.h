#ifndef	TASKCONTROLBLOCK_H
#define TASKCONTROLBLOCK_H

#include <Task.h>

/**
 * @brief The Task struct holds all necessary information for a tast to schedule, the task pointer, the timer
 * @brief and the information whether it is a single shot or not.
 */
class TaskControlBlock
{
	public:
		TaskControlBlock(void);
		~TaskControlBlock();

		bool set(Task * task_, unsigned long timer_, bool reshot_, bool isTaskHelper_, bool isTaskHelperWithData_);
		void run(void);
		bool isTaskHelper(void) const;
		bool isTaskHelperWithData(void) const;
		void reset(void);
		void remove(void);
		bool compare(Task * task_) const;
		bool compare(void (* func_)(void)) const;
		bool compare(void (* func_)(void *)) const;
		Task const * task(void) const;
		unsigned long timer(void) const;
		unsigned long timestamp(void) const;
		bool isFree(void) const;
		bool isUsed(void) const;
		bool reshot(void) const;
		bool ready(void) const;

	private:
		Task * task(void);
		void setTask(Task * task_);
		void setTimer(unsigned long timer_);
		void setTimestamp(unsigned long timestamp_);
		void setActualTimestamp(void);
		void setReshot(bool reshot_);
		void setIsTaskHelper(bool isTaskHelper_);
		void setIsTaskHelperWithData(bool isTaskHelperWithData_);
		void setIsFree(bool isFreeValue_);

		// Will be executed after timer milliseconds. NULL indicates this slot is free.
		Task * _task;
		// Time in milliseconds after task will be called.
		unsigned long _timer;
		// Time when task was added. Needed for calculation.
		unsigned long _timestamp;
		// If true, task will be executed after every timer milliseconds, otherwise it will be deleted after one call.
		bool _reshot;
		// If true, the task was instanciated by the scheduler, cause the was added only as function pointer.
		bool _isTaskHelper;
		// The same as _isTaskHelper, but this one has data to forward to it's function pointer.
		bool _isTaskHelperWithData;
		// If true, there is no task in this control block.
		bool _isFree;
};

#endif // TASKCONTROLBLOCK_H