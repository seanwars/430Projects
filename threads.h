#ifndef threads_h
#define threads_h

#include "q.h"

struct TCB_t *RunQ;

void start_thread(void (*function)(void))
{    
    void *stack = malloc(8192); //create stack of size 8192
    TCB_t* newTCB = (struct TCB_t*)malloc(sizeof(struct TCB_t)); //create new TCB object
    init_TCB(newTCB,function,stack,8192);
    AddQueue(&RunQ, newTCB);
}

void run()
{                           
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(RunQ->context));  // start the first thread
}

//swaps context if the current context to the next context
void yield()
{
    TCB_t *prev = RunQ;
    RotateQ(&RunQ);
    swapcontext(&(prev->context), &(RunQ->context));  
}

#endif
