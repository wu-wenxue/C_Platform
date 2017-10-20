#include "ipccommon.h"
#include "logger.h"

#include "fmacros.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "common.h"

/*
 * Function: ipcMsqInit()
 *     Create or Get the MessageQ.
 * Parameters:
 *     iMsqKey    I --MessageQ key
 *     iMode      I --Message create mode
 * Return:
 *     > 0 MessageQ Id.
 *     -1 IPC_FAILURE.
 * */

char* msqPath = NULL;


int ipcMsqInit(int iMsqKey, int iMode) {
    int iMsqId;
    int iMsgFlg = 0;
    key_t ipcKey;

    if (msqPath == NULL) {
        loggerLog(LOG_D, "agent.config.msqPath is null\n");
        return -1;
    }
    ipcKey = ftok(msqPath, iMsqKey);
    if (ipcKey == -1) {
        loggerLog(LOG_D, "ftok failed, errno=[%d], error desc=[%s]\n", errno, strerror(errno));
        return IPC_FAILURE;
    }

    if (iMode == IPC_FLAG_CREAT) {
        iMsgFlg = IPC_CREAT;
    }

    iMsqId = msgget(ipcKey, IPC_GET_FLAG | iMsgFlg);
    if (iMsqId == -1) {
        loggerLog(LOG_D, "msgget failed, errno=[%d], error desc=[%s]\n", errno, strerror(errno));
        return IPC_FAILURE;
    }

    return iMsqId;
}

/*
 * Function: ipcMsqRemove()
 *     Remove the MessageQ
 * Parameters:
 *     iMsqId    I --MessageQ Id
 * Return:
 *     0 IPC_SUCCESS
 *     -1 IPC_FAILURE
 */
int ipcMsqRemove(int iMsqId) {
    return msgctl(iMsqId, IPC_RMID, NULL);
}

/*
 * Function: ipcMsqRecv()
 *     Receive Message from messageQ
 * Parameters:
 *     iMsqId        I --MessageQ Id.
 *     lMsgType      I --Message type to receive
 *     iRcvMod       I --MessageQ receive mode.
 *     iMsgSize      I/O --Max message length, Received message length.
 *     sMsg          O --Received message buffer.
 * Return:
 *     0 IPC_SUCCESS
 *     -1 IPC_FAILURE
 **/
int ipcMsqRecv(int iMsqId, long lMsgType, int iRcvMod, int *iMsgSize, char *sMsg) {
    int iRet = 0;
    long lMsgFlag = 0;
    MsgDef *msq = (MsgDef *)malloc(sizeof(MsgDef));
    if(NULL == msq)
    {
        loggerLog(LOG_D,"ipcMsqRecv, agent_malloc msq failed ");
    }

    if (iRcvMod == MSQ_RCV_MODE_NONBLOCK) {
        lMsgFlag = lMsgFlag | IPC_NOWAIT;
    }
    if (*iMsgSize > MSG_BLOCK_SIZE) {
        free(msq);
        if(NULL != msq) { msq =NULL; }
        return IPC_FAILURE;
    }

    memset(msq, 0, sizeof(MsgDef));
    iRet = msgrcv(iMsqId, msq, *iMsgSize, lMsgType, lMsgFlag);
    if (iRet == -1) {
        if (errno == ENOMSG) {

        } else {
            loggerLog(LOG_D, "msgrcv failed, errno=[%d], error desc=[%s]\n", errno, strerror(errno));
        }
        free(msq);
        if(NULL != msq) { msq =NULL; }
        return IPC_FAILURE;
    }

    *iMsgSize = iRet;
    memcpy(sMsg, msq->sMsg, *iMsgSize);
    free(msq);
    if(NULL != msq) { msq =NULL; }

    return IPC_SUCCESS;
}



/*
 * Function: ipcMsqSnd()
 *     send Message to MessageQ
 * Parameters:
 *     iMsqId    I --MessageQ Id
 *     lMsgType  I --Message type to send
 *     iMsgSize  I --length of Message
 *     sMsg      I --Message buffer for send
 * Return:
 *     0 IPC_SUCCESS
 *     -1 IPC_FAILURE
 */
int ipcMsqSnd(int iMsqId, long lMsgType, int iMsgSize, const char *sMsg) {
    int iRet = 0;
    MsgDef *msg = (MsgDef *)malloc(sizeof(MsgDef));
    if(NULL == msg)
    {
        loggerLog(LOG_D,"ipcMsqRecv, agent_malloc msg failed ");
    }

    if (sMsg == NULL || iMsgSize <= 0) {
        loggerLog(LOG_D, "ipcMsqSnd, the message is NULL");
        free(msg);
        if(NULL != msg) { msg =NULL; }
        return IPC_FAILURE;
    }
    if (iMsgSize > MSG_BLOCK_SIZE) {
        loggerLog(LOG_D, "ipcMsqSnd, the message is too long, size to send=[%d], max size=[%d]\n", iMsgSize, MSG_BLOCK_SIZE);
        free(msg);
        if(NULL != msg) { msg =NULL; }
        return IPC_FAILURE;
    }

    memset(msg, 0, sizeof(MsgDef));
    msg->lMsgType = lMsgType;
    memcpy(msg->sMsg, sMsg, iMsgSize);

    iRet = msgsnd(iMsqId, msg, iMsgSize, IPC_NOWAIT);
    if (iRet == -1) {
        loggerLog(LOG_D, "ipcMsqSnd, msgsnd failed, errno=[%d], error desc=[%s]\n", errno, strerror(errno));
        free(msg);
        if(NULL != msg) { msg =NULL; }
        return IPC_FAILURE;
    }
    free(msg);
    if(NULL != msg) { msg =NULL; }
    return IPC_SUCCESS;
}


