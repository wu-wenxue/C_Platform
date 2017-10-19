#include "config.h"
#include "parson.h"
#include <stdlib.h>
#include "logger.h"

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
    const char* cstr;
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



    json_value_free(configValue);
}

