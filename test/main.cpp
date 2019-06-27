#include "dmlog.h"

int main(int argc, char *argv[])
{
    DMBench oBench;
    LOG_CRITICAL("hello world {}.", 2019);
    LOG_INFO("This is a basic logging message.");

    LOG_INFO("This message includes {} substitutions, similar to how {} work.", 2,
        "printf(), fprintf(), etc.");

    LOG_INFO("message test start");
    for (int i = 0; i < 1000000; i++) {
        oBench++;
        LOG_INFO("This message is 116 characters long including the info that comes before it. {}", i);
    }
    LOG_INFO("message test end");
    LOG_INFO("This message will cause the file to exceed the rollover value, which triggers it to "
        "be closed and renamed with an incremental number appended to it. A new file with the "
        "original filename is then opened and used in its place.");
    LOG_INFO("This message will be the first message in the new log file.");

    LOG_INFO("This concludes the feature demo for dmlog!");
    return 0;
}