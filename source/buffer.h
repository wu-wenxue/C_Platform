/* 
 * Message: header file, buffer.
 *          log file size control.
 * 
 * Module: Common
 * 
 * Author:
 *
 * Created 2016.07.26
 * 
 * Update Histories:
 *     None
 */
#ifndef BUFFER_H
#define BUFFER_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct buffer
{
    char    *data;
    size_t  used;
    size_t  avaliable;
} Buffer;

void    bufferInitialize(Buffer* buffer);
void    bufferReset(Buffer* buffer);

/*
 * Function:  make buffer to have the required memory space.
 * Arguments:
 *            buff -- input, Buffer.
 *            size -- input, size of memory required.
 *            
 * Return:    return 0 on success, !0 on error.
 */
//int bufferPrepareSpace(Buffer* buffer, size_t size);

/*
 * Function:  make buffer to have the required memory space, with data to initialize buffer.
 * Arguments:
 *            buff -- input, Buffer.
 *            s    -- input, initial data.
 *            size -- input, size of memory required.
 *            
 * Return:    return 0 on success, !0 on error.
 */
int bufferPrepareLenSpace(Buffer* buffer, const char* s, size_t size);

#ifdef __cplusplus
}
#endif
#endif
