#ifndef REPORTSYSTEM_REPORT_H
#define REPORTSYSTEM_REPORT_H

#include "ExportStrategy.h"
#include "DataProcessor.h"

#include <memory>
#include <string>
#include <vector>

namespace report_system {

    // Результат генерации отчёта
    struct ReportResult {
        bool success{false};
        std::string error_message;
        std::string generated_content;
        std::string export_destination;

        explicit operator bool() const {
            return success;
        }
    };

    // Основной класс отчёта
    class Report {
    public:
        Report(std::unique_ptr<DataProvider> provider,
               std::vector<std::unique_ptr<DataProcessor>> processors,
               std::unique_ptr<Formatter> formatter,
               std::unique_ptr<ExportStrategy> exporter);

        virtual ~Report() = default;

        // Сгенерировать отчёт
        virtual ReportResult generate();

        // Получить информацию об отчёте
        virtual std::string getInfo() const;

    protected:
        // Защищенный конструктор для декораторов
        Report() = default;

    private:
        std::unique_ptr<DataProvider> data_provider_;
        std::vector<std::unique_ptr<DataProcessor>> processors_;
        std::unique_ptr<Formatter> formatter_;
        std::unique_ptr<ExportStrategy> export_strategy_;
    };

} // namespace report_system

#endif // REPORTSYSTEM_REPORT_H
