/* 
 * Message: source file, HTTP request.
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
#include "http.h"
#include "errorcode.h"
#include "logger.h"
#include <string.h>
#include <curl/curl.h>

static size_t httpWriteResponseBuffer(void* data, size_t size, size_t nmemb, void* stream) {
    size_t length = size*nmemb;
    Buffer *buffer = (Buffer*)stream;
    
    if (buffer == NULL) return -1;
    if (bufferPrepareLenSpace(buffer, data, length) == -1) {
        return -1;
    }
    return length;
}

static size_t httpDownloadHander(void* data, size_t size, size_t nmemb, void* stream) {
    FILE *file = (FILE*)stream;
    
    if (file) {
        return fwrite(data, size, nmemb, file);
    }
    
    return -1;
}

short httpGet(const char* url, Buffer* buffer) {
    short ec = EC_OK;
    long code;
    CURL *curl;
    CURLcode status;
    struct curl_slist *headers;
    
    if (url == NULL) {
        loggerLog(LOG_E, "httpGet, URL null");
        return EC_ARGINVALID;
    }
    curl = curl_easy_init();
    if (curl == NULL) {
        loggerLog(LOG_E, "httpGet, initialize curl failed");
        return EC_OOM;
    }

    headers = curl_slist_append(NULL, "Accept:application/json");
    headers = curl_slist_append(headers, "Content-Type:application/json");
    headers = curl_slist_append(headers, "charset:utf-8");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,30);
    if (buffer) {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, httpWriteResponseBuffer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
    }
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    
    status = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
    if (code == 200 && status == CURLE_OK) {
        ec = EC_OK;
    } else {
        ec = EC_HTTPACCESSERROR;
    }
    loggerLog(LOG_D, "httGet, response(status=%d), code(%ld)", status, code);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return ec;
}

short httpPost(const char* url, const char* arguments, Buffer* buffer) {
    short ec = EC_OK;
    long code;
    CURL *curl;
    CURLcode status;
    struct curl_slist *headers;
    
    if (url == NULL) {
        loggerLog(LOG_D, "httpPost, URL null");
        return EC_ARGINVALID;
    }
    curl = curl_easy_init();
    if (curl == NULL) {
        loggerLog(LOG_D, "httpPost, initialize curl failed");
        return EC_OOM;
    }
    
    headers = curl_slist_append(NULL, "Accept:application/json");
    headers = curl_slist_append(headers, "Content-Type:application/json");
    headers = curl_slist_append(headers, "charset:utf-8");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,30);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    if (arguments) {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, arguments);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(arguments));
    }
    if (buffer) {
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, httpWriteResponseBuffer);
    }
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    
    status = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
    if (code == 200 && status == CURLE_OK) {
        ec = EC_OK;
    } else {
        ec = EC_HTTPACCESSERROR;
    }
    loggerLog(LOG_D, "httpPost, response(status=%d), code(%ld)", status, code);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return ec;
}

short httpDownload(const char* url, const char* file) {
    FILE *fp;
    short ec = EC_OK;
    long code;
    CURL *curl;
    CURLcode status;
    
    if (url == NULL || file == NULL) {
        loggerLog(LOG_D, "httpDownload, arguments null");
        return EC_ARGINVALID;
    }
    fp = fopen(file, "w");
    if (fp== NULL) {
        loggerLog(LOG_D, "httpDownload, create file(%s) failed", file);
        return EC_FILEOPENERROR;
    }
    curl = curl_easy_init();
    if (curl == NULL) {
        fclose(fp);
        loggerLog(LOG_D, "httpDownload, initialize curl failed");
        return EC_HTTPCONNCREATEERROR;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,30); 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, httpDownloadHander);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    
    status = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
    if (!(code == 200 && status == CURLE_OK)) {
        ec = EC_HTTPACCESSERROR;
    }
    loggerLog(LOG_D, "httpDownload, response(status=%d), code(%ld)", status, code);
    curl_easy_cleanup(curl);
    fflush(fp);
    fclose(fp);
    if (ec != EC_OK) {
        remove(file);
        loggerLog(LOG_D, "httpDownload, download failed(%d), remove temp file(%s)", ec, file);
    }
    return ec;
}
