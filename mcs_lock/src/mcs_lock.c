#include "include/mcs_lock.h"
#include <stdatomic.h>
#include <stdlib.h>

void init_mcs_lock_test(mcs_lock_t *lock) {
  lock->queue_tail = NULL;
}

void mcs_lock_test(mcs_lock_t *lock, qnode_t *curr){
  curr->free = 0;
  curr->next = NULL;
  qnode_t *prev = atomic_exchange(&lock->queue_tail, curr); // fetch and store lock->queue_tail = curr, prev = previous value of lock->queue_tail
  if (prev != NULL){
    prev->next = curr;
    do {} while(!curr->free);
  }
}

void mcs_unlock_test(mcs_lock_t *lock, qnode_t *curr){
  if(curr->next == NULL){
    if (atomic_compare_exchange_strong(&lock->queue_tail, &curr, NULL)){ // atomic compare and swap, if lock->queue_tail == curr, lock->queue_tail = NULL
      return;
    }
    do{} while (!curr->next);
  }
  curr->next->free = 1;
}