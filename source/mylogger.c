
#if 0

#include "mylogger.h"
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/file.h>
#include <stdio.h>

struct log_pair
{
    int     level;
    char    *id;
} logPairs[] =
{
    {LOG_D, "debug"},
    {LOG_I, "info"},
    {LOG_W, "warn"},
    {LOG_E, "err"},
    {LOG_F, "fatal"},
    {LOG_UNDEF, NULL}
};

pthread_mutex_t logMutex;
char* logfile = NULL;
int logMaxSize = 2048*1024;
int logLevel = LOG_D;


void loggerInitialize()
{
    pthread_mutex_init(&logMutex, NULL);

    logfile = "./test.log";
    logLevel = 1;
}

void loggerLog(int level, const char* fmt, ...)
{
    FILE *file;
    struct stat state;

    if(level != LOG_ALL && level < logLevel)
    {
        return;
    }
    pthread_mutex_lock(&logMutex);
    if(stat(logfile, &state) == 0)
    {
        if(state.st_size >= logMaxSize)
        {
            remove(logfile);
        }
    }
    if((file = fopen(logfile, "a")) == NULL)
    {
        pthread_mutex_unlock(&logMutex);
        return;
    }

    /*if(ftell(file) >= agent.config.logMaxSize)
    {
        int fd = 0;

        fclose(file);
        fd = open(AGENT_LOG_FILE, O_TRUNC);
        if(fd > 0)
        {
            close(fd);
        }
        file = fopen(AGENT_LOG_FILE, "a");
    }*/

    if(file)
    {
        int off;
        char log[LOG_MAX_MSG];
        struct timeval tv;
        struct tm *stm;
        va_list ap;

        switch(level)
        {
            case LOG_D:
                log[0] = 'D';
                break;
            case LOG_I:
                log[0] = 'I';
                break;
            case LOG_W:
                log[0] = 'W';
                break;
            case LOG_E:
                log[0] = 'E';
                break;
            case LOG_F:
                log[0] = 'F';
                break;
            default:
                log[0] = 'A';
        }
        gettimeofday(&tv, NULL);
        stm = localtime(&tv.tv_sec);
        off = strftime(log+1, sizeof(log)-1, " %Y-%m-%d %H:%M:%S.", stm);
        snprintf(log+off+1, sizeof(log)-off-1, "%03d ", (int)tv.tv_usec/1000);
        va_start(ap, fmt);
        vsnprintf(log+off+5, sizeof(log)-off-5, fmt, ap);
        va_end(ap);
        printf("%s\n", log);
        fprintf(file, "%s\n",log);
        fflush(file);
        fclose(file);
    }
    pthread_mutex_unlock(&logMutex);
}

#endif
