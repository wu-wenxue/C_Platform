/* 
 * Message: source file, buffer.
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
#include "buffer.h"
#include "errorcode.h"
#include "common.h"
#include "logger.h"

void bufferInitialize(Buffer* buffer) {
    if (buffer == NULL) return;
    buffer->used = 0;
    buffer->avaliable = 0;
    buffer->data = NULL;
}

void bufferReset(Buffer* buffer) {
    if (buffer == NULL) return;
    if (buffer->data) free(buffer->data);
    buffer->used = 0;
    buffer->avaliable = 0;
    buffer->data = NULL;
}

//int bufferPrepareSpace(Buffer* buffer, size_t size) {
//    char *data;
//    
//    if (buffer == NULL) return -1;
//    data = watcher_realloc(buffer->data, buffer->used + size+1);
//    if (data == NULL) return -1;
//    buffer->data = data;
//    memset(buffer->data+buffer->used, 0, size+1);
//    buffer->avaliable = size;
//    return 0;
//}

int bufferPrepareLenSpace(Buffer* buffer, const char* s, size_t size) {
    char *data;
    
    if (buffer == NULL) return -1;
    data = realloc(buffer->data, buffer->used + size+1);
    if (data == NULL) return -1;
    buffer->data = data;
    if (s) {
        memcpy(buffer->data+buffer->used, s, size);
        buffer->used += size;
        buffer->data[buffer->used] = '\0';
        buffer->avaliable = 0;
    } else {
        memset(buffer->data+buffer->used, 0, size+1);
        buffer->avaliable = size;
    }
    
    return 0;
}
