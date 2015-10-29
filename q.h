//****************************************************************************************************
// Name of Author(s): Austin Carr and Taylor Cameron
// Course Number and Name: CSE 430, Operating Systems
// Semester: Fall 2015
// Project: Project2
//***************************************************************************************************/
#ifndef q_h
#define q_h


#include "tcb.h"

// Returns a pointer to a new q-element
TCB_t* NewItem(){

	TCB_t* item = malloc(sizeof(struct TCB_t));
	item->next = NULL;
	item->prev = NULL;
	return item;

}
// Creates a empty queue, pointed to by the variable head.
void InitQueue(TCB_t** head){
	
	*head = NULL;
}

// Adds a queue item, pointed to by “item”, to the queue pointed to by head.
void AddQueue(TCB_t** head, TCB_t* item){

	// If head is NULL, set head to point to item
	if(*head == NULL)
	{
	        *head = item;
		item->next = item;
		item->prev = item;
	}
    
	// If queue has 1 item, add item after that node
	else if(((*head)->next) == (*head))
	{
		(*head)->next = item;
        	item->next = *head;
        	item->prev = *head;
        	(*head)->prev = item;
	}

	// If que has more than 1 item, iterate to end of list and add then item
	else
	{
        
		TCB_t* temp = *head;
        
		while(temp->next != *head)
		{
			temp = temp->next;
		}
		
 	// Set next item as i, set i->prev to original last item, and
   	// item->next to head pointer
        	temp->next = item;
		item->prev = temp;
		item->next = *head;
        	(*head)->prev = item;
	}
}
// Deletes an item from head and returns a pointer to the deleted item
TCB_t* DelQueue(TCB_t** head){

	// If queue is empty, return null pointer to head
	if(*head == NULL)
	{
		return *head;
	}
    
	// If queue has 1 item, delete that node and return it
	else if((*head)->next == (*head))
	{
		TCB_t* temp = *head;
        	*head = NULL;
		return temp;
	}
    
	// If que has more than 1 item, remove head and make head point to next
	else
	{
        // Save head and head's prev pointer
        	TCB_t* temp = *head;
        	TCB_t* headPrev = (*head)->prev;
        
        // Let head point to next node and let head->prev point to previous last element
        	*head = temp->next;
        	(*head)->prev = headPrev;
        
        // Update previous item to point to new head
        	headPrev->next = *head;
        	return temp;
	}

}

// Moves the header pointer to the next element in the queue. This is equivalent to AddQ(&head, DeleteQ(&head)),
// but is simpler to use and more efficient to implement.
void RotateQ(TCB_t** head){

	*head = (*head)->next;

} 

#endif
