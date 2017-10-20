/* 
 * Message: header file, define log manipulations. Log levels and log file
 *          log file size control.
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
#ifndef LOGGER_H
#define LOGGER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"

#define LOG_UNDEF   -1
#define LOG_D       1   /* debug */
#define LOG_I       2   /* info  */
#define LOG_W       3   /* warn  */
#define LOG_E       4   /* error */
#define LOG_F       5   /* fatal */
#define LOG_ALL     6

#define LOG_MAX_MSG     2048

typedef struct
{
    char* logFile;
    int logLevel;
    int singleLogSize;
    int logFileMaxSize;
}LogConfig;

void        loggerInitialize(LogConfig* config);
int         loggerGetLevel(const char* name);
const char* loggerGetName(int level);
void        loggerLog(int level, const char* fmt, ...);

#ifdef __cplusplus
}
#endif
#endif
