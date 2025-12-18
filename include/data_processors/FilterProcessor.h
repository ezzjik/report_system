#ifndef REPORTSYSTEM_FILTERPROCESSOR_H
#define REPORTSYSTEM_FILTERPROCESSOR_H

#include "../core/DataProcessor.h"

#include <functional>
#include <memory>
#include <string>

namespace report_system {

    // Процессор для фильтрации данных по условию
    class FilterProcessor: public DataProcessor {
    public:
        explicit FilterProcessor(const std::string& condition);

        // Реализация абстрактных методов
        DataResult process(DataResult input) override;
        std::string getName() const override;
        void setProcessFunction(ProcessFunction func) override;

        // Установить условие фильтрации
        void setCondition(const std::string& condition);

        // Создать стандартную функцию фильтрации
        static ProcessFunction createDefaultFilter(const std::string& condition);

    private:
        std::string condition_;
        ProcessFunction filter_function_;
    };

} // namespace report_system

#endif // REPORTSYSTEM_FILTERPROCESSOR_H
