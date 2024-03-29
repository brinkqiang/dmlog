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
