#include <main.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>

void printHello()
{
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto logger = std::make_shared<spdlog::logger>("MyApp", consoleSink);
    logger->info("HelloWorld");
}

int main()
{
    printHello();
    return 0;
}
