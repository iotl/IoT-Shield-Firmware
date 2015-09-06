#ifndef INTERPRETER_H
	#define INTERPRETER_H

#include <ParkingShield.h>

class Interpreter
{
	public:
		Interpreter(ParkingShield &shield);
		void interpreteAndExecuteCommand(char *command);

	private:
		ParkingShield &shield;
};

#endif // INTERPRETER_H
