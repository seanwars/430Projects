//
//  threads.h
//  q
//
//  Created by Shane T. Nelson on 10/12/15.
//	Created by Sean C Bennett on 10/12/15
//  Copyright © 2015 Shane T. Nelson. All rights reserved.
//

#ifndef threads_h
#define threads_h
#include <malloc.h>
#include "q.h"

void start_thread(void (*f)(void))
{
	TCB_t * t = ALLOCATE(TCB_t);//allocate a TCB_t
	void * s = malloc(8192); //allocate a stack
	//char * sp = (char *)_malloca( 8192 );	
	init_TCB(t, f, s, 8192);
	addQueue(runQ, t);
}

void run()
{
	ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(RunQ->conext));  // start the first thread
}

void yield()
{
	ucontext_t previous = runQ->head->context;
	//TCB_t *curr, *next;
	//curr = runQ;
	RotateQ(runQ);
	ucontext_t curr = runQ->head->conext;
	//next = runQ;
	swapcontext(&previous, &curr);
}

#endif /* threads_h */
