#include "data_providers/CsvDataProvider.h"

#include <fstream>
#include <sstream>
#include <filesystem>

namespace report_system {

    CsvDataRecord::CsvDataRecord(const std::vector<std::string>& fields, const std::vector<std::string>& column_names)
        : fields_(fields)
        , column_names_(column_names) {
    }

    std::string CsvDataRecord::getField(size_t index) const {
        if (index >= fields_.size()) {
            return "";
        }
        return fields_[index];
    }

    std::string CsvDataRecord::getField(const std::string& column_name) const {
        // Находим индекс колонки по имени
        for (size_t i = 0; i < column_names_.size(); ++i) {
            if (column_names_[i] == column_name) {
                return getField(i);
            }
        }
        return ""; // Колонка не найдена
    }

    const std::vector<std::string>& CsvDataRecord::getFields() const {
        return fields_;
    }

    const std::vector<std::string>& CsvDataRecord::getColumnNames() const {
        return column_names_;
    }

    size_t CsvDataRecord::size() const {
        return fields_.size();
    }

    CsvDataProvider::CsvDataProvider(const std::string& file_path)
        : file_path_(file_path) {
    }

    CsvDataProvider::CsvDataProvider(const std::string& file_path, char delimiter)
        : file_path_(file_path)
        , delimiter_(delimiter) {
    }

    DataResult CsvDataProvider::fetchData() {
        DataResult result;

        if (!isAvailable()) {
            result.success = false;
            result.error_message = "CSV file is not available: " + file_path_;
            return result;
        }

        try {
            std::ifstream file(file_path_);
            if (!file.is_open()) {
                result.success = false;
                result.error_message = "Failed to open CSV file: " + file_path_;
                return result;
            }

            std::string line;
            // Читаем заголовок (первую строку)
            if (std::getline(file, line)) {
                std::stringstream header_ss(line);
                std::string column;
                column_names_.clear();
                while (std::getline(header_ss, column, delimiter_)) {
                    column_names_.push_back(column);
                }
            } else {
                // Файл пустой
                result.success = false;
                result.error_message = "CSV file is empty: " + file_path_;
                return result;
            }

            // Читаем остальные строки (данные)
            size_t line_number = 2; // Начинаем с 2, т.к. 1 строка - заголовок
            while (std::getline(file, line)) {
                std::vector<std::string> fields;
                std::stringstream ss(line);
                std::string field;

                while (std::getline(ss, field, delimiter_)) {
                    fields.push_back(field);
                }

                if (!fields.empty()) {
                    // Проверяем соответствие количества полей количеству колонок
                    if (column_names_.size() != fields.size()) {
                        result.success = false;
                        result.error_message =
                            "CSV format error at line " + std::to_string(line_number) +
                            ": expected " + std::to_string(column_names_.size()) +
                            " columns, got " + std::to_string(fields.size());
                        return result;
                    }

                    result.data.push_back(std::make_unique<CsvDataRecord>(fields, column_names_));
                }
                line_number++;
            }

            result.success = true;
            return result;

        } catch (const std::exception& e) {
            result.success = false;
            result.error_message = "Error reading CSV file: " + std::string(e.what());
            return result;
        }
    }

    std::string CsvDataProvider::getName() const {
        return "CsvDataProvider";
    }

    bool CsvDataProvider::isAvailable() const {
        return std::filesystem::exists(file_path_);
    }

    void CsvDataProvider::setDelimiter(char delimiter) {
        delimiter_ = delimiter;
    }

    const std::vector<std::string>& CsvDataProvider::getColumnNames() const {
        return column_names_;
    }

} // namespace report_system
