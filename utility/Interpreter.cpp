#include <Interpreter.h>
#include <Arduino.h>

Interpreter::Interpreter(ParkingShield &shield) : shield(shield) {}

void Interpreter::interpreteAndExecuteCommand(char *command)
{
	  //TODO: check specification
	  const char *DEVICE_LED = "LED";
	  const int DEVICE_NUMBER_LED1 = 1;
	  const int DEVICE_NUMBER_LED2 = 2;
	  const int DEVICE_NUMBER_LED3 = 3;
	  const char *ACTION_LED_ON = "ON";
	  const char *ACTION_LED_OFF = "OFF";
	  const char *DEVICE_BUZZER = "BUZZER";
	  const int DEVICE_NUMBER_BUZZER = 0;
	  const char *ACTION_BUZZER_BUZZ = "BUZZ";
	  const char *DEVICE_SEGMENT = "SEGMENT";
	  const int DEVICE_NUMBER_SEGMENT = 0;
	  const char *ACTION_SEGMENT_COUNTDOWN = "COUNTDOWN";


	  String cmd = String(command);
	  int index = cmd.indexOf('_');
	  String device = cmd.substring(0,index);
	  int secondIndex = cmd.indexOf('_', index+1);
	  int deviceNumber = cmd.substring(index+1, secondIndex).toInt();
	  String action = cmd.substring(secondIndex+1);

	if( device.equals(DEVICE_LED) )
	{
		if( deviceNumber == DEVICE_NUMBER_LED1 )
		{
			if( action.equals(ACTION_LED_OFF) )
				shield.setLed(ParkingShield::RED_LED, true);
			else if(action.equals(ACTION_LED_ON) )
				shield.setLed(ParkingShield::RED_LED, false);
		}
		else if( deviceNumber == DEVICE_NUMBER_LED2 )
		{
			if( action.equals(ACTION_LED_OFF) )
				shield.setLed(ParkingShield::YELLOW_LED, true);
			else if(action.equals(ACTION_LED_ON) )
				shield.setLed(ParkingShield::YELLOW_LED, false);
		}
		else if( deviceNumber == DEVICE_NUMBER_LED3 )
		{
			if( action.equals(ACTION_LED_OFF) )
				shield.setLed(ParkingShield::GREEN_LED, true);
			else if(action.equals(ACTION_LED_ON) )
				shield.setLed(ParkingShield::GREEN_LED, false);
		}
	}
	else if( device.equals(DEVICE_BUZZER) )
	{
		if( deviceNumber == DEVICE_NUMBER_BUZZER )
		{
			if( action.equals(ACTION_BUZZER_BUZZ) )
			{
			}
		}
	}
	else if( device.equals(DEVICE_SEGMENT) )
	{
		if( deviceNumber == DEVICE_NUMBER_SEGMENT )
		{
			if( action.equals(ACTION_SEGMENT_COUNTDOWN) )
			{
				//TODO: not implemented
			}
		}
	}
}
