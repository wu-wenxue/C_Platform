#ifndef CONFIG_H
#define CONFIG_H
#ifdef __cplusplus
extern "C" {
#endif
#include "logger.h"

#define CONFIG_FILE "./conf/config.json"


typedef struct
{
    LogConfig logConfig;

}Config;

void  configInitialize(Config *config);
void  configUnInitialize(Config *config);
void  configLoad(Config *config);


#ifdef __cplusplus
}
#endif
#endif // CONFIG_H

