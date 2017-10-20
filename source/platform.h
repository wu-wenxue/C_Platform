#ifndef PLARFORM_H
#define PLARFORM_H
#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"

typedef struct
{
    Config config;
}PlatForm;

void platformInit(PlatForm* platForm);

#ifdef __cplusplus
}
#endif
#endif // PLARFORM_H

