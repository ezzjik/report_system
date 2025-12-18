#ifndef REPORTSYSTEM_DATAPROVIDER_H
#define REPORTSYSTEM_DATAPROVIDER_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace report_system {

    // Базовый класс для данных в отчёте
    struct DataRecord {
        virtual ~DataRecord() = default;
    };

    // Результат получения данных
    struct DataResult {
        bool success{false};
        std::string error_message;
        std::vector<std::unique_ptr<DataRecord>> data;

        // Конструкторы и операторы для управления копированием/перемещением
        DataResult() = default;
        ~DataResult() = default;

        // Копирование запрещено из-за unique_ptr
        DataResult(const DataResult&) = delete;
        DataResult& operator=(const DataResult&) = delete;

        // Разрешаем перемещение
        DataResult(DataResult&&) = default;
        DataResult& operator=(DataResult&&) = default;

        explicit operator bool() const {
            return success;
        }
    };

    // Абстрактный класс для поставщиков данных
    class DataProvider {
    public:
        virtual ~DataProvider() = default;

        // Получить данные
        virtual DataResult fetchData() = 0;

        // Получить имя провайдера
        virtual std::string getName() const = 0;

        // Проверить доступность источника данных
        virtual bool isAvailable() const = 0;
    };

} // namespace report_system

#endif // REPORTSYSTEM_DATAPROVIDER_H
