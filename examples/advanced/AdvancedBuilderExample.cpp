#include "../../include/builders/ReportBuilder.h"
#include "../../include/data_providers/CsvDataProvider.h"
#include "../../include/data_processors/FilterProcessor.h"
#include "../../include/formatters/HtmlFormatter.h"
#include "../../include/export_strategies/FileExportStrategy.h"
#include <iostream>
#include <memory>

int main() {
    std::cout << "=== Продвинутый пример использования ReportBuilder ===\n\n";

    try {
        // Создаем сложный отчет с несколькими процессорами
        auto report = report_system::ReportBuilder()
                          .setDataSource(std::make_unique<report_system::CsvDataProvider>("examples/data/sales.csv", ';'))
                          .addProcessor(std::make_unique<report_system::FilterProcessor>("quarter == 'Q1'"))
                          .addProcessor(std::make_unique<report_system::FilterProcessor>("region == 'Europe'"))
                          .setFormatter(std::make_unique<report_system::HtmlFormatter>())
                          .setExportStrategy(std::make_unique<report_system::FileExportStrategy>("custom_reports"))
                          .build();

        if (!report) {
            std::cerr << "Ошибка: не удалось построить отчёт\n";
            return 1;
        }

        std::cout << "Создан отчёт со следующей конфигурацией:\n";
        std::cout << report->getInfo() << "\n\n";

        std::cout << "Запуск генерации отчёта...\n";
        auto result = report->generate();

        if (result) {
            std::cout << "✓ Отчёт успешно сгенерирован!\n";
            std::cout << "  Размер контента: " << result.generated_content.size() << " байт\n";
            std::cout << "  Назначение: " << result.export_destination << "\n";

            // Показываем превью контента
            std::string preview = result.generated_content.substr(0, 200);
            std::cout << "  Превью контента: " << preview << "...\n";
        } else {
            std::cerr << "✗ Ошибка при генерации отчёта: " << result.error_message << "\n";

            // Даже при ошибке показываем, что было сделано
            if (!result.generated_content.empty()) {
                std::cout << "  Частично сгенерированный контент ("
                          << result.generated_content.size() << " байт):\n";
                std::string preview = result.generated_content.substr(0, 150);
                std::cout << "  " << preview << "...\n";
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << "\n";
        return 1;
    }

    std::cout << "\n=== Пример завершён ===\n";
    return 0;
}
