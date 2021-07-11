/********************************************************************/
/* A Small Real Time System for the Real-Time laboratory            */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum              */
/* Jerusalem College of Technology, 5759-64 (1999-03)               */
/* update  Tishrey   5777                                           */
/* APP77.CPP, an application to demonstrate SMARTS77  functioning   */
/********************************************************************/

/*By:

מיכל יונה 208094904
*/

#include "smarts77.h"
char * fileName = "Atest2.txt";
Mutex Mutex1;
// user Functions
void a( )
{
	//cout is an event so we want to unable context
	Mutex1.acquire();
	cout << "\n *************   A Start    *********************";
	FILE* f = fopen(fileName, "a"); //a == append Opens the file in append mode and Start writing from the end
	fprintf(f, "\n *************   A Start    *********************");
	fclose(f);
	Mutex1.release();
	
	for (int j=0; j <5; j++)
	{
		for (long i=0; i <200000; i++);
		Mutex1.acquire();
		f = fopen(fileName, "a");
		fprintf(f, "A");
		fclose(f);
		Mutex1.release();
	}
	
	Mutex1.acquire();
	cout << "\n *************   A Finish    *********************";
	f = fopen(fileName, "a");
	fprintf(f, "\n *************   A Finish   *********************");
	fclose(f);
	Mutex1.release();
}

void b( )
{
	Mutex1.acquire();
	cout << "\n *************   B Start    *********************";
	FILE* f = fopen(fileName, "a"); //a == append
	fprintf(f, "\n *************   B Start    *********************");
	fclose(f);
	Mutex1.release();
	
	for (int j=0; j <5; j++)
	{
		for (long i=0; i < 200000; i++);
		Mutex1.acquire();
		f = fopen(fileName, "a");
		fprintf(f, "B");
		fclose(f);
		Mutex1.release();
	}
	
	Mutex1.acquire();
	cout << "\n *************   B Finish    *********************";
	f = fopen(fileName, "a");
	fprintf(f, "\n *************   B Finish   *********************");
	fclose(f);
	Mutex1.release();
}

void c( )
{
	Mutex1.acquire();
	cout << "\n *************   C Start    *********************";
	FILE* f = fopen(fileName, "a"); //a == append
	fprintf(f, "\n *************   C Start    *********************");
	fclose(f);
	Mutex1.release();
	
	for (int j=0; j <5; j++)
	{
		for (long i=0; i < 200000; i++);
		Mutex1.acquire();
		f = fopen(fileName, "a");
		fprintf(f, "C");
		fclose(f);
		Mutex1.release();
	}	
	
	Mutex1.acquire();
	cout << "\n *************   C Finish    *********************";
	f = fopen(fileName, "a");
	fprintf(f, "\n *************   C Finish   *********************");
	fclose(f);
	Mutex1.release();
}

void main( )
{
	clrscr();
	SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, RMS ); //roundRobin EDF
	SMARTS.declareTask(a,'A',30,13); //time of each period, num of periods to run
	SMARTS.declareTask(b,'B',40,14);
	SMARTS.declareTask(c,'C',50,15);
	SMARTS.runTheTasks();
}
//50, 70, 100 stay as is

// j is the number of times the loop runs in every task:

// if j<=22 both EDF and RR work

// if 23 =< j <= 26, EDF works but RR doesn't work

// if j >= 27 both EDF and RR don't work



