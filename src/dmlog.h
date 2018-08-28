#ifndef __DMLOG_H__
#define __DMLOG_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdarg.h>

#define LOG_FATAL(...) CDMLog::Instance()->DMLog(DMLOG_MSG_LEVEL_FATAL, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) CDMLog::Instance()->DMLog(DMLOG_MSG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...)  CDMLog::Instance()->DMLog(DMLOG_MSG_LEVEL_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)  CDMLog::Instance()->DMLog(DMLOG_MSG_LEVEL_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) CDMLog::Instance()->DMLog(DMLOG_MSG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_TRACE(...) CDMLog::Instance()->DMLog(DMLOG_MSG_LEVEL_TRACE, __FILE__, __LINE__, __VA_ARGS__)

#define LOG(level, ...) CDMLog::Instance()->DMLog(level, __FILE__, __LINE__, __VA_ARGS__)

typedef enum dmlog_levels_e {
  DMLOG_LEVEL_OFF   = -1,
  DMLOG_LEVEL_FATAL = 0,
  DMLOG_LEVEL_ERROR = 1,
  DMLOG_LEVEL_WARN  = 2,
  DMLOG_LEVEL_INFO  = 3,
  DMLOG_LEVEL_DEBUG = 4,
  DMLOG_LEVEL_TRACE = 5,
  DMLOG_LEVEL_ALL   = DMLOG_LEVEL_TRACE
} DMLogLevels;

typedef enum dmlog_streams_e {
  DMLOG_STREAM_OFF     = 0,
  DMLOG_STREAM_CONSOLE = 1,
  DMLOG_STREAM_DISK    = 2,
  DMLOG_STREAM_ALL     = 3
} DMLogStreams;

typedef enum dmlog_color_e {
    DMLOG_COLOR_OFF = 0,
    DMLOG_COLOR_ON = 1
} DMLogColor;

typedef struct dmlog_props_s {
  DMLogLevels level;
  DMLogStreams   stream;
  DMLogColor     color;
  long        rollover;
  char *      filename;
} DMLogProps;

typedef enum dmlog_msg_levels_e {
    DMLOG_MSG_LEVEL_FATAL = DMLOG_LEVEL_FATAL,
    DMLOG_MSG_LEVEL_ERROR = DMLOG_LEVEL_ERROR,
    DMLOG_MSG_LEVEL_WARN = DMLOG_LEVEL_WARN,
    DMLOG_MSG_LEVEL_INFO = DMLOG_LEVEL_INFO,
    DMLOG_MSG_LEVEL_DEBUG = DMLOG_LEVEL_DEBUG,
    DMLOG_MSG_LEVEL_TRACE = DMLOG_LEVEL_TRACE
} DMLogMsgLevels;


class CDMLog
{
public:
    CDMLog();
    ~CDMLog();

    static CDMLog* Instance() {
        static CDMLog s_oT;
        return &s_oT;
    }

    void DMLogInitProps();

    void DMLogLoadProps(DMLogProps props);

    void DMLogResetProps();

    void DMLogSetPropLevel(DMLogLevels level);

    DMLogLevels DMLogGetPropLevel();

    void DMLogSetPropStream(DMLogStreams stream);

    DMLogStreams DMLogGetPropStream();

    void DMLogSetPropColor(DMLogColor color);

    DMLogColor DMLogGetPropColor();

    void DMLogSetPropRollover(long rollover);

    long DMLogGetPropRollover();

    void DMLogSetPropFilename(char *filename);

    char *DMLogGetPropFilename();

    void DMLog(DMLogMsgLevels level, const char *srcFilename, int srcLine, const char *message, ...);
private:
    DMLogProps logProps;
    FILE *fp;
    int currRolloverAppend;
    unsigned long currLogLen;
};


#endif // __DMLOG_H__