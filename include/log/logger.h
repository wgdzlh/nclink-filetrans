
#ifndef __LOGGER_H_
#define __LOGGER_H_

#include <stddef.h>
#include "elog.h"
extern int LoggerInit(const char *logFile, int maxSize,int LoggerLevel);
extern void LoggerDeinit();
typedef enum{
    Log_Level_Assert=0,
    Log_Level_Error,
    Log_Level_Warn,
    Log_Level_Info,
    Log_Level_Debug,
    Log_Level_Verbose
}LogLevel; 

extern int LoggerLevel;
extern int LoggerInited;
extern void LogDeinit();

#define Log_V(tag, ...) {   \
        if(LoggerInited)elog_v(tag, ##__VA_ARGS__);   \
}
#define Log_D(tag, ...) {   \
        if(LoggerInited)elog_d(tag, ##__VA_ARGS__);   \
}
#define Log_I(tag, ...) {   \
        if(LoggerInited)elog_i(tag, ##__VA_ARGS__);   \
}
#define Log_W(tag, ...) {   \
        if(LoggerInited)elog_w(tag, ##__VA_ARGS__);   \
}
#define Log_E(tag, ...) {   \
        if(LoggerInited)elog_e(tag, ##__VA_ARGS__);   \
}
#define Log_A(tag, ...) {   \
        if(LoggerInited)elog_a(tag, ##__VA_ARGS__);   \
}

#ifndef LOGGER_TAG
#define LOGGER_TAG __FILE__
#endif

#define LOG_A(...) {    \
    Log_A(LOGGER_TAG,log, ##__VA_ARGS__);\
}
#define LOG_E(...) {    \
    if(LoggerLevel>=Log_Level_Error)Log_E(LOGGER_TAG, ##__VA_ARGS__);\
}
#define LOG_W(...) {    \
    if(LoggerLevel>=Log_Level_Warn)Log_W(LOGGER_TAG, ##__VA_ARGS__);\
}
#define LOG_I(...) {    \
    if(LoggerLevel>=Log_Level_Info)Log_I(LOGGER_TAG, ##__VA_ARGS__);\
}
#define LOG_D(...) {    \
    if(LoggerLevel>=Log_Level_Debug)Log_D(LOGGER_TAG,##__VA_ARGS__);\
}
#define LOG_V(...) {    \
    if(LoggerLevel>=Log_Level_Verbose)Log_V(LOGGER_TAG, ##__VA_ARGS__);\
}

#endif //__LOGGER_H_
