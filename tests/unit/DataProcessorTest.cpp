#include "../../include/data_processors/FilterProcessor.h"
#include "../../include/data_providers/CsvDataProvider.h"

#include <gtest/gtest.h>

namespace report_system {
    namespace test {

        TEST(DataProcessorTest, FilterProcessorConstruction) {
            FilterProcessor processor("test_condition");
            EXPECT_EQ(processor.getName(), "FilterProcessor");
        }

        TEST(DataProcessorTest, FilterProcessorProcessEmptyData) {
            FilterProcessor processor("test_condition");

            DataResult empty_input;
            empty_input.success = true;

            auto result = processor.process(std::move(empty_input));

            EXPECT_TRUE(result.success);
            EXPECT_EQ(result.data.size(), 0);
        }

        TEST(DataProcessorTest, FilterProcessorProcessErrorInput) {
            FilterProcessor processor("test_condition");

            DataResult error_input;
            error_input.success = false;
            error_input.error_message = "Test error";

            auto result = processor.process(std::move(error_input));

            EXPECT_FALSE(result.success);
            EXPECT_EQ(result.error_message, "Test error");
        }

        TEST(DataProcessorTest, FilterProcessorWithCustomFunction) {
            FilterProcessor processor("test_condition");

            // Устанавливаем пользовательскую функцию фильтрации
            int call_count = 0;
            processor.setProcessFunction([&call_count](const DataRecord&) -> std::unique_ptr<DataRecord> {
                call_count++;
                // Всегда принимаем запись
                return std::make_unique<CsvDataRecord>(std::vector<std::string>{"test"});
            });

            DataResult input;
            input.success = true;
            input.data.push_back(std::make_unique<CsvDataRecord>(std::vector<std::string>{"data1"}));
            input.data.push_back(std::make_unique<CsvDataRecord>(std::vector<std::string>{"data2"}));

            auto result = processor.process(std::move(input));

            EXPECT_TRUE(result.success);
            EXPECT_EQ(result.data.size(), 2);
            EXPECT_EQ(call_count, 2);
        }

        TEST(DataProcessorTest, FilterProcessorWithoutFunction) {
            FilterProcessor processor("");

            // Удаляем стандартную функцию
            processor.setProcessFunction(nullptr);

            DataResult input;
            input.success = true;
            input.data.push_back(std::make_unique<CsvDataRecord>(std::vector<std::string>{"data"}));

            auto result = processor.process(std::move(input));

            EXPECT_FALSE(result.success);
            EXPECT_EQ(result.error_message, "Filter function is not set");
        }

        TEST(DataProcessorTest, SetConditionUpdatesProcessor) {
            FilterProcessor processor("initial_condition");

            processor.setCondition("new_condition");

            // Проверяем, что процессор всё ещё работает после смены условия
            DataResult input;
            input.success = true;
            input.data.push_back(std::make_unique<CsvDataRecord>(std::vector<std::string>{"data"}));

            auto result = processor.process(std::move(input));

            // Условие "new_condition" не соответствует данным "data", поэтому запись должна быть отклонена
            EXPECT_TRUE(result.success);
            EXPECT_EQ(result.data.size(), 0);
        }

    } // namespace test
} // namespace report_system
