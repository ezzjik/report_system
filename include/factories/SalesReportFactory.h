#ifndef REPORTSYSTEM_SALESREPORTFACTORY_H
#define REPORTSYSTEM_SALESREPORTFACTORY_H

#include "ReportFactory.h"
#include "../data_providers/CsvDataProvider.h"
#include "../data_processors/FilterProcessor.h"
#include "../formatters/HtmlFormatter.h"
#include "../export_strategies/FileExportStrategy.h"

#include <memory>

namespace report_system {

    // Конкретная фабрика для отчётов о продажах
    class SalesReportFactory: public ReportFactory {
    public:
        SalesReportFactory() = default;

        // Реализация фабричных методов
        std::unique_ptr<DataProvider> createDataProvider() override;
        std::unique_ptr<DataProcessor> createDataProcessor() override;
        std::unique_ptr<Formatter> createFormatter() override;
        std::unique_ptr<ExportStrategy> createExportStrategy() override;
    };

} // namespace report_system

#endif // REPORTSYSTEM_SALESREPORTFACTORY_H
