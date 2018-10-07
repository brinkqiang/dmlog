# dmlog

Copyright (c) 2013-2018 brinkqiang (brink.qiang@gmail.com)

[dmlog GitHub](https://github.com/brinkqiang/dmlog)

## Build status
| [Linux][lin-link] | [MacOSX][osx-link] | [Windows][win-link] |
| :---------------: | :----------------: | :-----------------: |
| ![lin-badge]      | ![osx-badge]       | ![win-badge]        |

[lin-badge]: https://travis-ci.org/brinkqiang/dmlog.svg?branch=master "Travis build status"
[lin-link]:  https://travis-ci.org/brinkqiang/dmlog "Travis build status"
[osx-badge]: https://travis-ci.org/brinkqiang/dmlog.svg?branch=master "Travis build status"
[osx-link]:  https://travis-ci.org/brinkqiang/dmlog "Travis build status"
[win-badge]: https://ci.appveyor.com/api/projects/status/github/brinkqiang/dmlog?branch=master&svg=true "AppVeyor build status"
[win-link]:  https://ci.appveyor.com/project/brinkqiang/dmlog "AppVeyor build status"

## Intro
dmlog
```cpp

#include "dmlog.h"
#include "dmtime.h"
int main(int argc, char *argv[]) {

  LOG_INFO("This is a basic logging message.");

  LOG_INFO("This message includes {} substitutions, similar to how {} work.", 2, 
           "printf(), fprintf(), etc.");

  LOG_FATAL("This is a fatal message with magenta coloring.");
  LOG_ERROR("This is an error message with red coloring.");
  LOG_WARN("This is a warning message with orange coloring.");
  LOG_INFO("This is an information message with green coloring.");

  LOG_DEBUG("This is a debugging message (that never gets printed).");

  CDMLog::Instance()->DMLogSetPropLevel(DMLOG_LEVEL_ALL);
  LOG_DEBUG("This is a debugging message with blue coloring.");
  LOG_TRACE("This is a tracing message with cyan coloring.");

  CDMLog::Instance()->DMLogSetPropFilename("demo.log");
  LOG_INFO("This will be printed to the console, as well as \"demo.log\" as its first entry.");

  CDMLog::Instance()->DMLogSetPropStream(DMLOG_STREAM_DISK);
  CDMLog::Instance()->DMLogSetPropRollover(LONG_MAX);
  LOG_INFO("start time: {:%Y-%m-%d %H:%M:%S}", fmt::localtime(time(NULL)));
  for(int i = 0; i < 1000000; i++) {
    LOG_INFO("This message is 116 characters long including the info that comes before it. {}", i);
  }
  LOG_INFO("end time: {:%Y-%m-%d %H:%M:%S}", fmt::localtime(time(NULL)));

  LOG_INFO("This message will cause the file to exceed the rollover value, which triggers it to "
           "be closed and renamed with an incremental number appended to it. A new file with the "
           "original filename is then opened and used in its place.");
  LOG_INFO("This message will be the first message in the new log file.");

  CDMLog::Instance()->DMLogSetPropStream(DMLOG_STREAM_ALL);
  LOG_INFO("This concludes the feature demo for dmlog!");

  return 0;
}

```
## Contacts
[![Join the chat](https://badges.gitter.im/brinkqiang/dmlog/Lobby.svg)](https://gitter.im/brinkqiang/dmlog)

## Thanks
