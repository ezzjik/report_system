#ifndef REPORTSYSTEM_REPORTFACTORY_H
#define REPORTSYSTEM_REPORTFACTORY_H

#include "../builders/ReportBuilder.h"
#include "../core/DataProvider.h"
#include "../core/DataProcessor.h"
#include "../core/Formatter.h"
#include "../core/ExportStrategy.h"
#include "../core/Report.h"

#include <memory>

namespace report_system {

    // Абстрактная фабрика для создания компонентов отчёта
    class ReportFactory {
    public:
        virtual ~ReportFactory() = default;

        // Создать поставщика данных
        virtual std::unique_ptr<DataProvider> createDataProvider() = 0;

        // Создать обработчик данных
        virtual std::unique_ptr<DataProcessor> createDataProcessor() = 0;

        // Создать форматировщик
        virtual std::unique_ptr<Formatter> createFormatter() = 0;

        // Создать стратегию экспорта
        virtual std::unique_ptr<ExportStrategy> createExportStrategy() = 0;

        // Создать готовый отчёт (шаблонный метод)
        std::unique_ptr<Report> createReport();
    };

} // namespace report_system

#endif // REPORTSYSTEM_REPORTFACTORY_H
