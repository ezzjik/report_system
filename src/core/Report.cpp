#include "core/Report.h"

#include <sstream>

namespace report_system {

    Report::Report(std::unique_ptr<DataProvider> provider,
                   std::vector<std::unique_ptr<DataProcessor>> processors,
                   std::unique_ptr<Formatter> formatter,
                   std::unique_ptr<ExportStrategy> exporter)
        : data_provider_(std::move(provider))
        , processors_(std::move(processors))
        , formatter_(std::move(formatter))
        , export_strategy_(std::move(exporter)) {
    }

    ReportResult Report::generate() {
        ReportResult result;

        // 1. Получение данных
        DataResult data_result = data_provider_->fetchData();
        if (!data_result) {
            result.success = false;
            result.error_message = "Failed to fetch data: " + data_result.error_message;
            return result;
        }

        // 2. Обработка данных
        DataResult processed_result = std::move(data_result); // Используем перемещение
        for (const auto& processor : processors_) {
            processed_result = processor->process(std::move(processed_result)); // process должен принимать DataResult по значению с перемещением
            if (!processed_result.success) {
                result.success = false;
                result.error_message = "Data processing failed in " + processor->getName() +
                                       ": " + processed_result.error_message;
                return result;
            }
        }

        // 3. Форматирование
        FormattedReport formatted_report = formatter_->format(processed_result);
        if (!formatted_report) {
            result.success = false;
            result.error_message = "Formatting failed";
            return result;
        }

        // 4. Экспорт
        bool export_success = export_strategy_->exportReport(formatted_report);
        if (!export_success) {
            result.success = false;
            result.error_message = "Export failed to " + export_strategy_->getDestinationInfo();
            return result;
        }

        // Успешное завершение
        result.success = true;
        result.generated_content = std::move(formatted_report.content);
        result.export_destination = export_strategy_->getDestinationInfo();
        return result;
    }

    std::string Report::getInfo() const {
        std::ostringstream info;
        info << "Report Configuration:\n";
        info << "  Data Provider: " << (data_provider_ ? data_provider_->getName() : "None") << "\n";
        info << "  Processors: " << processors_.size() << "\n";
        for (size_t i = 0; i < processors_.size(); ++i) {
            info << "    " << i + 1 << ". " << processors_[i]->getName() << "\n";
        }
        info << "  Formatter: " << (formatter_ ? formatter_->getName() : "None") << "\n";
        info << "  Export Strategy: " << (export_strategy_ ? export_strategy_->getName() : "None");
        return info.str();
    }

} // namespace report_system
