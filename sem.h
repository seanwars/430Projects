//
//  sem.h
//  sem
//
//  Created by Sean C Bennett on 10/29/15.
//  Created by Shane T. Nelson on 10/29/15.
//  Copyright © 2015 Sean C Bennett. All rights reserved.
//
#ifndef sem_h
#define sem_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "threads.h"

typedef struct sem_t{
	int count;
	struct TCB_t *Q;
}sem_t;

//Initialize the semaphore for positive values above 0
int InitSem(sem_t* sem, int value)
{
	if(value <= 0)
	{
		return -1;
	}
	else
		sem->count = value;
	return 0;
}
//wait function
void P(sem_t* sem)
{
	sem->count--;
	if(sem->count < 0)
	{
		TCB_t* temp = DelQueue(RunQ);
		AddQueue(&sem->Q, temp);
		swapcontext(&(temp->context), &(RunQ->context));
	}
}
//signal function
void V(sem_t* sem)
{
	sem->count++;
	if(sem->count <= 0)
	{
		TCB_t* temp = DelQueue(sem->Q);
		AddQueue(&RunQ, temp);
	}
	yield();
}
#endif
