#include "test.h"
#include "http.h"
#include "buffer.h"
#include "logger.h"
#include "errorcode.h"
#include "parson.h"

static char* generateLocationString() {
    char *queryString;
    JSON_Value *jsonValue;
    JSON_Object *jsonObject;

//    configUpdateIMEI(&agent.config, 0);
//    if (agent.config.imei == NULL) {
//        loggerLog(LOG_D, "generateUpgradeString, IMEI null");
//        return NULL;
//    }


    jsonValue = json_value_init_object();
    if (jsonValue == NULL) {
        loggerLog(LOG_D, "generateUpgradeString, create JSON Object failed");
        return NULL;
    }

    jsonObject = json_value_get_object(jsonValue);
    json_object_set_string(jsonObject, "IMEI", "A30120A125B76E");
    json_object_set_string(jsonObject, "ICCID", "8986031742203695812");
    queryString = json_serialize_to_string(jsonValue);
    json_value_free(jsonValue);
    return queryString;
}

short test_location()
{
    char* baseURL = "https://iot-api.chinacloudsites.cn/iot/getLocation";

    loggerLog(LOG_D,"doLocation_byICCID, start ....");
    short ec = EC_ERROR;
    if(NULL == baseURL)
    {
        return ec;
    }
    char* string = generateLocationString();
    if(NULL == string)
    {
        loggerLog(LOG_D,"doLocation_byICCID, generate query string failed");
        return EC_HTTPARGERROR;
    }
    loggerLog(LOG_D,"doLocation_byICCID, query string [%s]", string);
    Buffer buffer;

    bufferInitialize(&buffer);
    ec = httpPost(baseURL,string, &buffer);  // 如果超时，耗时30s
    printf("buffer.data = [%s]\n",buffer.data);
    if (ec == EC_OK) {
//        ec = parseLocation_New(&buffer, position);
    }
//    bufferUnInitialize(&buffer);
    return ec;
}



short test_download()
{
    char* download_url = "http://192.168.1.187/FTP/Beyond.Compare.v3.3.13.18981.exe";

    loggerLog(LOG_D,"test_download, start....");
    short ec = EC_ERROR;
    if(NULL == download_url)
    {
        return ec;
    }

    ec = httpDownload(download_url,"down_test");

}
