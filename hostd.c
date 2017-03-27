/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, <Samina Rahmanyar, Matthew Rabski>
 * All rights reserved.
 * 
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"

// Put macros or constants here using #define
#define MEMORY 1024
int avail_mem[MEMORY];


node_t *dispatch = NULL, *real = NULL, *p2 = NULL, *p3 = NULL, *p4 = NULL;
// Put global environment variables here

// Define functions declared in hostd.h here


void queue_up(node_t *queue)
{
    node_t * current = queue->next; //skip the head

    while (current != NULL) {
        if (current->process.priority == 0)
            push(real, current->process);
        if (current->process.priority == 1)
            push(p2, current->process);
        if (current->process.priority == 2)
            push(p3, current->process);
        if (current->process.priority == 3)
            push(p4, current->process);

        current = current->next;

    }
}

int execute_process( proc proc)
{
    int status;
    char *arg[256];
    pid_t pid;
 
    print_res(proc);
     
    if (alloc_mem(proc))
    {
        if (proc.priority == 0)//get done first
        {
            pid = fork();
            if (pid == 0)
            {
            /* This is the child process.  Execute the shell command. */
                execv("./process", arg);
                exit(0);
            }//end child

            else
            {
                /* This is the parent process.  Wait for the child to complete.  */
                sleep(proc.pr_time);
                kill(pid, SIGINT);
                waitpid(-1, &status, 0);
                //deallocateMemory(avail_mem, current);
                if (!status)
                {
                    printf("TERMINATED\n");
                }
            } //end parent
           return 0;
        }//end realtime

        ////>>>>>>>>>>><<<<<<<<<<<<<<////

       if (!proc.suspended) //if first run
       {
        pid = fork();
        if (pid == 0)
        {
         /* This is the child process.  Execute the shell command. */
         //printf("exec?\n");
                execv("./process", arg);
                exit(5);
        }

        else
        {
            /* This is the parent process.  Wait for the child to complete.  */
            proc.pid = pid;
            sleep(1);
            kill(pid, SIGTSTP);        
            proc.pr_time--;
            proc.suspended = 1;
            
        }//end parent
        } //done non suspense

       else
       {
           kill(proc.pid, SIGCONT);
           sleep(1);
           kill(proc.pid, SIGTSTP);
           proc.pr_time--;
       }//end suspense

       if (proc.pr_time >= 1) //if time left
        {
            if (proc.priority == 1 || proc.priority == 2)
            {
                proc.priority++;
                if (proc.priority == 1)
                {
                    push(p3, proc);
                }
                if (proc.priority == 2)
                {
                    push(p4, proc);
                }

            }
            if (proc.priority == 3)
                {
                    push(p4, proc);
                }
        }//end time

        
        else //no time
            {
                kill(proc.pid, SIGINT);
                waitpid(proc.pid, &status, 0);
            }

        free_mem();
         }//end exec

    else
    {
        printf("NOT ENOUGH RESOURCES\n");
    }
    return 1;
}         


int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //
    dispatch = malloc(sizeof(node_t));
 	dispatch->next = NULL;
    
    real = malloc(sizeof(node_t));
 	real->next = NULL;

    p2 = malloc(sizeof(node_t));
 	p2->next = NULL;

    p3 = malloc(sizeof(node_t));
 	p3->next = NULL;

    p4 = malloc(sizeof(node_t));
 	p4->next = NULL;

    avail.printers = 2;
    avail.scanners = 1;
    avail.cds = 2;
    avail.modems = 2;

  // printf("%d\n", avail.printers);
    // Load the dispatchlist
    load_dispatch("dispatchlist", dispatch);
    printf("DISPATCHING\n");
    queue_up(dispatch);
    
   // /*
    node_t * current = real->next; //real first

    while (current != NULL) {
        execute_process(current->process);
      //  printf("%d\n", current->process.pr_time);
        current = current->next;
    }

     current = p2->next; //skip the head

    while (current != NULL) {
        execute_process(current->process);
      //  printf("%d\n", current->process.pr_time);
        current = current->next;
    } //execute all real time first, FIFO style

    current = p3->next; //skip the head

    while (current != NULL) {
        execute_process(current->process);
      //  printf("%d\n", current->process.pr_time);
        current = current->next;
    } //execute all real time first, FIFO style

    current = p4->next; //skip the head

    while (current != NULL) {
        execute_process(current->process);
      //  printf("%d\n", current->process.pr_time);
        current = current->next;
    } //execute all real time first, FIFO style

       // sleep(3); //to finish prints and all
        printf("COMPLETE. THANK YOU.\n");
  //  */
   // print_queue(real);
   // print_queue(p2);
   // print_queue(p3);
   // print_queue(p4);
    // Add each process structure instance to the job dispatch list queue

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues

    // Allocate the resources for each process before it's executed

    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty

    /* 
    while (current != NULL) { //iterate through queue loop, easy coffee-pasta

        current = current->next;
    }
    */
    return EXIT_SUCCESS;
}
