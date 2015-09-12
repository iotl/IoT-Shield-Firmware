#ifndef SCHEDULER_H
	#define SCHEDULER_H

#include <Task.h>
#include <TaskControlBlock.h>

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
		 * @brief Adds a task to the scheduler.
		 * @param task Pointer to the task object that should be executed.
		 * @param timer task will be executed after timer milliseconds.
		 * @param data The data the function will be called with.
		 * @param reshot If true, func will be executed over and over every timer milliseconds.
		 * @return True if task was added, false if not (cause there was no space for another task).
		 */
		bool addTask(Task * task, unsigned long timer, bool reshot = true);

		bool addTask(void (* func)(void), unsigned long timer, bool reshot = true);
		bool addTask(void (* func)(void *), void * data, unsigned long timer, bool reshot = true);

    /** @brief Tells us if a task was already added to the scheduler.
     *  @param task Pointer to the task object that should be executed.
     *  @return True if task (func) is already in the scheduling list, false otherwise.
     */
    bool taskExists(Task * task) const;

    bool taskExists(void (* func)(void)) const;
    bool taskExists(void (* func)(void *)) const;
		
		/**
		 * @brief Adds a task to the scheduler.
		 * @param task Pointer to the task object that should be executed.
		 */
		void removeTask(Task * task);

		void removeTask(void (* func)(void));
		void removeTask(void (* func)(void *));
		
		/**
		 * @brief This is the main function to schedule all tasks. Should be called every frame in the main loop.
		 */
		void scheduleTasks(void);
		
	private:
    bool addTask(Task * task, unsigned long timer, bool reshot, bool isTaskHelper, bool taskHelperHasData);

    /**
     * @brief Internal function that removes a task given by an index (faster than searching for the function pointer).
     * @param index The index for the task. Valid values: [0 : MAX_TASKS-1].
     */
    inline void removeTask(unsigned long int index);

    char indexOf(Task * task) const;
    char indexOf(void (* func)(void)) const;
    char indexOf(void (* func)(void *)) const;

	// Maximum number of tasks.
	static char const MAX_TASKS = 20;
	// Array with the tasks to schedule.
	TaskControlBlock tasks[MAX_TASKS];
};

#endif //SCHEDULER_H
