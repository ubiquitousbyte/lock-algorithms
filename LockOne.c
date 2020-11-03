//
// Created by nas on 03.11.20.
//

#include <stdlib.h>
#include <stdio.h>
#include "inc/LockOne.h"


ERROR LockOne_init(LockOne *lockObj)
{
    if (lockObj == NULL)
    {
        printf("No memory for lock object.\n");
        return LOCK_INIT_ERROR;
    }
    lockObj->flags[0] = 0;
    lockObj->flags[1] = 0;
    lockObj->lock = lock;
    lockObj->unlock = unlock;
    return LOCK_NO_ERROR;
}

void lock(LockOne *lockObj, uint8_t threadID)
{
    uint8_t otherThread = 1 - threadID;
    lockObj->flags[threadID] = 1;
    while (lockObj->flags[otherThread]) {}; // Other thread is forced to wait.
}

void unlock(LockOne *lockObj, uint8_t threadID)
{
    lockObj->flags[threadID] = 0;
}

ERROR LockOne_destroy(LockOne *lockObj)
{
    free(lockObj);
    return LOCK_NO_ERROR;
}