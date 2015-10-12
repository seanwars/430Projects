//
//  q.h
//  q
//
//  Created by Sean C Bennett on 10/12/15.
//  Copyright © 2015 Sean C Bennett. All rights reserved.
//
#ifndef q_h
#define q_h

#include <stdlib.h>
#include <stdio.h>
#define ALLOCATE(t) (t*) calloc(1, sizeof(t))

int data = 0;

typedef struct itemObj {
    struct itemObj *next;
    struct itemObj *prev;
    ucontext_t context;
    int id;
} itemObj;

typedef struct Queue
{
    struct itemObj * head;
} Queue;

itemObj * NewItem();
Queue * InitQueue();
void AddQueue(struct Queue * queue, struct itemObj * item);
itemObj * DelQueue(struct Queue * queue);
void RotateQ(struct Queue * queue);

struct itemObj * NewItem()
{
    itemObj * element = ALLOCATE(struct itemObj);
    element->prev = NULL;
    element->next = NULL;
    element->id = ++data;
    return element;
}

struct Queue * InitQueue()
{
    return ALLOCATE(struct Queue);
}

void AddQueue(struct Queue * queue, struct itemObj * element)
{
    if(queue->head == NULL)
    {
        queue->head = element;
        queue->head->prev = queue->head;
        queue->head->next = queue->head;
    }
    else
    {
        itemObj * tail = queue->head->prev;
        tail->next = element;
        element->prev = tail;
        tail = tail->next;
        
        tail->next = queue->head;
        queue->head->prev = tail;
    }
}

struct itemObj * DelQueue(struct Queue * queue)
{
    if(queue->head == NULL) // if the queue is empty
    {
        return NULL;
    }
    else if (queue->head->next == queue->head) //if there is one element
    {
        itemObj * temp = queue->head;
        queue->head = NULL;
        return temp;
    }
    else //more than one element
    {
        itemObj * temp = queue->head;
        itemObj * tail = queue->head->prev;
        
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
