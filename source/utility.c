#include "utility.h"

#include "errorcode.h"
#include "common.h"
#include "logger.h"

#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>

void getWirelessIp(char* ip, int len) {
    int i, slen;
    char* pAddress = NULL;
    char line[512];
    FILE* fp;

    if (!(fp = popen("ifconfig", "r"))) return;

    memset(ip, 0, len);
    while (fgets(line, 512, fp)) {
//        if (!strstr(line, "wwan0")) continue;
        if (!strstr(line, "3g-modem")) continue;
        fgets(line, 512, fp);
        pAddress = strchr(line, ':');
        if (pAddress) pAddress = pAddress + 1;
        for (i = 0, slen = strlen(pAddress) - 1; i < slen; i++) {
            if (pAddress[i] != 0x20) continue;
            pAddress[i] = '\0';
            memcpy(ip, pAddress, len);
            break;
        }
        break;
    }
    pclose(fp);
}

long long getMicroSeconds() {
    struct timeval tv;
    long long ust;

    gettimeofday(&tv, NULL);
    ust = ((long long)tv.tv_sec)*1000000;
    ust += tv.tv_usec;

    return ust;
}

int getMSTime() {
    struct timeval tv;
    struct tm *stm;
    int mstime = 0;

    gettimeofday(&tv, NULL);
    stm = localtime(&tv.tv_sec);

    mstime = stm->tm_hour*3600;
    mstime += stm->tm_min*60;
    mstime += stm->tm_sec;
    mstime = mstime*1000 + tv.tv_usec/1000;

    return mstime;
}

short generateTimeHexString(char* buffer, int size) {
    struct timeval stv;

    if (gettimeofday(&stv, NULL) == 0) {
        snprintf(buffer, size, "%lu%ld", stv.tv_sec, stv.tv_usec);
        return EC_OK;
    }

    return EC_ERROR;
}

char* getCurrentTimeString() {
    time_t currentTime = time(NULL);
    struct tm *stm = localtime(&currentTime);
    char *timeString = malloc(20);

    if(timeString)
    {
        strftime(timeString, 20, "%Y-%m-%d %H:%M:%S", stm);
    }

    return timeString;
}

char* getCurrentTimeString_New()
{
    time_t currentTime = time(NULL);
    struct tm *stm = localtime(&currentTime);
    char *timeString = malloc(20);

    if(timeString)
    {
        strftime(timeString, 20, "%Y%m%d%H%M%S", stm);
    }

    return timeString;
}


char hexToChar(char hex) {
    if (hex >= 0) {
        if (hex <= 9) {
            return hex+'0';
        }

        if (hex >= 10 && hex <= 15) {
            return hex+'a'-10;
        }
    }

    return hex;
}

char* stringCopy(const char* s) {

    if (s) {
        return stringLenCopy(s, strlen(s));
    }
    return NULL;
}

char* stringLenCopy(const char* s, size_t sLen) {
    char *copy;
    if (s == NULL || sLen == 0) {
        return NULL;
    }
    copy = malloc(sLen+1);
    if (copy == NULL) {
        loggerLog(LOG_E, "stringCopy %d", EC_OOM);
        return NULL;
    }

    memcpy(copy, s, sLen);
    copy[sLen] = '\0';

    return copy;
}

void stringRelease(char* s) {
    if (s) {
        free(s);
    }
}


char* stringCat2(const char* first, const char* second) {
    char *target = NULL;
    size_t len1 = 0, len2 = 0;

    if (first) {
        len1 = strlen(first);
    }
    if (second) {
        len2 = strlen(second);
    }
    if ((len1+len2) == 0) {
        return NULL;
    }

    target = malloc(len1+len2+1);
    if (target) {
        if (first) {
            memcpy(target, first, len1);
        }
        if (second) {
            memcpy(target+len1, second, len2);
        }
        target[len1+len2] = '\0';
    }

    return target;
}

char* stringCat3(const char* first, const char* second, const char* last) {
    char *target = NULL;
    size_t len1 = 0, len2 = 0, len3;

    if (first) {
        len1 = strlen(first);
    }
    if (second) {
        len2 = strlen(second);
    }
    if (last) {
        len3 = strlen(last);
    }
    if ((len1+len2+len3) == 0) {
        return NULL;
    }

    target = malloc(len1+len2+len3+1);
    if (target) {
        if (first) {
            memcpy(target, first, len1);
        }
        if (second) {
            memcpy(target+len1, second, len2);
        }
        if (last) {
            memcpy(target+len1+len2, last, len3);
        }
        target[len1+len2+len3] = '\0';
    }

    return target;
}

char* stringCat(int num, ...) {
    va_list ap;
    char *arg, *copy, *s = NULL;
    int i, alen, mlen = 1, slen = 0;

    va_start(ap, num);
    for (i = 0; i < num; i++) {
        arg = va_arg(ap, char*);
        alen = strlen(arg);
        mlen += alen;

        copy = realloc(s, mlen);
        if (!copy) {
            if (s) free(s);
            s = NULL;
            break;
        }

        s = copy;
        memcpy(s+slen, arg, alen);
        slen += alen;
    }
    va_end(ap);
    s[slen] = '\0';

    return s;
}
