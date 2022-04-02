#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

extern int timeslice, switchmode;

typedef struct TCB_NODE *TCB_ptr;
typedef struct TCB_NODE{
    jmp_buf  Environment;
    int      Thread_id;
    TCB_ptr  Next;
    TCB_ptr  Prev;
    int i, N;
    int w, x, y, z;
} TCB;

extern jmp_buf MAIN, SCHEDULER;
extern TCB_ptr Head;
extern TCB_ptr Current;
extern TCB_ptr Work;
extern sigset_t base_mask, waiting_mask, tstp_mask, alrm_mask;

void sighandler(int signo);
void scheduler();

// Call function in the argument that is passed in
#define ThreadCreate(function, thread_id, number)                                         \
{                                                                                         \
    /* Please fill this code section. */		  										  \
    function(thread_id, number);                                                          \
}

// Build up TCB_NODE for each function, insert it into circular linked-list
#define ThreadInit(thread_id, number)                                                     \
{                                                                                         \
    /* Please fill this code section. */												  \
    TCB_ptr new_ptr = (TCB_ptr)malloc(sizeof(TCB));                                       \
    new_ptr->Thread_id = thread_id;                                                       \
    new_ptr->N = number;                                                                  \
    new_ptr->i = 1;                                                                       \
    if (Head == NULL)                                                                     \
    {                                                                                     \
        Head = new_ptr;                                                                   \
        Current = Head;                                                                   \
    }                                                                                     \
    else                                                                                  \
    {                                                                                     \
        Current->Next = new_ptr;                                                          \
        new_ptr->Prev = Current;                                                          \
        Current = new_ptr;                                                                \
    }                                                                                     \
    Head->Prev = Current;                                                                 \
    Current->Next = Head;                                                                 \
}

// Call this while a thread is terminated
#define ThreadExit()                                                                      \
{                                                                                         \
    /* Please fill this code section. */												  \
    longjmp(SCHEDULER, 2);                                                                \
}

// Decided whether to "context switch" based on the switchmode argument passed in main.c
#define ThreadYield()                                                                     \
{                                                                                         \
    /* Please fill this code section. */												  \
    if (switchmode == 0)                                                                  \
        longjmp(SCHEDULER, 1);                                                            \
    else                                                                                  \
    {                                                                                     \
        sigpending(&waiting_mask);                                                        \
        if (sigismember(&waiting_mask, SIGTSTP))                                          \
            sigprocmask(SIG_UNBLOCK, &tstp_mask, NULL);                                   \
        else if (sigismember(&waiting_mask, SIGALRM))                                     \
            sigprocmask(SIG_UNBLOCK, &alrm_mask, NULL);                                   \
        else                                                                              \
            continue;                                                                     \
    }                                                                                     \
}
