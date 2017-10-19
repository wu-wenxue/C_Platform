/* 
 * Message: header file, HTTP request.
 * 
 * Module: Common
 * 
 * Author:
 *
 * Created 2016.08.10
 * 
 * Update Histories:
 *     None
 */
#ifndef HTTP_H
#define HTTP_H
#ifdef __cplusplus
extern "C" {
#endif

#include "buffer.h"

short httpGet(const char* url, Buffer* buffer);
short httpPost(const char* url, const char* arguments, Buffer* buffer);
short httpDownload(const char* url, const char* file);

#ifdef __cplusplus
}
#endif
#endif
