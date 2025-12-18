#include "../../include/factories/SalesReportFactory.h"
#include <iostream>

int main() {
    std::cout << "=== Пример использования фабрики отчётов ===\n\n";

    try {
        // Создаём фабрику для отчётов о продажах
        auto factory = std::make_unique<report_system::SalesReportFactory>();

        // Создаём готовый отчёт через фабрику
        auto report = factory->createReport();

        if (!report) {
            std::cerr << "Ошибка: не удалось создать отчёт\n";
            return 1;
        }

        std::cout << "Конфигурация отчёта:\n";
        std::cout << report->getInfo() << "\n\n";

        std::cout << "Генерация отчёта...\n";
        auto result = report->generate();

        if (result) {
            std::cout << "✓ Отчёт успешно сгенерирован\n";
            std::cout << "  Экспортировано в: " << result.export_destination << "\n";
            std::cout << "  Размер контента: " << result.generated_content.size() << " байт\n";
        } else {
            std::cerr << "✗ Ошибка при генерации отчёта: " << result.error_message << "\n";
            return 1;
        }

    } catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << "\n";
        return 1;
    }

    std::cout << "\n=== Пример завершён ===\n";
    return 0;
}
