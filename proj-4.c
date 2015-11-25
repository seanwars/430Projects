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

sem_t mutex;
sem_t rsem;
sem_t wsem;

unsigned int rwc = 0;
unsigned int wwc = 0;
unsigned int rc = 0;
unsigned int wc = 0;

// Reader CASE 3
void reader(void){
	sleep(1);
	printf("Entering reader\n");
	while(1)
	{
		//Reader Entry
		P(&mutex);
		printf("Reader Entry\n");
		if((wwc > 0) || (wc > 0))
		{
			rwc++;
			V(&mutex);
			P(&rsem);
			V(&mutex);
			rwc--;
		}
		rc++;
		V(&mutex);
		//READ
		printf("Reading resource: Reader # %d \n", rc);
		sleep(1);
		//Reader Exit
		P(&mutex);
		printf("Reader Exit\n");
		rc--;
		if((rc == 0) && (wwc > 0))
		{
			V(&wsem);
		}
		V(&mutex);
    }
    return;
}
// Writer CASE 3
void writer(void) {
	int i;
	sleep(1);
	printf("Entering writer\n");
    while(1){
		//Writer Entry
		P(&mutex);
		printf("Writer Entry\n");
		if((rc > 0) || (wc > 0) || (rwc > 0) || (wwc > 0))
		{
			wwc++;
			V(&mutex);
			P(&wsem);
			P(&mutex);
			wwc--;
		}
		wc++;
		V(&mutex);
		//WRITE
		printf("Writing to resource: Writer # %d \n", wc);
		sleep(1);
		//Writer Exit
		P(&mutex);
		printf("Writer Exit\n");
		wc--;
		if(rwc > 0)
		{
			for(i = 0; i <= rwc; i++)
			{
				V(&rsem);
			}
		}
		else if(wwc > 0)
		{
			V(&wsem);
		}
		V(&mutex);
    }
    
    return;
}
// Main function
int main() {
	int ret1, ret2, ret3;
    TCB_t *RunQ = 0;
    InitQueue(&RunQ);
	ret1 = InitSem(&mutex, 1);
	if(ret1 < 0)
	{
		printf("Error initializing access semaphore");
	}
	ret2 = InitSem(&rsem, 1);
	if(ret2 < 0)
	{
		printf("Error initializing reader semaphore");
	}
	ret3 = InitSem(&wsem, 1);
	if(ret3 < 0)
	{
		printf("Error initializing order semaphore");
	}

    start_thread(reader);
	start_thread(reader);
	start_thread(reader);
    start_thread(writer);
	start_thread(writer);
    run();
    
    return 0;
}
