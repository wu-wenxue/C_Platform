#ifndef CONFIG_H
#define CONFIG_H
#ifdef __cplusplus
extern "C" {
#endif

#define CONFIG_FILE ""

typedef struct
{
    char* logFilePath;
    int logLevel;
}Config;

void  configInitialize(Config *config);
void  configUnInitialize(Config *config);
void  configLoad(Config *config);


#ifdef __cplusplus
}
#endif
#endif // CONFIG_H

