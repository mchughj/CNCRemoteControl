# CNCRemoteControl 

This is a remote control for a CNC machine.   Super simple build it consists of two main components an IR transmitter and then the receiver connected to an Arduino Uno which is directly wired to machine which is driving the CNC.

The CNC software that I use allows for keyboard shortcuts to move the gantry around.  The IR transmitter has a 'directional' control on it that sends IR signals to the receiver which is read by the UNO and translates the button presses on the remote to button presses on a virtual keyboard for the machine.  Which in turn is interpreted by the CNC controlling software into gantry movement commands.
