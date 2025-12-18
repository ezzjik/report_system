#ifndef REPORTSYSTEM_LOGGINGDECORATOR_H
#define REPORTSYSTEM_LOGGINGDECORATOR_H

#include "../core/Report.h"

#include <memory>
#include <string>

namespace report_system {

    // Декоратор для логирования операций с отчётом
    class LoggingDecorator: public Report {
    public:
        LoggingDecorator(std::unique_ptr<Report> report, const std::string& log_file_path = "");

        // Переопределение методов Report
        ReportResult generate() override;
        std::string getInfo() const override;

        // Методы для управления логированием
        void setLogFile(const std::string& log_file_path);
        void logMessage(const std::string& message) const;

    private:
        std::unique_ptr<Report> wrapped_report_;
        std::string log_file_path_;

        void logStart() const;
        void logEnd(bool success, const std::string& error_message = "") const;
    };

} // namespace report_system

#endif // REPORTSYSTEM_LOGGINGDECORATOR_H
