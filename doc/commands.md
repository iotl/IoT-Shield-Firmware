#Commands

The ParkingShield supports a simple ASCII-based command interface. A command controls the set of an output or the read of an input. 

##General Form
The general form of the command resamples a REST-API and is defined as follow:

	Format	 	:= /<Endpoint>/<#>/<Command>
	<Endpoint>	:= led | 7seg | buzzer | temp | light
	<#>			:= [1..9]
	<Command>	:= [0..9] | down | up | tone | melody | on | off

**Examples:**

	1. /led/1/on
	2. /led/1/off
	3. /7seg/1/1
	4. /7seg/1/down

## Supported Commands
### LED
Command to enable or disable a LED. 

_Prefix:_

	/led/[1..3]/<Command>
	
_Commands:_

	Command	| Description
	:---------| :-------
	on   	| Enables the LED.
	off	| Disables the LED.

_Examples:_

	/led/1/on  
	
### 7SEG
Command to show a number on the 7-segment display or to count up/down

_Prefix:_

	/7seg/1/<Command>
	
_Commands:_

	Command	| Description
	:---------| :-------
			| Reports the set number.
	0..9	  	| Displays the given digit.
	down		| Counts down from the preset digit to 0 with 3 seconds interval.
	up   		| Counts up from the preset digit to 9 with 3 seconds interval.

_Examples:_

	/7seg/1/
	/7seg/1/5
	/7seg/1/down
	/7seg/1/up
	
	
### BUZZER
Command to play a melody or tone with the buzzer.

_Prefix:_

	/buzzer/1/<Command>
	
_Commands:_

	Command	| Description
	:---------| :-------
	tone		| Plays a single tone for 1 sec.
	melody		| Plays a melody.
	march		| Plays a longer march. 

_Examples:_

	/buzzer/1/tone
	/buzzer/1/melody
	/buzzer/1/march
	
### TEMP
Reads out the temperature and sends the value to the configured ThingSpeak channel.

_Prefix:_

	/temp/1/<Command>
	
_Commands:_

	Command	| Description
	:---------| :-------
			| Returns the current temperature.
	report		| Reports the current temperature in °C to the webservie.
	monitor		| Continously reports the temperature every 15 seconds.
	
_Examples:_

	/temp/1
	/temp/1/report
	/temp/1/monitor
	
### LIGHT

Reads out the ambient light sensor and sends the value to the configured ThingSpeak channel.

_Prefix:_

	/light/1/<Command>
	
_Commands:_

	Command	| Description
	:---------| :-------
			| Returns the current light between 0..1024.
	report		| Reports the current light to the webservice.
	monitor		| Continously reports every 15 seconds.

_Examples:_

	/light/1
	/light/1/report
	/tight/1/monitor
	
