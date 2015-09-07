#ifndef SCHEDULER_H
	#define SCHEDULER_H


/**
 * @brief The Scheduler class provides basic scheduling capabilities. Simply add functions to it with a timer and it
 * @brief will call this function after timer is zero. It is also possible to periodically call a function.
 * @author Marc Vester (XaserLE)
 */
class Scheduler
{
	public:
		/**
		 * @brief Initializes the scheduler by initializing all tasks. This function needs to be called once before all other functions.
		 * @brief Not calling this function at first will result in undefined behaviour.
		 */
		static void init(void);
		
		/**
		 * @brief Adds a task to the scheduler.
		 * @param func Pointer to the function that should be executed.
		 * @param timer func will be executed after timer milliseconds.
		 * @param reshot If true, func will be executed over and over every timer milliseconds.
		 * @return True if task was added, false if not (cause there was no space for another task).
		 */
		static bool addTask(void (*func)(void), unsigned long int timer, bool reshot = true);

        /** @brief Tells us if a task was already added to the scheduler.
        *  @param fung Pointer to the function that identifies the task.
        *  @return True if task (func) is already in the scheduling list, false otherwise.
        */
        static bool taskExists(void (*func)(void));
		
		/**
		 * @brief Adds a task to the scheduler.
		 * @param func Pointer to the function that is associated with the task.
		 */
		static void removeTask(void (*func)(void));
		
		/**
		 * @brief This is the main function to schedule all tasks. Should be called every frame in the main loop.
		 */
		static void scheduleTasks(void);
		
	private:
	    /**
	     * @brief Internal function that sets a task with the given parameters.
	     * @param index Index for the tasks array. Valid values: [0 : MAX_TASKS-1].
	     * @param func Pointer to the function to execute.
	     * @param timer Time in milliseconds after func will be executed.
	     * @param timestamp Reference value for calculation for the execution time, should be the actually timestampt normally.
	     * @param reshot If true, function will be called after every timer milliseconds, otherwise it will be deleted after one call.
	     */
	    static inline void setTask(unsigned char index, void (*func)(void), unsigned long int timer, unsigned long int timestamp, bool reshot);

	    /**
	     * @brief Internal function that removes a task given by an index (faster than searching for the function pointer).
	     * @param index The index for the task. Valid values: [0 : MAX_TASKS-1].
	     */
	    static inline void removeTask(unsigned long int index);
  
		/**
		 * @brief The Task struct holds all necessary information for a function to schedule, the function pointer, the timer
		 * @brief and the information whether it is a single shot or not.
		 */
		struct Task
		{
			// Will be executed after timer milliseconds. NULL indicates this slot is free.
			void (*func)(void);
			// Time in milliseconds after func will be called.
			unsigned long int timer;
			// Time when task was added. Needed for calculation.
			unsigned long int timestamp;
			// If true, function will be called after every timer milliseconds, otherwise it will be deleted after one call.
			bool reshot;
		};
		
		// Maximum number of tasks, cause we hardcode this for simplicity.
		static unsigned char const MAX_TASKS = 20;
		// Array with the tasks to schedule.
		static Task tasks[MAX_TASKS];
};

#endif //SCHEDULER_H
