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
Mutex output;
Mutex m1;
//MutexInheritance m1;
Event evAtoC;
Event evAtoB;

// user Functions
void a( )
{
	int j;
	long i;
	output.acquire();
	cout << "\n *************   A Start    *********************";
	FILE* f = fopen(fileName, "a"); //a == append
	fprintf(f, "\n *************   A Start   *********************");
	fclose(f);
	output.release();
	for (j=0; j <10; j++)
	{
		for (i=0; i <200000; i++);
		output.acquire();
		cout << "A";
		f = fopen(fileName, "a");
		fprintf(f, "A");
		fclose(f);
		output.release();
	}
	output.acquire();
	cout << "\n ##   A acquire m1    ## ";
	f = fopen(fileName, "a");
	fprintf(f, "\n ##   A acquire m1    ## ");
	fclose(f);
	output.release();

	m1.acquire();
	output.acquire();
	output.release();

	
	for ( j = 0; j <10; j++)
	{
		for (i = 0; i <200000; i++);
		output.acquire();
		cout << "A";
		f = fopen(fileName, "a");
		fprintf(f, "A");
		fclose(f);
		output.release();
	}
	
	output.acquire();
	cout << "\n ##   A sent event to C    ## ";
	f = fopen(fileName, "a");
	fprintf(f, "\n ##   A sent event to C    ## ");
	fclose(f);
	output.release();	
	evAtoC.send('C', NULL, 0);//A send event to C. send(char name, void *param, int synch)
	
	output.acquire();
	cout << "\n ##   A sent event to B    ## ";
	f = fopen(fileName, "a");
	fprintf(f, "\n ##   A sent event to B    ## ");
	fclose(f);
	output.release();
	evAtoB.send('B', NULL, 0);////A send event to B. send(char name, void *param, int synch)
	
	for (j = 0; j <10; j++)
	{
		for (i = 0; i <200000; i++);
		output.acquire();
		cout << "A";
		f = fopen(fileName, "a");
		fprintf(f, "A");
		fclose(f);
		output.release();
	}
	
	output.acquire();
	cout << "\n ##   A released m1    ## \n";
	f = fopen(fileName, "a");
	fprintf(f, "\n ##   A released m1    ## \n");
	fclose(f);
	output.release();
	m1.release();
	
	for (j = 0; j <10; j++)
	{
		for (i = 0; i <200000; i++);
		output.acquire();
		cout << "A";
		f = fopen(fileName, "a");
		fprintf(f, "A");
		fclose(f);
		output.release();
	}
	
	output.acquire();
	cout << "\n *************   A Finish   *********************";
	f = fopen(fileName, "a");
	fprintf(f, "\n *************   A Finish   *********************");
	fclose(f);
	output.release();
}


void b( )
{
	int j;
	long i;
	output.acquire();
	cout << "\n *************   B Start    *********************";
	FILE* f = fopen(fileName, "a");
	fprintf(f, "\n *************   B Start   *********************");
	fclose(f);
	output.release();
	
	for (j=0; j <5; j++)
	{
		for (i=0; i < 200000; i++);
		output.acquire();
		cout << "B";
		f = fopen(fileName, "a");
		fprintf(f, "B");
		fclose(f);
		output.release();
	}
	
	output.acquire();
	cout << "\n ##   B wait to an event from A    ## ";
	f = fopen(fileName, "a");
	fprintf(f, "\n ##   B wait to an event from A    ## ");
	fclose(f);
	output.release();
	char sender;
	evAtoB.wait(sender);//B wait for event from A

	output.acquire();
	cout << "\n ##   B received event from A    ## ";
	f = fopen(fileName, "a");
	fprintf(f, "\n ##   B received event from A    ## ");
	fclose(f);
	output.release();

	for (j = 0; j <5; j++)
	{
		for (i = 0; i < 200000; i++);
		output.acquire();
		cout << "B";
		f = fopen(fileName, "a");
		fprintf(f, "B");
		fclose(f);
		output.release();
	}
	
	output.acquire();
	cout << "\n *************   B Finish   *********************";
	f = fopen(fileName, "a");
	fprintf(f, "\n *************   B Finish   *********************");
	fclose(f);
	output.release();
}

void c( )
{
	int j;
	long i;
	output.acquire();
	cout << "\n\n\n *************   C Start    *********************";
	FILE* f = fopen(fileName, "a");
	fprintf(f, "\n\n\n*************   C Start   *********************");
	fclose(f);
	output.release();
	for (j=0; j <15; j++)
	{
		for (i=0; i < 200000; i++);
		output.acquire();
		cout << "C";
		f = fopen(fileName, "a");
		fprintf(f, "C");
		fclose(f);
		output.release();
	}
	output.acquire();
	cout << "\n ##   C wait to event from A    ## ";
	f = fopen(fileName, "a");
	fprintf(f, "\n ##   C wait to event from A    ## ");
	fclose(f);
	output.release();
	
    char sender;
	evAtoC.wait(sender);//C wait for event from A

	output.acquire();
	cout << "\n ##   C received event from A    ## ";
	f = fopen(fileName, "a");
	fprintf(f, "\n ##   C received event from A    ## ");
	fclose(f);
	output.release();

	for (j = 0; j <15; j++)
	{
		for (i = 0; i < 200000; i++);
		output.acquire();
		cout << "C";
		f = fopen(fileName, "a");
		fprintf(f, "C");
		fclose(f);
		output.release();
	}
	
	output.acquire();
	cout << "\n ##   C acquire m1    ## ";
	f = fopen(fileName, "a");
	fprintf(f, "\n ##   C acquire m1    ## ");
	fclose(f);
	output.release();

	m1.acquire();


	for (j = 0; j <15; j++)
	{
		for (i = 0; i < 200000; i++);
		output.acquire();
		cout << "C";
		f = fopen(fileName, "a");
		fprintf(f, "C");
		fclose(f);
		output.release();
	}
	output.acquire();
	cout << "\n ##   C released m1    ## \n";
	f = fopen(fileName, "a");
	fprintf(f, "\n ##   C released m1    ## \n");
	fclose(f);
	output.release();

	m1.release();
	output.acquire();
	cout << "*************   C Finish   *********************";
	f = fopen(fileName, "a");
	fprintf(f, "*************   C Finish   *********************");
	fclose(f);
	output.release();
}

void main( )
{
	clrscr();
	SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, RMS ); //roundRobin EDF
	SMARTS.declareTask(a,'A',402,3); //time of each period, num of periods to run
	SMARTS.declareTask(b,'B',401,3);
	SMARTS.declareTask(c,'C',400,3);
	SMARTS.runTheTasks();
}
//50, 70, 100 stay as is

// j is the number of times the loop runs in every task:

// if j<=22 both EDF and RR work

// if 23 =< j <= 26, EDF works but RR doesn't work

// if j >= 27 both EDF and RR don't work



