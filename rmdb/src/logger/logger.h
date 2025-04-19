#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/async.h>

void setup_logger();

#define LOG_TRACE(...) spdlog::trace("[{}] {}", __FUNCTION__, fmt::format(__VA_ARGS__))
#define LOG_DEBUG(...) spdlog::debug("[{}] {}", __FUNCTION__, fmt::format(__VA_ARGS__))
#define LOG_INFO(...)  spdlog::info("[{}] {}", __FUNCTION__, fmt::format(__VA_ARGS__))
#define LOG_WARN(...)  spdlog::warn("[{}] {}", __FUNCTION__, fmt::format(__VA_ARGS__))
#define LOG_ERROR(...) spdlog::error("[{}] {}", __FUNCTION__, fmt::format(__VA_ARGS__))
#define LOG_CRITICAL(...) spdlog::critical("[{}] {}", __FUNCTION__, fmt::format(__VA_ARGS__))
