//
//  q.h
//  q
//
//  Created by Sean C Bennett on 10/12/15.
//  Created by Shane T. Nelson on 10/12/15.
//  Copyright © 2015 Sean C Bennett. All rights reserved.
//
#ifndef q_h
#define q_h
#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tcb.h"
#define ALLOCATE(t) (t*) calloc(1, sizeof(t))

int data = 0;

typedef struct Queue
{
    struct TCB_t * head;
} Queue;

Queue * runQ; //global header pointer to TCB
//Queue * RunQ; //global header pointer to TCB

TCB_t * NewItem();
Queue * InitQueue();
void AddQueue(struct Queue * queue, struct TCB_t * item);
TCB_t * DelQueue(struct Queue * queue);
void RotateQ(struct Queue * queue);

struct TCB_t * NewItem()
{
    TCB_t * node = ALLOCATE(struct TCB_t);
    node->prev = NULL;
    node->next = NULL;
    node->data = ++data;
    return node;
}

struct Queue * InitQueue()
{
    return ALLOCATE(struct Queue);
}

void AddQueue(struct Queue * queue, struct TCB_t * node)
{
    if(queue->head == NULL)
    {
        queue->head = node;
        queue->head->prev = queue->head;
        queue->head->next = queue->head;
    }
    else
    {
        TCB_t * tail = queue->head->prev;
        tail->next = node;
        node->prev = tail;
        tail = tail->next;
        
        tail->next = queue->head;
        queue->head->prev = tail;
    }
}

struct TCB_t * DelQueue(struct Queue * queue)
//struct Queue * DelQueue(struct Queue * queue)
{
    if(queue->head == NULL) // if the queue is empty
    {
        return NULL;
    }
    else if (queue->head->next == queue->head) //if there is one node
    {
        TCB_t * temp = queue->head;
        queue->head = NULL;
        return temp;
    }
    else //more than one node
    {
        TCB_t * temp = queue->head;
        TCB_t * tail = queue->head->prev;
        
        if(queue->head->next == queue->head)
        {
            queue->head = NULL;
        }
        else
        {
            queue->head = queue->head->next;
            queue->head->prev = tail;
            tail->next = queue->head;
        }
        return temp;
    }
}
void RotateQ(struct Queue * queue)
{
    queue->head = queue->head->next;
}

#endif /* q_h */
