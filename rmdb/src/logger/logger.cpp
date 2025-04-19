#include "logger.h"

void setup_logger() {
    // 日志文件路径和文件大小限制
    std::string log_dir = "logs/";
    std::string log_filename = log_dir + "log.txt";  // 日志按日期切分
    
    auto file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(log_filename, 0, 0);
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>(spdlog::color_mode::always);
    file_sink->set_level(spdlog::level::trace);
    console_sink->set_level(spdlog::level::warn);

    auto sinks = std::vector<spdlog::sink_ptr>{file_sink, console_sink};
    

    spdlog::flush_every(std::chrono::seconds(1));
    spdlog::flush_on(spdlog::level::debug);

    // 创建多线程日志记录器
    spdlog::init_thread_pool(8192, 1);
    auto logger = std::make_shared<spdlog::async_logger>("global_logger", sinks.begin(), sinks.end(), spdlog::thread_pool());
    logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%^%l%$] %v");
    spdlog::set_default_logger(logger);
}