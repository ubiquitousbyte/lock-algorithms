//
// Created by nas on 03.11.20.
//

#ifndef LOCK_ALGORITHMS_LOCK_H
#define LOCK_ALGORITHMS_LOCK_H

#include <stdint.h>

typedef enum ERROR {
    LOCK_INIT_ERROR,
    LOCK_NO_ERROR,
} ERROR;

typedef struct Lock {
    void (* lock)(struct Lock*, uint8_t);
    void (* unlock)(struct Lock*, uint8_t);
    volatile uint8_t flags[2];
} LockOne;

ERROR LockOne_init(LockOne *lockObj);

ERROR LockOne_destroy(LockOne *lockObj);

void lock(LockOne *lock, uint8_t threadID);

void unlock(LockOne *lock, uint8_t threadID);

#endif //LOCK_ALGORITHMS_LOCK_H
