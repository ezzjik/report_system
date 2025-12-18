#ifndef REPORTSYSTEM_FORMATTER_H
#define REPORTSYSTEM_FORMATTER_H

#include "DataProvider.h"

#include <memory>
#include <string>

namespace report_system {

    // Структура для отформатированных данных отчёта
    struct FormattedReport {
        std::string content;
        std::string mime_type;
        bool is_valid{false};

        explicit operator bool() const {
            return is_valid;
        }
    };

    // Абстрактный класс для форматировщиков
    class Formatter {
    public:
        virtual ~Formatter() = default;

        // Форматировать данные в отчёт
        virtual FormattedReport format(const DataResult& data) = 0;

        // Получить имя форматировщика
        virtual std::string getName() const = 0;

        // Получить поддерживаемый тип вывода
        virtual std::string getOutputType() const = 0;
    };

} // namespace report_system

#endif // REPORTSYSTEM_FORMATTER_H
