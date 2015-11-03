//
//  thread_test2.c
//  thread_test2
//
//  Created by Sean C Bennett on 10/12/15.
//  Created by Shane T. Nelson on 10/12/15.
//  Copyright © 2015 Sean C Bennett. All rights reserved.
//
#include "sem.h"

#define SIZE	3	//Size of the buffer
//These may be unnecessary
#define P		2	//Number of producers
#define C		2	//Number of consumers

typedef struct buf_t {
	int buf[SIZE];
	int in;			//first empty slot
	int out;		//first full slot
	sem_t full;		//keep track of full spots
	sem_t empty;	//keep track of empty spots
	sem_t mutexC;	//Enforce mutual exclusion
	sem_t mutexP;
}buf_t;

int global = 0;
//sem_t mutex;
buf_t shared;

//get item

//put item
// Thread test1 
void thread1(void){
    int local = 0;
    printf("Running Thread 1!\n");
    
    while (1) {
		P(&mutex);
        printf("Thread 1: GlobalCount= %d  LocalCount = %d \n",global,local);
        global++;
        local++;
        sleep(1);
		V(&mutex);
		printf("Thread 1: Out of the semaphore \n");
        sleep(1);
    }
    
    return;
}
// Thread test2
void thread2(void) {
    //square local each time
    int local = 2; 
    printf("Running Thread 2!\n");
    
    while(1){
		P(&mutex);
        printf("Thread 2: GlobalCount= %d  LocalCount = %d \n",global,local);
        global++;
        local *= 2;
        sleep(1);
		V(&mutex);
        printf("Thread 2: Out of the semaphore \n");
		sleep(1);
    }
    
    return;
}
// Main function
int main() {
	int ret;
    TCB_t *RunQ = 0;
	ret = InitSem(&mutex, 1);
	if(ret < 0)
	{
		printf("Error initializing semaphore");
	}
    InitQueue(&RunQ);
    start_thread(thread1);
    start_thread(thread2);
    run();
    
    return 0;
}
