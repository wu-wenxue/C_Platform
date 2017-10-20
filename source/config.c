#include "config.h"
#include "parson.h"
#include <stdlib.h>
#include "logger.h"
#include "utility.h"

void configInitialize(Config *config)
{
    memset(config,0,sizeof(Config));


}

void configUnInitialize(Config *config)
{
    if (config == NULL) return;

    memset(config,0,sizeof(Config));

}

void configLoad(Config *config)
{
    const char* cstr = NULL;
    int value = 0;
    JSON_Value* configValue;
    JSON_Object* configObject;

    if(NULL == config)
    {
        return;
    }

    configValue = json_parse_file(CONFIG_FILE);
    if(NULL == configValue)
    {
        loggerLog(LOG_E,"configLoad: parse json-file=[%s] failed",CONFIG_FILE);
        return;
    }

    configObject = json_value_get_object(configValue);
    if(NULL == configObject)
    {
        loggerLog(LOG_E,"configLoad, json data inviled");
        json_value_free(configValue);
        return;
    }

    cstr = json_object_get_string(configObject,"logLevel");
    if(NULL != cstr && strlen(cstr) > 0)
    {
        config->logConfig.logLevel = loggerGetLevel(cstr);
    }

    value = json_object_get_number(configObject,"logFileMaxSize");
    if(0 != value)
    {
        config->logConfig.logFileMaxSize = value * 1024;
    }

    cstr = json_object_get_string(configObject,"logFile");
    if(NULL != cstr && strlen(cstr) > 0)
    {
        config->logConfig.logFile = stringCopy(cstr);
    }

    value = json_object_get_number(configObject,"singleLogMaxSize");
    if(0 != value)
    {
        config->logConfig.singleLogSize = value;
    }


    json_value_free(configValue);
}

