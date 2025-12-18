#include "factories/ReportFactory.h"

#include "builders/ReportBuilder.h"

namespace report_system {

    std::unique_ptr<Report> ReportFactory::createReport() {
        // Используем строитель для создания отчёта
        ReportBuilder builder;

        // Используем фабричные методы для создания компонентов
        builder.setDataSource(createDataProvider());
        builder.addProcessor(createDataProcessor());
        builder.setFormatter(createFormatter());
        builder.setExportStrategy(createExportStrategy());

        // Строим отчёт
        return builder.build();
    }

} // namespace report_system
