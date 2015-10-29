
//****************************************************************************************************
// Name of Author(s): Austin Carr and Taylor Cameron
// Course Number and Name: CSE 430, Operating Systems
// Semester: Fall 2015
// Project: Project2
//***************************************************************************************************/

// Header files //////////////////////////////////////////////////////////////////////////////////////

#ifndef tcb_h
#define tcb_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Header file needed for ucontext calls.
#include <ucontext.h>

typedef struct TCB_t {
     struct TCB_t     *next;
     struct TCB_t     *prev;
     ucontext_t      context;
} TCB_t;

void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
    memset(tcb, '\0', sizeof(TCB_t));       // wash, rinse
    getcontext(&tcb->context);              // have to get parent context, else snow forms on hell
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    makecontext(&tcb->context, function, 0);// context is now cooked
}

#endif
