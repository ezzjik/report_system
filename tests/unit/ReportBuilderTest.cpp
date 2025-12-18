#include "../../include/builders/ReportBuilder.h"
#include "../../include/data_providers/CsvDataProvider.h"
#include "../../include/data_processors/FilterProcessor.h"
#include "../../include/formatters/HtmlFormatter.h"
#include "../../include/export_strategies/FileExportStrategy.h"

#include <gtest/gtest.h>

namespace report_system {
    namespace test {

        TEST(ReportBuilderTest, ReportBuilderConstruction) {
            ReportBuilder builder;
            // Builder должен создаваться без ошибок
            SUCCEED();
        }

        TEST(ReportBuilderTest, ReportBuilderFluentInterface) {
            ReportBuilder builder;

            // Проверяем, что методы возвращают ссылку на builder (fluent interface)
            ReportBuilder& ref1 = builder.setDataSource(std::make_unique<CsvDataProvider>("test.csv"));
            ReportBuilder& ref2 = builder.addProcessor(std::make_unique<FilterProcessor>("test"));
            ReportBuilder& ref3 = builder.setFormatter(std::make_unique<HtmlFormatter>());
            ReportBuilder& ref4 = builder.setExportStrategy(std::make_unique<FileExportStrategy>("/tmp"));

            EXPECT_EQ(&ref1, &builder);
            EXPECT_EQ(&ref2, &builder);
            EXPECT_EQ(&ref3, &builder);
            EXPECT_EQ(&ref4, &builder);
        }

        TEST(ReportBuilderTest, ReportBuilderBuildWithAllComponents) {
            ReportBuilder builder;

            auto report = builder
                              .setDataSource(std::make_unique<CsvDataProvider>("test.csv"))
                              .addProcessor(std::make_unique<FilterProcessor>("test"))
                              .setFormatter(std::make_unique<HtmlFormatter>())
                              .setExportStrategy(std::make_unique<FileExportStrategy>("/tmp"))
                              .build();

            EXPECT_TRUE(report != nullptr);
            EXPECT_FALSE(report->getInfo().empty());
        }

        TEST(ReportBuilderTest, ReportBuilderBuildMissingDataSource) {
            ReportBuilder builder;

            auto report = builder
                              .setFormatter(std::make_unique<HtmlFormatter>())
                              .setExportStrategy(std::make_unique<FileExportStrategy>("/tmp"))
                              .build();

            EXPECT_TRUE(report == nullptr);
        }

        TEST(ReportBuilderTest, ReportBuilderBuildMissingFormatter) {
            ReportBuilder builder;

            auto report = builder
                              .setDataSource(std::make_unique<CsvDataProvider>("test.csv"))
                              .setExportStrategy(std::make_unique<FileExportStrategy>("/tmp"))
                              .build();

            EXPECT_TRUE(report == nullptr);
        }

        TEST(ReportBuilderTest, ReportBuilderBuildMissingExportStrategy) {
            ReportBuilder builder;

            auto report = builder
                              .setDataSource(std::make_unique<CsvDataProvider>("test.csv"))
                              .setFormatter(std::make_unique<HtmlFormatter>())
                              .build();

            EXPECT_TRUE(report == nullptr);
        }

        TEST(ReportBuilderTest, ReportBuilderMultipleProcessors) {
            ReportBuilder builder;

            auto report = builder
                              .setDataSource(std::make_unique<CsvDataProvider>("test.csv"))
                              .addProcessor(std::make_unique<FilterProcessor>("condition1"))
                              .addProcessor(std::make_unique<FilterProcessor>("condition2"))
                              .addProcessor(std::make_unique<FilterProcessor>("condition3"))
                              .setFormatter(std::make_unique<HtmlFormatter>())
                              .setExportStrategy(std::make_unique<FileExportStrategy>("/tmp"))
                              .build();

            EXPECT_TRUE(report != nullptr);

            std::string info = report->getInfo();
            // Проверяем, что информация о процессорах содержится в info
            EXPECT_TRUE(info.find("Processors: 3") != std::string::npos);
        }

        TEST(ReportBuilderTest, ReportBuilderEmptyProcessors) {
            ReportBuilder builder;

            auto report = builder
                              .setDataSource(std::make_unique<CsvDataProvider>("test.csv"))
                              .setFormatter(std::make_unique<HtmlFormatter>())
                              .setExportStrategy(std::make_unique<FileExportStrategy>("/tmp"))
                              .build();

            EXPECT_TRUE(report != nullptr);

            std::string info = report->getInfo();
            EXPECT_TRUE(info.find("Processors: 0") != std::string::npos);
        }

    } // namespace test
} // namespace report_system
