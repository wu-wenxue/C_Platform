#ifndef MYLOGGER_H
#define MYLOGGER_H


#ifdef __cplusplus
extern "C" {
#endif

#if 0

#define LOG_UNDEF   -1
#define LOG_D       1   /* debug */
#define LOG_I       2   /* info  */
#define LOG_W       3   /* warn  */
#define LOG_E       4   /* error */
#define LOG_F       5   /* fatal */
#define LOG_ALL     6

#define LOG_MAX_MSG     2048


void        loggerInitialize();
//int         loggerGetLevel(const char* name);
//const char* loggerGetName(int level);
void        loggerLog(int level, const char* fmt, ...);


#endif

#ifdef __cplusplus
}
#endif

#endif // MYLOGGER_H

