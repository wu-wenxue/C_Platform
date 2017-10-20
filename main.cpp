

#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include "test.h"


using namespace std;

int myprintf(char* pformat,...)
{
    va_list pArgList;
    char buf[1024] = {0};
    va_start(pArgList,pformat);
    vsnprintf(buf,sizeof(buf),pformat,pArgList);

    int nByteWrite = vfprintf(stdout, pformat,pArgList);

    va_end(pArgList);
    printf("\nbuf : [%s] \n",buf);

    return nByteWrite;
}

int test(const char* fmt, ...)
{
//    int off;
//    char log[1024];
//    struct timeval tv;
//    struct tm *stm;
//    va_list ap;


//    gettimeofday(&tv, NULL);
//    stm = localtime(&tv.tv_sec);
//    off = strftime(log+1, sizeof(log)-1, " %Y-%m-%d %H:%M:%S.", stm);
//    snprintf(log+off+1, sizeof(log)-off-1, "%03d ", (int)tv.tv_usec/1000);
//    va_start(ap, fmt);
//    vsnprintf(log+off+5, sizeof(log)-off-5, fmt, ap);
//    va_end(ap);

//    printf("log : %s \n",log);
}

int main()
{

//    int num = myprintf("test %d , %s , %s ,%d",1,"2","3",4);
//    printf("num : %d\n",num);

//    test("test1","test2");

//    loggerInitialize();
//    loggerLog(LOG_D,"test %d , %s , %s ,%d",1,"2","3",4);

//    test_location();

    test_download();

    getchar();

    return 0;
}
