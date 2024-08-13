
#include <stdio.h>
#include <stdlib.h>
#include "include/scheduler.h"

void scheduler_init(){
    head = NULL;
    tail = NULL;
}

void add_task(void (*task)(void *), void *args){
    task_t *new_task = (task_t *) malloc(sizeof(task_t));
    if (new_task == NULL){
        perror("Failed to allocate memory for new task");
        exit(EXIT_FAILURE);
    }
    new_task->task = task;
    new_task->arg = args;
    new_task->next = NULL;

    if (head == NULL){
        head = new_task;
        tail = new_task;
    } else {
        tail->next = new_task;
        tail = new_task;
    }
}

void run(){
    task_t *current_task = head;
    head = head->next;
    current_task->task(current_task->arg);
    free(current_task);
}

void scheduler_start(){
    while (head != NULL){
        run();
    }
}
