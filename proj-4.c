//
//  proj-4.c
//  proj-4
//
//  Created by Sean C Bennett on 10/12/15.
//  Created by Shane T. Nelson on 10/12/15.
//  Copyright © 2015 Sean C Bennett. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

sem_t accessMutex;
sem_t readerMutex;
sem_t orderMutex;

unsigned int readers = 0;

// Reader 
void reader(void){
	printf("Entering reader");
	while(1)
	{
		P(&orderMutex);
		
		P(&readerMutex);
		if(readers == 0)
		{
			P(&accessMutex);
		}
		readers++;
		V(&orderMutex);
		V(&readerMutex);
		
		//readResource();
		printf("Reader %d access", readers);
		
		P(&readerMutex);
		readers--;
		if(readers == 0)
		{
			V(&accessMutex);
		}
		V(&readerMutex);
    }
    return;
}
// Writer
void writer(void) {
	printf("Entering writer");
    while(1){
		P(&orderMutex);
		P(&accessMutex);
		V(&orderMutex);
		
		//writeResource();
		printf("Writer access");
		
		V(&accessMutex);
    }
    
    return;
}
// Main function
int main() {
	int ret1, ret2, ret3;
    TCB_t *RunQ = 0;
    InitQueue(&RunQ);
	ret1 = InitSem(&accessMutex, 1);
	if(ret1 < 0)
	{
		printf("Error initializing access semaphore");
	}
	ret2 = InitSem(&readerMutex, 1);
	if(ret2 < 0)
	{
		printf("Error initializing reader semaphore");
	}
	ret3 = InitSem(&orderMutex, 1);
	if(ret3 < 0)
	{
		printf("Error initializing order semaphore");
	}

    start_thread(reader);
    start_thread(writer);
    run();
    
    return 0;
}
