#include "dmlog.h"


static const char *simpleFormat = "%s %s %-5s (%s:%d): ";
static const char *coloredFormat = "%s %s %s%-5s%s %s(%s:%d)%s: ";
static const char *colorBlack = "\x1b[90m";
static const char *colorReset = "\x1b[0m";
static const char *levels[] = {
  "FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE"
};
static const char *colors[] = {
  "\x1b[95m", "\x1b[91m", "\x1b[93m", "\x1b[92m", "\x1b[94m", "\x1b[96m"
};

CDMLog::CDMLog()
{
    DMLogInitProps();
}

CDMLog::~CDMLog()
{
    DMLogResetProps();
}

void CDMLog::DMLogInitProps() {
  logProps.level = DMLOG_LEVEL_INFO;
  logProps.stream = DMLOG_STREAM_ALL;
  logProps.color = DMLOG_COLOR_ON;
  logProps.rollover = LONG_MAX;
  logProps.filename = NULL;
  fp = NULL;
  currRolloverAppend = 1;
  currLogLen = 0;
}

void CDMLog::DMLogLoadProps(DMLogProps props) {
  if(fp != NULL) {
    fclose(fp);
  }
  logProps.level = props.level;
  logProps.stream = props.stream;
  logProps.color = props.color;
  logProps.rollover = props.rollover;
  logProps.filename = props.filename;
  //TODO: error: handling
  fp = fopen(logProps.filename, "a");
  currRolloverAppend = 1;
  currLogLen = 0;
}

void CDMLog::DMLogResetProps() {
  if(fp != NULL) {
    fclose(fp);
  }
  DMLogInitProps();
}

void CDMLog::DMLogSetPropLevel(DMLogLevels level) {
  logProps.level = level;
}

DMLogLevels CDMLog::DMLogGetPropLevel() {
  return logProps.level;
}

void CDMLog::DMLogSetPropStream(DMLogStreams stream) {
  logProps.stream = stream;
}

DMLogStreams CDMLog::DMLogGetPropStream() {
  return logProps.stream;
}

void CDMLog::DMLogSetPropColor(DMLogColor color) {
  logProps.color = color;
}

DMLogColor CDMLog::DMLogGetPropColor() {
  return logProps.color;
}

void CDMLog::DMLogSetPropRollover(long rollover) {
  if(rollover < 1024) {
    logProps.rollover = 1024;
  }
  else if(rollover > LONG_MAX) {
    logProps.rollover = LONG_MAX;
  }
  else {
    logProps.rollover = rollover;
  }
}

long CDMLog::DMLogGetPropRollover() {
  return logProps.rollover;
}

void CDMLog::DMLogSetPropFilename(char *filename) {
  logProps.filename = filename;
}

char *CDMLog::DMLogGetPropFilename() {
  return logProps.filename;
}

void CDMLog::DMLog(DMLogMsgLevels level, const char *srcFilename, int srcLine, const std::string &message) {
  // Only consider logging if the message's level is within the global level bound
  if(logProps.level >= (DMLogLevels)level) {
    // Only print to the console if enabled
    if(logProps.stream == DMLOG_STREAM_ALL || logProps.stream == DMLOG_STREAM_CONSOLE) {
      FILE *cp;
      // Print to either stdout or stderr depending on the level given for this message
      if(level == DMLOG_MSG_LEVEL_ERROR || level == DMLOG_MSG_LEVEL_FATAL) {
        cp = stderr;
      }
      else {
        cp = stdout;
      }

      // Only use colored console printing if enabled
      if(logProps.color == DMLOG_COLOR_ON) {
        fprintf(cp, coloredFormat, __DATE__, __TIME__, colors[level], levels[level], 
                colorReset, colorBlack, srcFilename, srcLine, colorReset);
      }
      else {
        fprintf(cp, simpleFormat, __DATE__, __TIME__, levels[level], srcFilename, srcLine);
      }

      // Print the logging message along with any option parameters

      fprintf(cp, message.c_str());

      fprintf(cp, "\n");
      fflush(cp);
    }

    // Only print to the file pointer if one was provided
    if(logProps.stream == DMLOG_STREAM_ALL || logProps.stream == DMLOG_STREAM_DISK) {
      // Make sure a valid filename was actually provided
      if(logProps.filename != NULL) {
        // Open the file pointer if it wasn't open already
        if(fp == NULL) {
          fp = fopen(logProps.filename, "a");
          currLogLen = ftell(fp);
        }

        // Print the logging message along with any option parameters
        currLogLen += fprintf(fp, simpleFormat, __DATE__, __TIME__, levels[level], srcFilename, 
                              srcLine);
        currLogLen += fprintf(fp, message.c_str());
        currLogLen += fprintf(fp, "\n");
        fflush(fp);

        // Perform log rollover if necessary
        if(logProps.rollover < (int)currLogLen) {
          int len = (int)strlen(logProps.filename);
          char rolledFilename[260];
          FILE *tp;

          while(1) {
            //TODO: edge case where restarting program after 10 or more rolls have occurred, buffer size
            sprintf(rolledFilename, "%s.%d", logProps.filename, currRolloverAppend);
            tp = fopen(rolledFilename, "r");
            if(tp != NULL) {
              fclose(tp);
              currRolloverAppend++;
            }
            else {
              break;
            }
          }
          fclose(fp);
          rename(logProps.filename, rolledFilename);
          fp = fopen(logProps.filename, "a");
          currRolloverAppend++;
          currLogLen = 0;
        }
      }
    }
  }
}