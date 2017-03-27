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
#include <string.h>
#include <sys/wait.h>
#include "utility.h"
#include "queue.h"



char *command = "./process";

// Define your utility functions here, you will likely need to add more...

int alloc_mem(proc p)
{
   // printf("ALLOCATING\n");
 	if (p.suspended) {
 		return 1;
 	}
    // printf("%d vs %d\n", p.res.printers, avail.printers);
 	//Check if the resources needs to be allocated, and if there is enough resources to allocate.
 	if (p.res.printers <= avail.printers && p.res.scanners <= avail.scanners && p.res.modems <= avail.modems && p.res.cds <= avail.cds) {
            avail.printers = avail.printers - p.res.printers;
            avail.scanners = avail.scanners - p.res.scanners;
            avail.modems = avail.modems - p.res.modems;
            avail.cds = avail.cds - p.res.cds;
        return 1;
 	} 
    else 
 		return 0;
 

}

void free_mem()
 {
     avail.printers = 2;
     avail.scanners = 1;
     avail.modems = 1;
     avail.cds = 2;
     //add avail_mem freeing
     //printf("FREE\n");
 }

void print_res(proc p)
{

    printf("| arrival: %d\t| processing time: %d \t| priority: %d \t| memory: %d \t| pid: %d \t| address: %d \t| RESOURCES | printers: %d \t| cds: %d \t| scanners: %d \t| modems: %d \t|\n", 
    p.arrival, p.pr_time, p.priority, p.mbytes, p.pid, p.address, p.res.printers, p.res.cds, p.res.scanners, p.res.modems);

}

void print_queue(node_t *queue)
{

    node_t * current = queue->next; //skip the head

    while (current != NULL) {
        print_res(current->process);
        current = current->next;
    }
}

int countLines(char *file)
{
    
    FILE* f = fopen(file, "r");
    int ch, l = 0;
    do 
    {
        ch = fgetc(f);
        if(ch == '\n')
            l++;
    } while (ch != EOF);

    // last line doesn't end with a new line!
    // but there has to be a line at least before the last line
    if(ch != '\n' && l != 0) 
        l++;

    fclose(f);
    //printf("%s\n", file);
    return l;
}

void load_dispatch(char *dispatch_file, node_t *queue)
{
    FILE *f;
    char *pt, buff[256] = {0};
    int lines = countLines(dispatch_file);
    f = fopen(dispatch_file, "r");

    proc p[lines]; 
    lines = 0;
    while (fgets(buff, sizeof(buff), f)) { 

        pt = strtok (buff,",");
        p[lines].arrival = atoi(pt);

        pt = strtok (NULL, ",");
        p[lines].priority = atoi(pt);

        pt = strtok (NULL, ",");
        p[lines].pr_time = atoi(pt);

        pt = strtok (NULL, ",");
        p[lines].mbytes = atoi(pt);

        pt = strtok (NULL, ",");
        p[lines].res.printers = atoi(pt);

        pt = strtok (NULL, ",");
        p[lines].res.scanners = atoi(pt);

        pt = strtok (NULL, ",");
        p[lines].res.modems = atoi(pt);

        pt = strtok (NULL, ",");
        p[lines].res.cds = atoi(pt);
        
        p[lines].suspended = 0;
        p[lines].pid = 0;
        p[lines].address = 0;

        push(queue, p[lines]);
        //print_res(p[lines]);

    }

    fclose(f);
}

