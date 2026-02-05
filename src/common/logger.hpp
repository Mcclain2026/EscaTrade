#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

namespace EscaTrade {
    class Log {
    public:
        static void Init() {
            spdlog::init_thread_pool(8192, 1);
            auto console_sink{ std::make_shared<spdlog::sinks::stdout_color_sink_mt>() };
            auto logger{ std::make_shared<spdlog::async_logger>(
                "EscaLogger",
                console_sink,
                spdlog::thread_pool(),
                spdlog::async_overflow_policy::block) };
            spdlog::set_default_logger(logger);
            spdlog::set_pattern("[%T.%e] [%^%l%$] %v");
            spdlog::set_level(spdlog::level::debug);
        }
    };
}

#ifdef NDEBUG
    #define ESCA_DEBUG(...) ((void)0)
#else
    #define ESCA_DEBUG(...) spdlog::debug(__VA_ARGS__)
#endif

#define ESCA_INFO(...)  spdlog::info(__VA_ARGS__)
#define ESCA_ERROR(...) spdlog::error(__VA_ARGS__)