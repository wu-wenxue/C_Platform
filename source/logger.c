/* 
 * Message: source file, logger.
 * 
 * Module: Log
 * 
 * Author:
 *
 * Created 2016.07.24
 * 
 * Update Histories:
 *     None
 */
#include "common.h"
#include "logger.h"
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
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
char* logFile = NULL;
int logFileMaxSize = 2048*1024;
int logLevel = LOG_D;
int singleLogMaxSize = 1024;
char* log = NULL;

void loggerInitialize(LogConfig *config)
{
    pthread_mutex_init(&logMutex, NULL);

    logFile = config->logFilePath;
    logLevel = config->logLevel;
    logFileMaxSize = config->logFileMaxSize;
    singleLogMaxSize = config->singleLogSize;

    log = (char*)malloc(singleLogMaxSize);
}


int loggerGetLevel(const char* name)
{
    int i;
    
    for(i = 0; logPairs[i].id; ++i)
    {
        if(strcasecmp(name, logPairs[i].id) == 0)
        {
            return logPairs[i].level;
        }
    }
    
    return LOG_E;
}

const char* loggerGetName(int level)
{
    int i;
    
    for(i = 0; logPairs[i].id; ++i)
    {
        if(logPairs[i].level == level)
        {
            return logPairs[i].id;
        }
    }
    
    return "err";
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
    if(stat(logFile, &state) == 0)
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
        memset(log,0,singleLogMaxSize);
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
        off = strftime(log + 1, singleLogMaxSize - 1, " %Y-%m-%d %H:%M:%S.", stm);
        snprintf(log + off + 1, singleLogMaxSize - off - 1, "%03d ", (int)tv.tv_usec/1000);
        va_start(ap, fmt);
        vsnprintf(singleLogMaxSize + off + 5, singleLogMaxSize - off - 5, fmt, ap);
        va_end(ap);
        //if(level == LOG_D) printf("%s\n", log);
        fprintf(file, "%s\n",log);
        fflush(file);
        fclose(file);
    }
    pthread_mutex_unlock(&logMutex);
}
