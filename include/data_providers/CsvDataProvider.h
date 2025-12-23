#ifndef REPORTSYSTEM_CSVDATAPROVIDER_H
#define REPORTSYSTEM_CSVDATAPROVIDER_H

#include "../core/DataProvider.h"

#include <memory>
#include <string>
#include <vector>

namespace report_system {

    // Конкретная запись данных из CSV
    class CsvDataRecord: public DataRecord {
    public:
        explicit CsvDataRecord(const std::vector<std::string>& fields, const std::vector<std::string>& column_names = {});

        // Получить поле по индексу
        std::string getField(size_t index) const;

        // Получить поле по имени колонки
        std::string getField(const std::string& column_name) const;

        // Получить все поля
        const std::vector<std::string>& getFields() const;

        // Получить имена колонок
        const std::vector<std::string>& getColumnNames() const;

        // Получить количество полей
        size_t size() const;

    private:
        std::vector<std::string> fields_;
        std::vector<std::string> column_names_;
    };

    // Поставщик данных из CSV файла
    class CsvDataProvider: public DataProvider {
    public:
        explicit CsvDataProvider(const std::string& file_path);
        explicit CsvDataProvider(const std::string& file_path, char delimiter);

        // Реализация абстрактных методов
        DataResult fetchData() override;
        std::string getName() const override;
        bool isAvailable() const override;

        // Установить разделитель
        void setDelimiter(char delimiter);

        // Получить имена колонок
        const std::vector<std::string>& getColumnNames() const;

    private:
        std::string file_path_;
        char delimiter_{','};
        std::vector<std::string> column_names_;
    };

} // namespace report_system

#endif // REPORTSYSTEM_CSVDATAPROVIDER_H
