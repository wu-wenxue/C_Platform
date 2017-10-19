#ifndef SHELL_H
#define SHELL_H
#ifdef __cplusplus
extern "C" {
#endif

short shellExecutePattern(const char* shell, const char* pattern);

/*
 * Function:  execute shell command.
 * Arguments: shell -- shell commands
 *
 * Return:    return 0 on success, !0 on error.
 */
short shellExecute(const char* shell);

int shellRebootSystem();
int shellAlive(const char* ip);

#ifdef __cplusplus
}
#endif

#endif // SHELL_H

