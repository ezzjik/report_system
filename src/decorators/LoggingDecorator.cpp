#include "decorators/LoggingDecorator.h"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace report_system {

    LoggingDecorator::LoggingDecorator(std::unique_ptr<Report> report, const std::string& log_file_path)
        : wrapped_report_(std::move(report))
        , log_file_path_(log_file_path) {
    }

    ReportResult LoggingDecorator::generate() {
        logStart();

        auto start_time = std::chrono::high_resolution_clock::now();
        ReportResult result = wrapped_report_->generate();
        auto end_time = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        logEnd(result.success, result.error_message);

        // Добавляем информацию о времени выполнения
        std::stringstream ss;
        ss << " [Execution time: " << duration.count() << " ms]";
        if (result.success) {
            result.generated_content += ss.str();
        }

        return result;
    }

    std::string LoggingDecorator::getInfo() const {
        std::string wrapped_info = wrapped_report_->getInfo();
        return "LoggingDecorator wrapping:\n" + wrapped_info;
    }

    void LoggingDecorator::setLogFile(const std::string& log_file_path) {
        log_file_path_ = log_file_path;
    }

    void LoggingDecorator::logMessage(const std::string& message) const {
        if (log_file_path_.empty()) {
            return;
        }

        try {
            std::ofstream log_file(log_file_path_, std::ios_base::app);
            if (log_file.is_open()) {
                auto now = std::chrono::system_clock::now();
                auto time_t_now = std::chrono::system_clock::to_time_t(now);

                log_file << std::put_time(std::localtime(&time_t_now), "%Y-%m-%d %H:%M:%S");
                log_file << " - " << message << std::endl;
            }
        } catch (const std::exception&) {
            // Игнорируем ошибки логирования
        }
    }

    void LoggingDecorator::logStart() const {
        std::string message = "Starting report generation: " + wrapped_report_->getInfo();
        logMessage(message);
    }

    void LoggingDecorator::logEnd(bool success, const std::string& error_message) const {
        std::string message = "Report generation ";
        message += success ? "completed successfully" : "failed";
        if (!error_message.empty()) {
            message += ": " + error_message;
        }
        logMessage(message);
    }

} // namespace report_system
