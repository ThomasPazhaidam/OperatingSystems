#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;
/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Thomas
 */
void PQ_insert(int priority, char * data) {
    Node_ptr_t node = malloc(sizeof(Node_t));
    node->data=data;
    node->priority=priority;
    
    Node_ptr_t tempnode = malloc(sizeof(Node_t));
    
    if(head == NULL){
        node->next=NULL;
        head=node;
    }else{
        if(node->priority > head->priority){
            node->next=head;
            head=node; 
        }
        else{
            tempnode=head;
            while(tempnode->next != NULL && node->priority<tempnode->next->priority){
               tempnode=tempnode->next; 
            }
            node->next=tempnode->next;
            tempnode->next=node;   
        }
    }
}
/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
    Node_ptr_t tempnode = malloc(sizeof(Node_t));
    tempnode=head;
    head=head->next;
    return tempnode;
}

/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++)
        ;
    return size;
}


