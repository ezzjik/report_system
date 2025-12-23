#include "data_processors/FilterProcessor.h"
#include "data_providers/CsvDataProvider.h"

#include <algorithm>
#include <sstream>
#include <iostream>

namespace report_system {

    FilterProcessor::FilterProcessor(const std::string& condition)
        : condition_(condition) {
        filter_function_ = createDefaultFilter(condition);
    }

    DataResult FilterProcessor::process(DataResult input) {
        if (!input.success) {
            return input;
        }

        if (!filter_function_) {
            DataResult result;
            result.success = false;
            result.error_message = "Filter function is not set";
            return result;
        }

        DataResult result;
        result.success = true;

        for (const auto& record : input.data) {
            auto processed_record = filter_function_(*record);
            if (processed_record) {
                result.data.push_back(std::move(processed_record));
            }
        }

        return result;
    }

    std::string FilterProcessor::getName() const {
        return "FilterProcessor";
    }

    void FilterProcessor::setProcessFunction(ProcessFunction func) {
        filter_function_ = std::move(func);
    }

    void FilterProcessor::setCondition(const std::string& condition) {
        condition_ = condition;
        filter_function_ = createDefaultFilter(condition);
    }

    ProcessFunction FilterProcessor::createDefaultFilter(const std::string& condition) {
        // Если условие пустое - отклоняем все записи
        if (condition.empty()) {
            return [](const DataRecord&) -> std::unique_ptr<DataRecord> {
                return nullptr;
            };
        }

        // Упрощенная реализация фильтрации для CSV данных
        // Обрабатываем условия вида: "field == 'value'"

        // Извлекаем имя поля и значение из условия
        std::string field_name, expected_value;
        size_t eq_pos = condition.find("==");

        if (eq_pos != std::string::npos) {
            // Условие с оператором ==
            field_name = condition.substr(0, eq_pos);
            expected_value = condition.substr(eq_pos + 2);

            // Убираем пробелы
            field_name.erase(0, field_name.find_first_not_of(" \t"));
            field_name.erase(field_name.find_last_not_of(" \t") + 1);
            expected_value.erase(0, expected_value.find_first_not_of(" \t"));
            expected_value.erase(expected_value.find_last_not_of(" \t") + 1);

            // Убираем кавычки
            if (expected_value.size() >= 2 &&
                ((expected_value.front() == '\'' && expected_value.back() == '\'') ||
                 (expected_value.front() == '"' && expected_value.back() == '"'))) {
                expected_value = expected_value.substr(1, expected_value.size() - 2);
            }
        } else {
            // Условие без оператора == - ищем подстроку во всех полях
            expected_value = condition;
            // Убираем пробелы
            expected_value.erase(0, expected_value.find_first_not_of(" \t"));
            expected_value.erase(expected_value.find_last_not_of(" \t") + 1);
        }

        return [field_name, expected_value, eq_pos](const DataRecord& record) -> std::unique_ptr<DataRecord> {
            // Пытаемся привести запись к CsvDataRecord
            const CsvDataRecord* csv_record = dynamic_cast<const CsvDataRecord*>(&record);
            if (!csv_record) {
                return nullptr;
            }

            // Если условие не содержит "==", проверяем наличие подстроки во всех полях
            if (eq_pos == std::string::npos) {
                for (size_t i = 0; i < csv_record->size(); ++i) {
                    if (csv_record->getField(i).find(expected_value) != std::string::npos) {
                        return std::make_unique<CsvDataRecord>(csv_record->getFields(), csv_record->getColumnNames());
                    }
                }
                return nullptr;
            }

            // Используем метод getField по имени колонки
            std::string field_value = csv_record->getField(field_name);
            // Если поле не найдено, проверяем, может быть колонка с таким именем не существует
            if (field_value.empty()) {
                // Проверяем, существует ли такая колонка
                bool column_exists = false;
                for (const auto& col_name : csv_record->getColumnNames()) {
                    if (col_name == field_name) {
                        column_exists = true;
                        break;
                    }
                }
                // Если колонка существует, но значение пустое - это нормально
                if (!column_exists) {
                    return nullptr;
                }
            }

            // Сравниваем значение поля с ожидаемым
            if (field_value == expected_value) {
                return std::make_unique<CsvDataRecord>(csv_record->getFields(), csv_record->getColumnNames());
            }

            return nullptr;
        };
    }

} // namespace report_system
