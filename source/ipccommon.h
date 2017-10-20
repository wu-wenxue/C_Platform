#ifndef IPCCOMMON_H
#define IPCCOMMON_H

#define IPC_SUCCESS             0
#define IPC_FAILURE             -1

#define IPC_GET_FLAG            666

#define IPC_FLAG_CREAT          1
#define IPC_FLAG_GET            2

#define MSQ_RCV_MODE_BLOCK      1
#define MSQ_RCV_MODE_NONBLOCK   2

/* Max message block size */
#define MSG_BLOCK_SIZE          51200  //1024

/* 
 * Message type:
 *     MSG_TYPE_APP APP send and BOX receive
 *     MSG_TYPE_BOX BOX send and APP receive 
 **/
#define MSG_TYPE_APP            1
#define MSG_TYPE_BOX            2

typedef struct
{
    long lMsgType;
    char sMsg[MSG_BLOCK_SIZE];
} MsgDef;

int ipcMsqInit(int iMsqKey, int iMsgFlag);
int ipcMsqRemove(int iMsqId);
int ipcMsqRecv(int iMsqId, long lMsgType, int iRcvMod, int *iMsgSize, char *sMsg);
int ipcMsqSnd(int iMsqId, long lMsgType, int iMsgSize, const char *sMsg);

#endif
