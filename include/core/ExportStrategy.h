#ifndef REPORTSYSTEM_EXPORTSTRATEGY_H
#define REPORTSYSTEM_EXPORTSTRATEGY_H

#include "Formatter.h"

#include <memory>
#include <string>

namespace report_system {

    // Абстрактный класс для стратегий экспорта
    class ExportStrategy {
    public:
        virtual ~ExportStrategy() = default;

        // Экспортировать отчёт
        virtual bool exportReport(const FormattedReport& report) = 0;

        // Получить имя стратегии
        virtual std::string getName() const = 0;

        // Получить информацию о назначении (куда экспортируется)
        virtual std::string getDestinationInfo() const = 0;
    };

} // namespace report_system

#endif // REPORTSYSTEM_EXPORTSTRATEGY_H
