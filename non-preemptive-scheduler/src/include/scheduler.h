#ifndef SCHEDULER_H
#define SCHEDULER_H
void task (void *pvParameters);

typedef struct task_t {
  void (*task)(void *);
  void *arg;
  struct task_t *next;
} task_t;

typedef struct {
    int arg1;
    int arg2;
} task_args_t;

void add_task(void (*task)(void *), void *arg);
void scheduler_init();
void scheduler_start();
void run();
task_t *head;
task_t *tail;

#endif