#include <stdio.h>
#include <stdlib.h>
#include "include/scheduler.h"

void add_s(void *num){
    task_args_t *task_args = (task_args_t *) num;
    float a = task_args->arg1;
    float b = task_args->arg2;
    printf("Sum: %f\n", a+b);
}

void sub_s(void *num){
    task_args_t *task_args = (task_args_t *) num;
    float a = task_args->arg1;
    float b = task_args->arg2;
    printf("Difference: %f\n", a-b);
}

void mul_s(void *num){
    task_args_t *task_args = (task_args_t *) num;
    float a = task_args->arg1;
    float b = task_args->arg2;
    printf("Product: %f\n", a*b);
}

void div_s(void *num){
    task_args_t *task_args = (task_args_t *) num;
    float a = task_args->arg1;
    float b = task_args->arg2;
    printf("Quotient: %f\n", a/b);
}


int main (){
    // Initialize the scheduler
    scheduler_init();
    task_args_t *args = malloc(sizeof(task_args_t));
    if (args == NULL){
        perror("Failed to allocate memory for task arguments");
        exit(EXIT_FAILURE);
    }
    args->arg1 = 1;
    args->arg2 = 2;
    // Add tasks to the scheduler
    add_task(add_s, (void *) args);
    add_task(sub_s, (void *) args);
    add_task(mul_s, (void *) args);
    add_task(div_s, (void *) args);

    // Start the scheduler
    scheduler_start();
    free(args);
    return 0;
}