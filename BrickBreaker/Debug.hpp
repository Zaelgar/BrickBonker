// Found and added to, from https://learnmoderncpp.com/2020/02/10/writing-assert-in-cpp/

#pragma once

#include <exception>
#include <iostream>
#include <string_view>

constexpr bool ReleaseBuild = false;
constexpr bool AssertionsBuild = true;
constexpr bool EnableLogging = true;

template<typename T, typename E = std::exception>
inline void ASSERT(T&& assertion, const E throwing = {})
{
    if constexpr (AssertionsBuild)
    {
        if (!assertion)
        {
            throw throwing;
        }
    }
}

template<typename T>
inline void LOGERROR(T&& assertion,
    const std::string_view log_msg = {},
    std::ostream& out = std::cerr,
    const char* file = __FILE__,
    const int line = __LINE__)
{
    if constexpr (!ReleaseBuild)
    {
        if (!assertion)
        {
            out << file << '(' << line << "): *** assertion failed: " << log_msg << std::endl;
        }
    }
}

inline void LOG(std::string_view log_msg = {})
{
    if constexpr (EnableLogging)
    {
        std::cout << log_msg << std::endl;
    }
}