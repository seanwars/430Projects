//
//  tcb.h
//  q
//
//  Created by Sean C Bennett on 10/12/15.
//  Copyright © 2015 Sean C Bennett. All rights reserved.
//

#ifndef tcb_h
#define tcb_h
#include <ucontext.h>

typedef struct TCB_t {
    struct TCB_t     *next;
    struct TCB_t     *prev;
    ucontext_t      context;
    int data;
} TCB_t;



void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
    memset(tcb, '\0', sizeof(TCB_t));       // wash, rinse
    getcontext(&tcb->context);              // have to get parent context, else snow forms on hell
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    makecontext(&tcb->context, function, 0);// context is now cooked
}

#endif /* tcb_h */
