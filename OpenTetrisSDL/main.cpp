#include "Game.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <ctime>
std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &time);
#elif __linux__
    localtime_r(&tm, &time);
#else
    spdlog::error("Не поддерживаемая операционная система");
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
    return oss.str();
}
void createLogDirectory(const std::string& path) {
    std::filesystem::path logPath(path);
    if (!std::filesystem::exists(logPath)) {
        std::filesystem::create_directories(logPath);
    }
}
int main(int argc, char* argv[]) {
    setlocale(0,"Russian");
    system("chcp 1251");
#if Log_To_File
    std::string logDir = "logs";
    createLogDirectory(logDir);
    std::string dateTime = getCurrentDateTime();
    std::string logFileName = logDir + "/log_" + dateTime + ".txt";
    auto file_logger = spdlog::basic_logger_mt("file_logger", logFileName);
    spdlog::set_default_logger(file_logger);
    spdlog::set_level(spdlog::level::info);
#endif

    

    std::shared_ptr<Settings> settings = std::make_shared<Settings>();
    settings->LoadFromJson();
    Game* game = new Game(settings);
    game->run();
    delete game;
    return 0;
}