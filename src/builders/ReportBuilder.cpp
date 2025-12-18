#include "builders/ReportBuilder.h"

#include <memory>
#include <utility>

namespace report_system {

    ReportBuilder& ReportBuilder::setDataSource(std::unique_ptr<DataProvider> provider) {
        data_provider_ = std::move(provider);
        return *this;
    }

    ReportBuilder& ReportBuilder::addProcessor(std::unique_ptr<DataProcessor> processor) {
        processors_.push_back(std::move(processor));
        return *this;
    }

    ReportBuilder& ReportBuilder::setFormatter(std::unique_ptr<Formatter> formatter) {
        formatter_ = std::move(formatter);
        return *this;
    }

    ReportBuilder& ReportBuilder::setExportStrategy(std::unique_ptr<ExportStrategy> exporter) {
        export_strategy_ = std::move(exporter);
        return *this;
    }

    std::unique_ptr<Report> ReportBuilder::build() {
        // Проверка обязательных компонентов
        if (!data_provider_) {
            // Можно выбросить исключение или вернуть nullptr
            return nullptr;
        }

        if (!formatter_) {
            return nullptr;
        }

        if (!export_strategy_) {
            return nullptr;
        }

        // Создаём отчёт
        return std::make_unique<Report>(
            std::move(data_provider_),
            std::move(processors_),
            std::move(formatter_),
            std::move(export_strategy_));
    }

} // namespace report_system
