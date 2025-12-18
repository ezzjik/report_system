#ifndef REPORTSYSTEM_DATAPROCESSOR_H
#define REPORTSYSTEM_DATAPROCESSOR_H

#include <functional>
#include <memory>
#include <string>

#include "DataProvider.h"

namespace report_system {

    // Тип функции для обработки данных (лямбды, std::function)
    using ProcessFunction = std::function<std::unique_ptr<DataRecord>(const DataRecord&)>;

    // Абстрактный класс для обработчиков данных
    class DataProcessor {
    public:
        virtual ~DataProcessor() = default;

        // Обработать данные (принимаем DataResult по значению для перемещения)
        virtual DataResult process(DataResult input) = 0;

        // Получить имя процессора
        virtual std::string getName() const = 0;

        // Установить пользовательскую функцию обработки
        virtual void setProcessFunction(ProcessFunction func) = 0;
    };

} // namespace report_system

#endif // REPORTSYSTEM_DATAPROCESSOR_H
