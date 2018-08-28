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


/*** Start of inlined file: dmlog.cpp ***/

/*** Start of inlined file: dmlog.h ***/
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


/*** Start of inlined file: dmlog.cpp ***/
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
  logProps.rollover = 8388608;
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

void CDMLog::DMLog(DMLogMsgLevels level, const char *srcFilename, int srcLine, const char *message, ...) {
  // Only consider logging if the message's level is within the global level bound
  if(logProps.level >= (DMLogLevels)level) {
	// Only print to the console if enabled
	if(logProps.stream == DMLOG_STREAM_ALL || logProps.stream == DMLOG_STREAM_CONSOLE) {
	  FILE *cp;
	  va_list args;

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
	  va_start(args, message);
	  vfprintf(cp, message, args);
	  va_end(args);
	  fprintf(cp, "\n");
	  fflush(cp);
	}

	// Only print to the file pointer if one was provided
	if(logProps.stream == DMLOG_STREAM_ALL || logProps.stream == DMLOG_STREAM_DISK) {
	  va_list args;

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
		va_start(args, message);
		currLogLen += vfprintf(fp, message, args);
		va_end(args);
		currLogLen += fprintf(fp, "\n");
		fflush(fp);

		// Perform log rollover if necessary
		if(logProps.rollover < currLogLen) {
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
/*** End of inlined file: dmlog.cpp ***/

#endif // __DMLOG_H__
/*** End of inlined file: dmlog.h ***/

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
  logProps.rollover = 8388608;
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

void CDMLog::DMLog(DMLogMsgLevels level, const char *srcFilename, int srcLine, const char *message, ...) {
  // Only consider logging if the message's level is within the global level bound
  if(logProps.level >= (DMLogLevels)level) {
	// Only print to the console if enabled
	if(logProps.stream == DMLOG_STREAM_ALL || logProps.stream == DMLOG_STREAM_CONSOLE) {
	  FILE *cp;
	  va_list args;

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
	  va_start(args, message);
	  vfprintf(cp, message, args);
	  va_end(args);
	  fprintf(cp, "\n");
	  fflush(cp);
	}

	// Only print to the file pointer if one was provided
	if(logProps.stream == DMLOG_STREAM_ALL || logProps.stream == DMLOG_STREAM_DISK) {
	  va_list args;

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
		va_start(args, message);
		currLogLen += vfprintf(fp, message, args);
		va_end(args);
		currLogLen += fprintf(fp, "\n");
		fflush(fp);

		// Perform log rollover if necessary
		if(logProps.rollover < currLogLen) {
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
/*** End of inlined file: dmlog.cpp ***/

#endif // __DMLOG_H__
