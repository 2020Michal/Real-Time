/********************************************************************/
/* A Small Real Time System for the Real-Time laboratory            */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum              */
/* Jerusalem College of Technology, 5759-64 (1999)                  */
/* update  Tishrey   5777                                           */
/* SMARTS77.H, main header file                                     */
/********************************************************************/

/*By:

מיכל יונה 208094904
*/

#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <values.h>
#include <iostream.h>

/**********    Constants    **********/
#define true 1
#define false 0
#define timerInt 0x08
#define userInt 0x60
#define MaxTask 15
#define MaxStack 512
enum taskStatus {READY, NOT_ACTIVE, SUSPENDED, SLEEP, UNDEFINED};

/**********    Classes    **********/
class Event
{
private:
	int  flag;       // arrived flag
	void *data;      // the parameter
	char source;     // source task name
	char dest;       // destination task name
	int senderWait;  // tells if the sender has to wait till the reciver receives
	int testAndSet();// test and set 'flag' in an 'atomic transaction'
 public:
	Event();
	// sends an event to 'dest', if 'synch' is true waits until the receiver gets it.
	void send(char dest,void *param, int synch);
	// waits for the event, and returns the parameter. 
	void *wait(char &sourceP); //'sourceP' will contain the task sender ID.
	// check for for an arrived event. 'sourceP' will contain the task sender ID.
	int arrived(char &sourceP);
	// resets the event
	void reset();
};

// SMARTS manages an entry of this type for each task
class Task 
{
public:
	char name;                       // task name
	unsigned stack[MaxStack];        // the stack
	
	unsigned stackCopy[MaxStack];    // ---------NEW  a copy of the task stack to restart task 
	int numOfCyclesLeft;             // ---------NEW number of cycles the task need to run
	int cycleTime;                  // ---------NEW 
	int cycleTimeLeft;               // ---------NEW
	int contextSwitchFlag;  // enables/disables context switch // ---------NEW for targil 2
	unsigned stackSeg, stackPtr;    // the stack pointer
	int currentPriority;            // the priority of the task
	int priority;                   // the original priority
	taskStatus status;              // the status of the task
	Event *expectedEvent;           // the event that this task is waiting for
	int sleepCount;                 // the sleep remainder time
	Task();
	void declare(void far *code, void far *taskEnd, char name, /*NEW*/int cycleTime, int numOfCyclesLeft /*NEW*/);
	void redeclare();              // ---------NEW
	void sleepDecr();
	void incrPriority();
	void setOriginalPriority();

};
//                           Main class
class Parallelism
{
private:
	Task context[MaxTask];  // all tasks entries
	Task contextSched;      // scheduler entry
	unsigned schedCopy[MaxStack];  // a copy of the scheduler stack
	int totalTasks;          // total declared tasks
	int currentTask;        // time slice holding task
	int deadlock;           // deadlock flag
    int error;                          // -------------------------------NEW error flag 
	int progInt;            // 'program interrupt' flag
	//int contextSwitchFlag;  // enables/disables context switch ******************NEW for targil 2
	int endOfTimeSlice;     // indicates that has to be a context switch as soon as possible
		// a pointer to the new timer interrupt handler
	void interrupt ( *timerInterruptHandler)(...);
		// a pointer to the original BIOS timer interrupt handler
	void interrupt ( *userIntAddress)(...);
	void far *scheduler;    // a pointer to the scheduler
	void far *userTaskEnd;      // a pointer to the function called at the end of each task
public:
	int sleepTasks;         // indicates how many task is sleeping, and it can't be deadlock
	int activeTasks;        // indicates how many task is activate 
	int traceInd;           // debugging index
	long TScount;           // counts the clocks of the current task
	unsigned timerClocksBegin;// time start of the current task
	unsigned timerClocksEnd;// time finish of the current task
	int far (*algorithm)(); // short-term scheduler algorithm function
	Parallelism();
		// sets the addresses of the external functions
	void externalFunctions(void interrupt ( *timerInterruptHandler)(...),
				   void far *scheduler, void far *userTaskEnd,
				   int far (*algorithm)());
	int declareTask(void far *code, char name, /*NEW*/int cycleTime, int numOfCyclesLeft /*NEW*/);
	void runTheTasks();// start running the tasks
	void callScheduler();          // return to the control to the scheduler
	void restoreSchedStack();       // restore the 'scheduler' stack
	int getCurrentTask();           // get the current running task entry number
	void setCurrentTask(int taskNum);// set the next running task number
	int getTotalTasks();             // get total declared tasks
	int getDeadlock();              // get deadlock flag
	void setDeadlock();             // set deadlock flag
	int contextSwitchOn();          // enable context switch
	void contextSwitchOff();        // disable context switch
	int getContextSwitch();         // get 'context switch' flag status
	void setProgInt();              // set the 'program interrupt' flag
	void resetProgInt();            // clear the 'program interrupt' flag
	int getProgInt();               // get the 'program interrupt' flag status
	void setEndOfTimeSlice();       // set the 'end of time slice' flag
	char getName(int taskNum);
	char getCurrentName();
	taskStatus getStatus(int taskNum);
	taskStatus getCurrentStatus();
	void resume(int taskNum);
	void resume(char taskName);
	void setCurrentNotActive();
	void suspended();
	void incrPriority(int taskNum );
	void setOriginalPriority(int taskNum );
	void setCurrentOriginalPriority();
	Event *getExpectedEvent(int taskNum);
	Event *getCurrentExpectedEvent();
	void setCurrentExpectedEvent(Event *expectedEvent);
	void sleep(int t);             // sleep current task for 't' milliseconds
	void sleepDecr(int taskNum);
	void getCurrentStack(unsigned &StackSeg, unsigned &StackPtr);
	void setCurrentStack(unsigned StackSeg, unsigned StackPtr);
	void getSchedStack(unsigned &StackSeg, unsigned &StackPtr);
	void handleTimers();
	
