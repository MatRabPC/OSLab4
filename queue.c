/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, <Samina Rahmanyar, Matthew Rabski>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

// Define your FIFO queue functions here, these will most likely be the
// push and pop functions that you declared in your header file

node_t *push(node_t *head, proc process)
{ 
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = malloc(sizeof(node_t));
    current->next->process = process; //dont know why i didnt do it this way before
    current->next->next = NULL;

    return current;
}

node_t *pop(node_t *head) {
    node_t * next_node = NULL, *retval = NULL;

    if (head == NULL) {
        return retval;
    }

    next_node = (head)->next->next;
    retval = (head);
    
    free(head->next);
    head->next = next_node;

    return retval;
}
