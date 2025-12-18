#include "data_providers/CsvDataProvider.h"

#include <fstream>
#include <sstream>
#include <filesystem>

namespace report_system {

    CsvDataRecord::CsvDataRecord(const std::vector<std::string>& fields)
        : fields_(fields) {
    }

    std::string CsvDataRecord::getField(size_t index) const {
        if (index >= fields_.size()) {
            return "";
        }
        return fields_[index];
    }

    const std::vector<std::string>& CsvDataRecord::getFields() const {
        return fields_;
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
            // Пропускаем заголовок (первую строку)
            std::getline(file, line);

            while (std::getline(file, line)) {
                std::vector<std::string> fields;
                std::stringstream ss(line);
                std::string field;

                while (std::getline(ss, field, delimiter_)) {
                    fields.push_back(field);
                }

                if (!fields.empty()) {
                    result.data.push_back(std::make_unique<CsvDataRecord>(fields));
                }
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

} // namespace report_system
