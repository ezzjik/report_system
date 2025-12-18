#ifndef REPORTSYSTEM_REPORTBUILDER_H
#define REPORTSYSTEM_REPORTBUILDER_H

#include "../core/Report.h"
#include "../core/DataProvider.h"
#include "../core/DataProcessor.h"
#include "../core/Formatter.h"
#include "../core/ExportStrategy.h"

#include <memory>
#include <vector>

namespace report_system {

    // Строитель для пошагового создания отчётов
    class ReportBuilder {
    public:
        ReportBuilder() = default;

        // Установить источник данных
        ReportBuilder& setDataSource(std::unique_ptr<DataProvider> provider);

        // Добавить обработчик данных
        ReportBuilder& addProcessor(std::unique_ptr<DataProcessor> processor);

        // Установить форматировщик
        ReportBuilder& setFormatter(std::unique_ptr<Formatter> formatter);

        // Установить стратегию экспорта
        ReportBuilder& setExportStrategy(std::unique_ptr<ExportStrategy> exporter);

        // Построить отчёт
        std::unique_ptr<Report> build();

    private:
        std::unique_ptr<DataProvider> data_provider_;
        std::vector<std::unique_ptr<DataProcessor>> processors_;
        std::unique_ptr<Formatter> formatter_;
        std::unique_ptr<ExportStrategy> export_strategy_;
    };

} // namespace report_system

#endif // REPORTSYSTEM_REPORTBUILDER_H
