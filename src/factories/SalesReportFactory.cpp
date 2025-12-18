#include "factories/SalesReportFactory.h"

namespace report_system {

    std::unique_ptr<DataProvider> SalesReportFactory::createDataProvider() {
        // Используем CSV файл с продажами
        return std::make_unique<CsvDataProvider>("data/sales.csv", ';');
    }

    std::unique_ptr<DataProcessor> SalesReportFactory::createDataProcessor() {
        // Фильтр для данных о продажах (например, только за первый квартал)
        return std::make_unique<FilterProcessor>("quarter == 'Q1'");
    }

    std::unique_ptr<Formatter> SalesReportFactory::createFormatter() {
        auto formatter = std::make_unique<HtmlFormatter>();
        formatter->setTitle("Отчёт о продажах");
        formatter->setTableStyle("border-collapse: collapse; width: 100%;");
        formatter->includeColumnNames(true);
        return formatter;
    }

    std::unique_ptr<ExportStrategy> SalesReportFactory::createExportStrategy() {
        // Экспорт в директорию reports/sales
        return std::make_unique<FileExportStrategy>("reports/sales");
    }

} // namespace report_system
