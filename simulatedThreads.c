#include "threadtools.h"

// Please complete this three functions. You may refer to the macro function defined in "threadtools.h"

// Mountain Climbing
// You are required to solve this function via iterative method, instead of recursion.
void MountainClimbing(int thread_id, int number){
	/* Please fill this code section. */
	if (Current == NULL || Current->Thread_id != thread_id)
		ThreadInit(thread_id, number);

	if (setjmp(Current->Environment) == 0)    return;

	while(Current->i < Current->N)
	{
		sleep(1);
		/* function work */
		if (Current->i == 1)
		{
			Current->w = 2;
			printf("Mountain Climbing: %d\n", Current->w);
		}
		else if (Current->i == 2)
		{
			Current->x = 3;
			printf("Mountain Climbing: %d\n", Current->x);
		}
		else
		{
			Current->y = Current->x + Current->w;
			printf("Mountain Climbing: %d\n", Current->y);
			Current->w = Current->x;
			Current->x = Current->y;
		}
		Current->i ++;

		ThreadYield();
	}
	ThreadExit();
}

// Reduce Integer
// You are required to solve this function via iterative method, instead of recursion.
void ReduceInteger(int thread_id, int number){
	/* Please fill this code section. */
	if (Current == NULL || Current->Thread_id != thread_id)
		ThreadInit(thread_id, number);

	if (setjmp(Current->Environment) == 0)    return;

	while(Current->N > 1)
	{
		sleep(1);
		/* function work */
		if (Current->N % 2 == 1)
			Current->N -= 1;
		else
			Current->N /= 2;
		
		printf("Reduce Integer: %d\n", Current->i);
		Current->i ++;

		ThreadYield();
	} 
	ThreadExit();
}

// Operation Count
// You are required to solve this function via iterative method, instead of recursion.
void OperationCount(int thread_id, int number){
	/* Please fill this code section. */
	if (Current == NULL || Current->Thread_id != thread_id)
		ThreadInit(thread_id, number);

	Current->N /= 2;

	if (setjmp(Current->Environment) == 0)    return;

	while(Current->i <= Current->N)
	{
		sleep(1);
		/* function work */
		if (Current->i == 1)
		{
			Current->w = 1;
			Current->x = 1;
			printf("Operation Count: %d\n", Current->x);
		}
		else
		{
			Current->w += 2;
			Current->x += Current->w;
			printf("Operation Count: %d\n", Current->x);
		}
		Current->i ++;
		
		ThreadYield();
	}
	ThreadExit();
}
