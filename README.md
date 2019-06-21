# Arduino-Test-Platform
Using a GUI on PC to send commands to Arduino via serial port. The purpose of this project is having a way to interact with the physical world, for example controlling the state of some GPIO pin. This in fact will simplify the test procedures by avoiding an annoying flashing and re-flashing of the Arduino program memory.

# Data Structure
To control the peripherals (PORTS, TIMERS) the program writes data to special registers (for example the DDRB controls the direction of the pins associated to PORTB). We benefit from storing these informations in a data structure that fits well the specifications, in particular:

	 1. The register has to be referenced with his own name
	 2. The register is a char variable, you can do arithmetic on it
	 3. It help accessing each bit with functions like set(), toggle(), clear()
	 4. Each bit should be addressed with his own function (PORTB.B0, SREG.C)

# Communication
This is the basic concept: the PC sends two bytes, the firts one being the istruction the second one the argument.
