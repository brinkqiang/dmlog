# dmlog

Copyright (c) 2013-2018 brinkqiang (brink.qiang@gmail.com)

[![dmlog](https://img.shields.io/badge/brinkqiang-dmlog-blue.svg?style=flat-square)](https://github.com/brinkqiang/dmlog)
[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://github.com/brinkqiang/dmlog/blob/master/LICENSE)
[![blog](https://img.shields.io/badge/Author-Blog-7AD6FD.svg)](https://brinkqiang.github.io/)
[![Open Source Love](https://badges.frapsoft.com/os/v3/open-source.png)](https://github.com/brinkqiang)
[![GitHub stars](https://img.shields.io/github/stars/brinkqiang/dmlog.svg?label=Stars)](https://github.com/brinkqiang/dmlog) 
[![GitHub forks](https://img.shields.io/github/forks/brinkqiang/dmlog.svg?label=Fork)](https://github.com/brinkqiang/dmlog)

## Build status
| [Linux][lin-link] | [Mac][mac-link] | [Windows][win-link] |
| :---------------: | :----------------: | :-----------------: |
| ![lin-badge]      | ![mac-badge]       | ![win-badge]        |

[lin-badge]: https://github.com/brinkqiang/dmlog/workflows/linux/badge.svg "linux build status"
[lin-link]:  https://github.com/brinkqiang/dmlog/actions/workflows/linux.yml "linux build status"
[mac-badge]: https://github.com/brinkqiang/dmlog/workflows/mac/badge.svg "mac build status"
[mac-link]:  https://github.com/brinkqiang/dmlog/actions/workflows/mac.yml "mac build status"
[win-badge]: https://github.com/brinkqiang/dmlog/workflows/win/badge.svg "win build status"
[win-link]:  https://github.com/brinkqiang/dmlog/actions/workflows/win.yml "win build status"

## Intro
dmlog based on spdlog
```cpp
#include "dmlog.hpp"
#include "dmutil.h"
int main(int argc, char* argv[])
{
    DMBench oBench;
    LOG_CRITICAL("hello world {}.", 2019);
    LOG_CRITICAL("It is {:%Y-%m-%d %H:%M:%S}\n", fmt::localtime(time(NULL)));
    for (int i = 0; i < 1000; i++) {
        oBench++;
        LOG_INFO("This message is 116 characters long including the info that comes before it. {}", i);
    }

    LOG_CRITICAL("This concludes the feature demo for dmlog!");
    return 0;
}
```
## Contacts

## Thanks
