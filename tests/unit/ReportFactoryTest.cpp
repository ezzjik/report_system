#include "../../include/factories/SalesReportFactory.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace report_system {
    namespace test {

        TEST(ReportFactoryTest, SalesReportFactoryCreatesCorrectComponents) {
            SalesReportFactory factory;

            auto provider = factory.createDataProvider();
            auto processor = factory.createDataProcessor();
            auto formatter = factory.createFormatter();
            auto exporter = factory.createExportStrategy();

            EXPECT_TRUE(provider != nullptr);
            EXPECT_TRUE(processor != nullptr);
            EXPECT_TRUE(formatter != nullptr);
            EXPECT_TRUE(exporter != nullptr);

            // Проверяем, что возвращаются объекты правильных типов
            EXPECT_TRUE(dynamic_cast<CsvDataProvider*>(provider.get()) != nullptr);
            EXPECT_TRUE(dynamic_cast<FilterProcessor*>(processor.get()) != nullptr);
            EXPECT_TRUE(dynamic_cast<HtmlFormatter*>(formatter.get()) != nullptr);
            EXPECT_TRUE(dynamic_cast<FileExportStrategy*>(exporter.get()) != nullptr);
        }

        TEST(ReportFactoryTest, FactoryCreatesReport) {
            SalesReportFactory factory;
            auto report = factory.createReport();

            EXPECT_TRUE(report != nullptr);
            EXPECT_FALSE(report->getInfo().empty());
        }

        TEST(ReportFactoryTest, ReportFactoryComponentsHaveNames) {
            SalesReportFactory factory;

            auto provider = factory.createDataProvider();
            auto processor = factory.createDataProcessor();
            auto formatter = factory.createFormatter();
            auto exporter = factory.createExportStrategy();

            EXPECT_FALSE(provider->getName().empty());
            EXPECT_FALSE(processor->getName().empty());
            EXPECT_FALSE(formatter->getName().empty());
            EXPECT_FALSE(formatter->getOutputType().empty());
            EXPECT_FALSE(exporter->getName().empty());
            EXPECT_FALSE(exporter->getDestinationInfo().empty());
        }

    } // namespace test
} // namespace report_system
