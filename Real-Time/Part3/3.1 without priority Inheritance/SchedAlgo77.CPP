/********************************************************************/
/* A Small Real Time System for the Real-Time laboratory                 */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum                  */
/* Jerusalem College of Technology, 5759-64 (1999)                            */
/* SchedAlgo64.CPP, short-term scheduler algorithms                */
/****************************************************************/

/*By:

מיכל יונה 208094904
*/

#include "smarts77.h"

int roundRobin( )
// Round Robin short-term algorithm 
{
	int count;
	int nextTask = (SMARTS.getCurrentTask()+1)%SMARTS.getTotalTasks( );
	for (count=0;
	     SMARTS.getStatus(nextTask)!=READY && count<SMARTS.getTotalTasks( );
	     count++)
	     nextTask=++nextTask%SMARTS.getTotalTasks( );
	if (count == SMARTS.getTotalTasks( ))	// no found READY task to run
		nextTask = SMARTS.getTotalTasks( );
	return nextTask;
}


//----------------------NEW-----------------------------//
int EDF()
// Edf algorithm 
{
	int min = MAXINT;
    int nextTask = SMARTS.getTotalTasks();
	
	for (int i = 0; i < SMARTS.getTotalTasks(); i++)
	{
		if(SMARTS.getStatus(i) == READY)
		{
			//find the task with the soonest deadline
			if (SMARTS.getCycleTime(i) < min)
			{
				min = SMARTS.getCycleTime(i);
				nextTask = i;
			}

		}
	}
	return nextTask;
}


//---------------------- NEW for targil 2-----------------------------//

// RMS algorithm- Rate Monotonic Scheduling
//the task with the lowest time cycle has higher priority

int RMS()

{
	int min = MAXINT;
    int nextTask = SMARTS.getTotalTasks();
	
	for (int i = 0; i < SMARTS.getTotalTasks(); i++)
	{
		if(SMARTS.getStatus(i) == READY)
		{
			//find the task with the highest priority
			if (SMARTS.getCurrentPriority(i) < min)
			{
				min = SMARTS.getCurrentPriority(i);
				nextTask = i;
			}

		}
	}
	return nextTask;
}

//---------------------- NEW for targil 2-----------------------------//

