#include "shell.h"
#include "logger.h"
#include "errorcode.h"
#include <stdbool.h>

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>


short shellExecutePattern(const char* shell, const char* pattern) {
    bool flag = false;
    short ec = EC_ERROR;

    if (shell && pattern) {
        char line[512] = {0};
        FILE *file = popen(shell, "r");

        if (file) {
            while (fgets(line, sizeof(line), file)) {
                if (strstr(line, pattern)) {
                    flag = true;
                    break;
                }
                memset(line, 0, sizeof(line));
            }
            fclose(file);
        } else {
            loggerLog(LOG_E, "shellExecutePattern, open file failed");
        }
    } else {
        ec = EC_ARGINVALID;
    }

    if (flag) {
        ec = EC_OK;
    }

    return ec;
}

short shellExecute(const char* shell) {
    short ec = EC_OK;

    if (shell) {
        loggerLog(LOG_D, "shellExecute, try to execute:%s", shell);
        ec = system(shell);
        if (ec == -1 || ec == 127) {
            ec = EC_SHELLERROR;
        }
    } else {
        ec = EC_ARGINVALID;
    }

    return ec;
}

int shellRebootSystem() {
    return shellExecute("reboot");
}

int shellAlive(const char* ip) {
    char cmd[32] = {0};

    snprintf(cmd, sizeof(cmd), "ping -w 3 -c 1 %s", ip);
    if (shellExecutePattern(cmd, "time=") == EC_OK) {
        return 1;
    }

    return 0;
}
