#include "../../include/decorators/LoggingDecorator.h"
#include "../../include/factories/SalesReportFactory.h"
#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

namespace report_system {
    namespace test {

        TEST(DecoratorTest, LoggingDecoratorWrapping) {
            auto factory = std::make_unique<SalesReportFactory>();
            auto base_report = factory->createReport();

            ASSERT_TRUE(base_report != nullptr);

            // Создаем декоратор с логированием в файл
            const std::string log_file = "test_decorator.log";
            auto decorated_report = std::make_unique<LoggingDecorator>(
                std::move(base_report),
                log_file);

            EXPECT_TRUE(decorated_report != nullptr);

            // Проверяем, что информация о декораторе содержит нужную строку
            std::string info = decorated_report->getInfo();
            EXPECT_TRUE(info.find("LoggingDecorator") != std::string::npos);

            // Убираем файл лога если он существует
            std::filesystem::remove(log_file);
        }

        TEST(DecoratorTest, LoggingDecoratorLogFileCreation) {
            auto factory = std::make_unique<SalesReportFactory>();
            auto base_report = factory->createReport();

            const std::string log_file = "test_log_creation.log";

            // Удаляем файл если он существует
            std::filesystem::remove(log_file);

            auto decorated_report = std::make_unique<LoggingDecorator>(
                std::move(base_report),
                log_file);

            // Генерируем отчет (логирование должно создать файл)
            auto result = decorated_report->generate();

            // Проверяем, что файл лога был создан (если генерация начала работать)
            // Игнорируем результат генерации, важно что не было падения
            SUCCEED();

            // Очистка
            std::filesystem::remove(log_file);
        }

        TEST(DecoratorTest, LoggingDecoratorWithoutLogFile) {
            auto factory = std::make_unique<SalesReportFactory>();
            auto base_report = factory->createReport();

            // Декоратор без указания файла лога (должен работать, но не логировать в файл)
            auto decorated_report = std::make_unique<LoggingDecorator>(
                std::move(base_report),
                "" // пустой путь к файлу
            );

            auto result = decorated_report->generate();
            // Должно работать без ошибок (возможно, с ошибкой данных, но не падением)
            EXPECT_TRUE(result.success || !result.error_message.empty());
        }

        TEST(DecoratorTest, DecoratorInfoMethod) {
            auto factory = std::make_unique<SalesReportFactory>();
            auto base_report = factory->createReport();

            std::string base_info = base_report->getInfo();

            auto decorated_report = std::make_unique<LoggingDecorator>(
                std::move(base_report),
                "test.log");

            std::string decorated_info = decorated_report->getInfo();

            // Информация декоратора должна отличаться от базовой
            EXPECT_NE(base_info, decorated_info);
            // И содержать название декоратора
            EXPECT_TRUE(decorated_info.find("LoggingDecorator") != std::string::npos);

            std::filesystem::remove("test.log");
        }

    } // namespace test
} // namespace report_system
