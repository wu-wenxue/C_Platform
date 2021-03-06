#include "platform.h"
#include "logger.h"


void platformInit(PlatForm *platForm)
{
    configInitialize(&platForm->config);

    configLoad(&platForm->config);

    loggerInitialize(&platForm->config.logConfig);
}
