#ifndef THREAD_H
#define THREAD_H
#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>

typedef void(*THREADDATA_FREE)(void*);
typedef void(*THREAD_RUN)(void*);

typedef struct thread_data
{
    long            iData;
    double          fData;
    void            *vData;
    THREADDATA_FREE vDataFree;
} ThreadData;

#define threadDataGetSignedLong(d)  ((d)->iData)
#define threadDataGetDouble(d)      ((d)->fData)
#define threadDataGetVoid(d)        ((d)->vData)

#define THREAD_STOPPED      0
#define THREAD_RUNNING      1

typedef struct thread
{
    pthread_t       threadId;           /* thread ID                              */
    void            *threadArgument;    /* thread argument passed to run function */
    int             running;            /* thread running flag                    */
    int             sleepIntervalInMS;  /* sleep time(millisecond)                */
    ThreadData      *privData;          /* thread data                            */
    THREAD_RUN      run;                /* thread working function                */
} Thread;


/*
 * Function:  create ThreadData instance.
 * Arguments:
 *            iData -- input, long integer data.
 *            fData -- input, double data.
 *            vData -- input, any type of data, can be structure, function or other.
 *            vFree -- input, callback function to free vData, can.
 * Return:    return thread data instance on success, NULL on error.
 */
ThreadData* threadDataCreate(long iData, double fData, void* vData, THREADDATA_FREE vFree);

/*
 * Function:  free ThreadData instance.
 * Arguments: data -- input, ThreadData instance created by threadDataCreate.
 * Return:    none.
 */
void threadDataRelease(ThreadData* data);

/*
 * Function:  create Thread instance.
 * Arguments:
 *            intervalInMS -- input, sleep time(unit:microsecond).
 *            privData     -- input, private data needed by thread.
 *            run          -- input, thread working method.
 *
 * Return:    return NULL on error, return new Thread instance on success
 */
Thread* threadCreate(int intervalInMS, ThreadData* privData, THREAD_RUN run);

/*
 * Function:  free Thread instance, created by threadCreate.
 * Arguments: thread -- input, thread instance.
 * Return:    none.
 */
void threadRelease(Thread* thread);

/*
 * Function:  start thread.
 * Arguments: thread -- input, thread instance.
 * Return:    none.
 */
void threadStart(Thread* thread);

/*
 * Function:  stop thread.
 * Arguments: thread -- input, thread instance.
 * Return:    none.
 */
void threadStop(Thread* thread);

/*
 * Function:  sleep thread, the sleep time is in microseconds
 * Arguments: thread -- input, thread instance.
 * Return:    none.
 */
void threadSleep(Thread* thread);

#ifdef __cplusplus
}
#endif

#endif // THREAD_H

