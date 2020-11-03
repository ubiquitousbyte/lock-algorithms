#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "inc/LockOne.h"

typedef struct threadPayload {
    LockOne *lockObj;
    int *counter;
    uint8_t threadID;
} threadArgs;

void * increment(void *args)
{
    threadArgs *arguments = (threadArgs *) args;

    // Entering critical section
    arguments->lockObj->lock(arguments->lockObj, arguments->threadID);
    printf("Thread %d entered critical region.\n", arguments->threadID);
    *(arguments->counter) += 1;
    printf("Thread %d is leaving critical region.\n",arguments->threadID);
    // Leaving critical section
    arguments->lockObj->unlock(arguments->lockObj, arguments->threadID);
}

int main() {
    pthread_t threads[2];
    int counter = 0;

    LockOne *lock = malloc(sizeof(LockOne));

    if (LOCK_NO_ERROR != LockOne_init(lock))
    {
        printf("Could not initialize lock.\n");
        return 1;
    }

    threadArgs firstArgs = {lock, &counter, 0};
    threadArgs secondArgs = {lock, &counter, 1};
    pthread_create(&threads[0], NULL, increment, &firstArgs);
    pthread_create(&threads[1], NULL, increment, &secondArgs);

    pthread_exit(NULL);

    LockOne_destroy(lock);
    return 0;
}
