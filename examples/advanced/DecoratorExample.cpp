#include "../../include/decorators/LoggingDecorator.h"
#include "../../include/factories/SalesReportFactory.h"
#include <iostream>
#include <memory>

int main() {
    std::cout << "=== Пример использования декоратора для логирования ===\n\n";

    try {
        // Создаём фабрику отчётов
        auto factory = std::make_unique<report_system::SalesReportFactory>();

        // Создаём базовый отчёт через фабрику
        auto base_report = factory->createReport();

        if (!base_report) {
            std::cerr << "Ошибка: не удалось создать базовый отчёт\n";
            return 1;
        }

        std::cout << "Базовый отчёт создан.\n";
        std::cout << base_report->getInfo() << "\n\n";

        // Оборачиваем отчёт в декоратор логирования
        auto decorated_report = std::make_unique<report_system::LoggingDecorator>(
            std::move(base_report),
            "report_generation.log");

        std::cout << "Отчёт обёрнут в LoggingDecorator.\n";
        std::cout << decorated_report->getInfo() << "\n\n";

        std::cout << "Генерация отчёта с логированием...\n";
        auto result = decorated_report->generate();

        if (result) {
            std::cout << "✓ Отчёт успешно сгенерирован с логированием!\n";
            std::cout << "  Проверьте лог в файле: report_generation.log\n";
        } else {
            std::cerr << "✗ Ошибка при генерации отчёта: " << result.error_message << "\n";
        }

        // Пример с каскадом декораторов (закомментировано, так как нужен второй декоратор)
        // auto double_decorated = std::make_unique<report_system::CachingDecorator>(
        //     std::make_unique<report_system::LoggingDecorator>(
        //         std::move(base_report),
        //         "report.log"
        //     )
        // );

    } catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << "\n";
        return 1;
    }

    std::cout << "\n=== Пример завершён ===\n";
    return 0;
}
