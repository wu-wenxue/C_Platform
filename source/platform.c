#include "platform.h"


void platformInit(PlatForm *platForm)
{
    configInitialize(&platForm->config);

    configLoad(&platForm->config);
}
