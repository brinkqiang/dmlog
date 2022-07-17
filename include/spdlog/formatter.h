//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __FORMATTER_H__
#define __FORMATTER_H__

#pragma once

#include "dmformat.h"
#include "spdlog/details/log_msg.h"

namespace spdlog {

    class formatter
    {
    public:
        virtual ~formatter() = default;
        virtual void format(const details::log_msg& msg, fmt::memory_buffer& dest) = 0;
        virtual std::unique_ptr<formatter> clone() const = 0;
    };
} // namespace spdlog


#endif // __FORMATTER_H__
