/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, <Samina Rahmanyar, Matthew Rabski>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "queue.h"

const char *resource_list[8] = {"arrival", "priority", "pr_time", "mbytes", "printers", 
    "scanners", "modems", "cds"};

char *command = "./process";

// Define your utility functions here, you will likely need to add more...

// int alloc_mem(resources res, int size)
// {
//      ...
// }

// free_mem(resources res, int index, int size)
// {
//      ...
// }

void print_res(resources p)
{

    printf("| %s: %d\t| %s: %d \t| %s: %d \t| %s: %d |\n| %s: %d\t| %s: %d \t| %s: %d \t| %s: %d |\n\n", resource_list[0], p.arrival, resource_list[1], p.priority,resource_list[2], p.pr_time,
    resource_list[3],  p.mbytes,resource_list[4], p.printers,resource_list[5], p.scanners,resource_list[6], p.modems, resource_list[7], p.cds);

}

void load_dispatch(char *dispatch_file, node_t *queue)
{
    FILE *f;
    char *pt, buff[256] = {0};
    resources p;

    f = fopen(dispatch_file, "r");

    while (fgets(buff, sizeof(buff), f)) { 

        pt = strtok (buff,",");
        p.arrival = atoi(pt);

        pt = strtok (NULL, ",");
        p.priority = atoi(pt);

        pt = strtok (NULL, ",");
        p.pr_time = atoi(pt);

        pt = strtok (NULL, ",");
        p.mbytes = atoi(pt);

        pt = strtok (NULL, ",");
        p.modems = atoi(pt);

        pt = strtok (NULL, ",");
        p.printers = atoi(pt);

        pt = strtok (NULL, ",");
        p.scanners = atoi(pt);

        pt = strtok (NULL, ",");
        p.cds = atoi(pt);
        
        
        print_res(p);

    }

    fclose(f);
}
