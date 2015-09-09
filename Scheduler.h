#ifndef SCHEDULER_H
	#define SCHEDULER_H

#include <Task.h>

/**
 * @brief The Scheduler class provides basic scheduling capabilities. Simply add task objects to it with a timer and it
 * @brief will call its update-function after timer is zero. It is also possible to periodically call this function.
 * @param MAX_TASKS Maximum number of tasks, cause we hardcode this for simplicity.
 * @author Marc Vester (XaserLE)
 * @author Jörn Hoffmann (jhoffmann)
 */
class Scheduler
{
	public:
		/**
		 * @brief Constructor, initializes the scheduler by initializing all tasks.
		 * @param maxTasks Maximum number of tasks the scheduler can handle.
		 */
		Scheduler();
		
		/**
		 * @brief Adds a task to the scheduler.
		 * @param task Pointer to the task object that should be executed.
		 * @param timer task will be executed after timer milliseconds.
		 * @param data The data the function will be called with.
		 * @param reshot If true, func will be executed over and over every timer milliseconds.
		 * @return True if task was added, false if not (cause there was no space for another task).
		 */
		bool addTask(Task * task, unsigned long timer, bool reshot = true);

    /** @brief Tells us if a task was already added to the scheduler.
     *  @param task Pointer to the task object that should be executed.
     *  @return True if task (func) is already in the scheduling list, false otherwise.
     */
    bool taskExists(Task * task);
		
		/**
		 * @brief Adds a task to the scheduler.
		 * @param task Pointer to the task object that should be executed.
		 */
		void removeTask(Task * task);
		
		/**
		 * @brief This is the main function to schedule all tasks. Should be called every frame in the main loop.
		 */
		void scheduleTasks(void);
		
	private:
    /**
     * @brief Internal function that sets a task with the given parameters.
     * @param index Index for the tasks array. Valid values: [0 : MAX_TASKS-1].
     * @param task Pointer to the task object that should be executed.
     * @param timer Time in milliseconds after task will be executed.
     * @param timestamp Reference value for calculation for the execution time, should be the actually timestampt normally.
     * @param reshot If true, function will be called after every timer milliseconds, otherwise it will be deleted after one call.
     */
    inline void setTask(unsigned char index, Task * task, unsigned long int timer, unsigned long int timestamp, bool reshot);

    /**
     * @brief Internal function that removes a task given by an index (faster than searching for the function pointer).
     * @param index The index for the task. Valid values: [0 : MAX_TASKS-1].
     */
    inline void removeTask(unsigned long int index);
  
		/**
		 * @brief The Task struct holds all necessary information for a tast to schedule, the task pointer, the timer
		 * @brief and the information whether it is a single shot or not.
		 */
		struct TCB
		{
			// Will be executed after timer milliseconds. NULL indicates this slot is free.
			Task * task;
			// Time in milliseconds after task will be called.
			unsigned long int timer;
			// Time when task was added. Needed for calculation.
			unsigned long int timestamp;
			// If true, task will be executed after every timer milliseconds, otherwise it will be deleted after one call.
			bool reshot;
		};
		
		// Maximum number of tasks.
		static unsigned char const MAX_TASKS = 20;
		// Array with the tasks to schedule.
		TCB tasks[MAX_TASKS];
};

#endif //SCHEDULER_H
