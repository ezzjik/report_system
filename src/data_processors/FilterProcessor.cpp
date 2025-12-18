#include "data_processors/FilterProcessor.h"

#include <algorithm>
#include <sstream>

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
        // Простая реализация: фильтрация по наличию подстроки в строковом представлении
        return [condition](const DataRecord&) -> std::unique_ptr<DataRecord> {
            // В реальной реализации здесь должна быть логика фильтрации
            // Для примера возвращаем nullptr, если условие пустое
            if (condition.empty()) {
                return nullptr;
            }
            // Заглушка: всегда возвращаем nullptr (в реальном коде нужно было бы преобразовать DataRecord в конкретный тип)
            return nullptr;
        };
    }

} // namespace report_system
