# Real-Time
This project implement parts of RTOS

files explainations:

SMARTS77.H
the main header file. This file includes Event class, Mutex class, Task class, and Parallelism class. Parallelism class includes all the tasks of the system and implements the tasks schedule.

SMARTS77.CPP
SMARTS77.H class body.

SchedAlgo77.CPP
short-term scheduler algorithms: RoundRobin, EDF, RMS, FPS.

EXTERN77.CPP
This class implements the external function of SMART system.

timerInterruptHandler
This function is interrupt function and called 18.2 times per second ( every ~~ 55 millisec).

scheduler
This function is called by hardware called 'timerInterruptHandler' function or by software SMARTS system's functions or by software SMARTS system's functions.

myTaskEnd
This function called when task is done.

EVENT77.CPP
Events handling

APP77.CPP
An application to demonstrate SMARTS77 functioning.

Part 1
Implementation of activating cyclic processes using RMS algorithm.

Part 2
Implementation of Mutex (Acquire Release ect.).

Part 3
Solving the Unbounded priority inversion problem by the implementation of priority-inheritance

Unbounded priority inversion and priority-inheritance
