//****************************************************************************************************
// Name of Author(s): Austin Carr and Taylor Cameron
// Course Number and Name: CSE 430, Operating Systems
// Semester: Fall 2015
// Project: Project2
//***************************************************************************************************/

#include "threads.h"

int global = 0;

// Thread test1 
void thread1(void){
    int local = 0;
    
    printf("Running Thread 1!\n");
    
    while (1) {
        printf("Thread 1: GlobalCount= %d  LocalCount = %d \n",global,local);
        global++;
        local++;
        sleep(1);
        yield();
    }
    
    return;
}
// Thread test2
void thread2(void) {
    //cubing local each time
    
    int local = 3;
    
    printf("Running Thread 2!\n");
    
    while(1){
        printf("Thread 2: GlobalCount= %d  LocalCount = %d \n",global,local);
        global++;
        local *= 3;
        sleep(1);
        yield();
    }
    
    return;
}
// Main function
int main() {
    TCB_t *RunQ = 0;
    InitQueue(&RunQ);
    start_thread(thread1);
    start_thread(thread2);
    run();
    
    return 0;
}
