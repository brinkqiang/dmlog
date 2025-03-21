
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __DMLOG_H__
#define __DMLOG_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdarg.h>

#include <chrono>

#include "dmutil.h"
#include "dmformat.h"
#include "dmchrono.h"
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/details/console_globals.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

#define LOG_CRITICAL(...) CDMLog::Instance()->GetLogger()->log(spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, SPDLOG_FUNCTION}, spdlog::level::level_enum::critical, __VA_ARGS__)
#define LOG_ERROR(...) CDMLog::Instance()->GetLogger()->log(spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, SPDLOG_FUNCTION}, spdlog::level::level_enum::err, __VA_ARGS__)
#define LOG_WARN(...)  CDMLog::Instance()->GetLogger()->log(spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, SPDLOG_FUNCTION}, spdlog::level::level_enum::warn, __VA_ARGS__)
#define LOG_INFO(...)  CDMLog::Instance()->GetLogger()->log(spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, SPDLOG_FUNCTION}, spdlog::level::level_enum::info, __VA_ARGS__)
#define LOG_DEBUG(...) CDMLog::Instance()->GetLogger()->log(spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, SPDLOG_FUNCTION}, spdlog::level::level_enum::debug, __VA_ARGS__)
#define LOG_TRACE(...) CDMLog::Instance()->GetLogger()->log(spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, SPDLOG_FUNCTION}, spdlog::level::level_enum::trace, __VA_ARGS__)

class CDMLog
{
public:
    CDMLog()
    {
        std::string strPath = DMGetRootPath() + "/logs";
        std::string strFile = DMGetRootPath() + "/logs/" + DMGetExeName() + ".log";
        DMCreateDirectories((DMGetRootPath() + "/logs").c_str());

        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::warn);
        console_sink->set_pattern("[%Y-%m-%d %H:%M:%S %f] [%@][%t][%l] %v");

        auto daily_logger = std::make_shared<spdlog::sinks::daily_file_sink_mt>(strFile,
            2, 30);
        daily_logger->set_level(spdlog::level::trace);
        daily_logger->set_pattern("[%Y-%m-%d %H:%M:%S %f] [%@][%t][%l] %v");

        //auto rotating_logger = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(strFile, 5 * 1024 * 1024, 7);
        //rotating_logger->set_level(spdlog::level::trace);
        //rotating_logger->set_pattern("[%Y-%m-%d %H:%M:%S %f] [%@][%t][%l] %v");

        //spdlog::logger logger(DMGetExeName(), {console_sink, daily_logger , rotating_logger});
        spdlog::logger logger(DMGetExeName(), { console_sink, daily_logger});

        my_logger = logger.clone(DMGetExeName());

        my_logger->flush_on(spdlog::level::warn);

        spdlog::flush_every(std::chrono::seconds(0));
    }
    ~CDMLog()
    {
        spdlog::drop_all();
    }

    static CDMLog* Instance()
    {
        static CDMLog s_oT;
        return &s_oT;
    }

    inline std::shared_ptr<spdlog::logger> GetLogger()
    {
        return my_logger;
    }

private:
    std::shared_ptr<spdlog::logger> my_logger;
};

#define DMLOG_INIT() CDMLog::Instance()


struct DMLogTimer
{
    DMLogTimer() : tp(std::chrono::system_clock::now()) {}
    virtual ~DMLogTimer()
    {
        auto dur = std::chrono::system_clock::now() - tp;
        LOG_DEBUG("Cost {} ms", std::chrono::duration_cast<std::chrono::milliseconds>
            (dur).count());
    }
    std::chrono::system_clock::time_point tp;
};

struct DMBench : public DMLogTimer
{
    DMBench() : val(0) {}
    virtual ~DMBench()
    {
        stop();
    }
    inline void stop()
    {
        auto dur = std::chrono::system_clock::now() - tp;
        LOG_DEBUG("Per op: {} ns",
            std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count() / std::max(
                val, (uint64_t)1));
        auto perf = (double)val / std::chrono::duration_cast<std::chrono::milliseconds>
            (dur).count() / 10;

        if (perf < 1)
        {
            LOG_DEBUG("Performance: {:03.2f}  w/s", perf);
        }
        else
        {
            LOG_DEBUG("Performance: {} w/s", perf);
        }
    }
    DMBench& operator++()
    {
        ++val;
        return *this;
    }
    DMBench& operator++(int)
    {
        ++val;
        return *this;
    }
    DMBench& operator+=(uint64_t v)
    {
        val += v;
        return *this;
    }
    DMBench& add(uint64_t v)
    {
        val += v;
        return *this;
    }
    uint64_t val;
};



#endif // __DMLOG_H__
