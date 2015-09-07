#Commands

The ParkingShield supports a simple ASCII-based command interface. Commands can control the output or trigger the read of an input

##General Form
The general form of the command is the following:

	Format	 	:= <Endpoint>_<#>_<Command>
	<Endpoint>	:= LED | 7SEG | BUZZER | TEMP | LIGHT
	<#>			:= [1..9]
	<Command>	:= ON | OFF | [0..9] | DOWN | UP | TONE | MELODY | REPORT | MONITOR

**Examples:**

	1. LED_1_ON
	2. LED_1_OFF
	3. 7SEG_1_SHOW1
	4. 7SEG_1_COUNTDOWN

## Supported Commands
### LED
Command to enable or disable a LED. 

_Prefix:_

	LED_[1..3]_<Command>
	
_Commands:_

	Command	| Description
	:---------| :-------
	ON 			| Enables the LED.
	OFF			| Disables the LED.

_Examples:_

	LED_1_ON  
	
### 7SEG
Command to show a number on the 7-segment display or to count up/down

_Prefix:_

	7Seg_1_<Command>
	
_Commands:_

	Command	| Description
	:---------| :-------
	0..9		| Displays the given digit.
	DOWN		| Counts down from the preset digit to 0 with 3 seconds interval.
	UP   		| Counts up from the preset digit to 9 with 3 seconds interval.

_Examples:_

	7SEG_1_5
	7SEG_1_COUNTDOWN 
	
### BUZZER
Command to play a melody or tone with the buzzer.

_Prefix:_

	BUZZER_1_<Command>
	
_Commands:_

	Command	| Description
	:---------| :-------
	MELODY		| Plays a melody.
	TONE		| Plays a single tone for 1 sec.

_Examples:_

	BUZZER_1_TONE
	BUZZER_1_MELODY
	
### TEMP
Reads out the temperature and sends the value to the configured ThingSpeak channel.

_Prefix:_

	TEMP_1_<Command>
	
_Commands:_

	Command	| Description
	:---------| :-------
	REPORT		| Reports the current temperature in °C
	MONITOR	| Continously reports the temperature every 15 seconds.

_Examples:_

	TEMP_1_REPORT
	TEMP_1_MONITOR
	
	
### LIGHT

Reads out the ambient light sensor and sends the value to the configured ThingSpeak channel.

_Prefix:_

	LIGHT_1_<Command>
	
_Commands:_

	Command	| Description
	:---------| :-------
	REPORT		| Reports the current light intesity between 0 and 1024.
	MONITOR	| Continously reports the temperature every 15 seconds.

_Examples:_

	TEMP_1_REPORT
	TEMP_1_MONITOR
	
