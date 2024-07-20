#ifndef MCS_LOCK_H
#define MCS_LOCK_H

#include <stdatomic.h>

typedef struct qnode {
  int free;
  struct qnode *next;
} qnode_t;

typedef struct mcs_lock{
  _Atomic(qnode_t*) queue_tail;
} mcs_lock_t;

void init_mcs_lock_test(mcs_lock_t *lock);
void mcs_lock_test(mcs_lock_t *lock, qnode_t *curr);
void mcs_unlock_test(mcs_lock_t *lock, qnode_t *curr);

#endif // MCS_LOCK_H