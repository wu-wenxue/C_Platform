
#include "thread.h"
#include "common.h"
#include <unistd.h>

ThreadData* threadDataCreate(long iData, double fData, void* vData, THREADDATA_FREE vFree)
{
    ThreadData *data;

    data = malloc(sizeof(*data));
    if(data == NULL)
    {
        return NULL;
    }

    data->iData = iData;
    data->fData = fData;
    data->vData = vData;
    data->vDataFree = vFree;

    return data;
}

void threadDataRelease(ThreadData* data)
{
    if(data)
    {
        if(data->vData)
        {
            if(data->vDataFree)
            {
                data->vDataFree(data->vData);
            }
        }
    }
}

Thread* threadCreate(int intervalInMS, ThreadData* privData, THREAD_RUN run)
{
    Thread *thread;

    thread = malloc(sizeof(*thread));
    if(thread == NULL)
    {
        return NULL;
    }

    thread->sleepIntervalInMS = intervalInMS;
    thread->privData = privData;
    thread->run = run;
    thread->running = THREAD_STOPPED;
    thread->threadArgument = thread;
    thread->threadId = 0;

    return thread;
}

void threadRelease(Thread* thread)
{
    if(thread)
    {
        if(thread->privData)
        {
            threadDataRelease(thread->privData);
        }
        free(thread);
    }
}

void threadStart(Thread* thread)
{
    int retCode;

    if(thread == NULL || thread->running == THREAD_RUNNING)
    {
        return;
    }

    thread->running = THREAD_RUNNING;
    retCode = pthread_create(&thread->threadId, NULL, (void*)thread->run, thread->threadArgument);
    if(retCode)
    {
        thread->running = THREAD_STOPPED;
    }
}

void threadStop(Thread* thread)
{
    if(thread == NULL)
    {
        return;
    }
    thread->running = THREAD_STOPPED;
    pthread_join(thread->threadId, NULL);
}

void threadSleep(Thread* thread)
{
    if(thread)
    {
        usleep(thread->sleepIntervalInMS*1000);
    }
}