	//------------------------ NEW-------------------------

	int  getNumOfCyclesLeft(int i);             // --------- NEW 
    int  getCycleTime(int i);                  // --------- NEW 
    int  getCycleTimeLeft(int i);             // --------- NEW
    void setError();                         // --------- NEW
	int  getError();                        // --------- NEW
	int  allTaskFinished();                //---------- NEW
	
	
	int getPriority(int i); // --------------NEW for targil 2
	void setCurrentPriority(int taskNum);//---------------------NEW for targil 2
	int getCurrentPriority(int taskNum);//----------------------NEW for targil 2
	void taskEnd();
};
//=======================
/**********    Functions    **********/
	// reads the number of the remaining clocks from the timer register
extern unsigned getTimerClocks();
	// external functions for 'externalFunctions' function
void far interrupt timerInterruptHandler(...);
void scheduler();
void myTaskEnd();
	// 'short term' scheduler algorithms 
int roundRobin();
int EDF(); //-------------------------NEW
int RMS(); //-------------------------NEW for targil 2
	// main scheduler object
extern Parallelism SMARTS;


//-------------------------NEW for targil 2
class PriorityQueue
{
private:
	int queue[MaxTask];
public:
	int tail;
	PriorityQueue();
	void enqueue(int task);
    int  dequeue();
	int  isEmpty();
	int isFull();
};
//-------------------------NEW for targil 2

//-------------------------NEW for targil 2
class Mutex
{
private:
	PriorityQueue waitingQueue;
	int s;
	int owner;
	int level;
public:
	Mutex();
	void acquire();
	void release();
};


//-------------------------NEW for targil 2
class MutexInheritance
{
private:
	PriorityQueue waitingQueue;
	int s;
	int owner;
	int level;
public:
	MutexInheritance();
	void acquire();
	void release();
};
//-------------------------NEW for targil 2


