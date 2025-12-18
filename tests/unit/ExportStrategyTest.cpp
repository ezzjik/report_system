#include "../../include/export_strategies/FileExportStrategy.h"
#include "../mocks/MockExportStrategy.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <filesystem>

using ::testing::_;
using ::testing::Return;

namespace report_system {
    namespace test {

        TEST(ExportStrategyTest, FileExportStrategyConstruction) {
            FileExportStrategy exporter("/tmp/reports");
            EXPECT_EQ(exporter.getName(), "FileExportStrategy");
            EXPECT_EQ(exporter.getDestinationInfo(), "Directory: /tmp/reports");
        }

        TEST(ExportStrategyTest, FileExportStrategySetDirectory) {
            FileExportStrategy exporter("/tmp/initial");
            EXPECT_EQ(exporter.getDestinationInfo(), "Directory: /tmp/initial");

            exporter.setDirectory("/tmp/new_location");
            EXPECT_EQ(exporter.getDestinationInfo(), "Directory: /tmp/new_location");
        }

        TEST(ExportStrategyTest, FileExportStrategyInvalidDirectory) {
            FileExportStrategy exporter("");

            FormattedReport report;
            report.content = "Test content";
            report.mime_type = "text/html";
            report.is_valid = true;

            bool result = exporter.exportReport(report);
            EXPECT_FALSE(result);
        }

        TEST(ExportStrategyTest, FileExportStrategyInvalidReport) {
            FileExportStrategy exporter("/tmp/reports");

            FormattedReport report;
            report.is_valid = false;

            bool result = exporter.exportReport(report);
            EXPECT_FALSE(result);
        }

        TEST(ExportStrategyTest, MockExportStrategyUsage) {
            MockExportStrategy mock_exporter;

            EXPECT_CALL(mock_exporter, getName())
                .WillOnce(Return("MockExporter"));

            EXPECT_CALL(mock_exporter, getDestinationInfo())
                .WillOnce(Return("Mock destination"));

            EXPECT_CALL(mock_exporter, exportReport(_))
                .WillOnce(Return(true));

            EXPECT_EQ(mock_exporter.getName(), "MockExporter");
            EXPECT_EQ(mock_exporter.getDestinationInfo(), "Mock destination");

            FormattedReport report;
            report.is_valid = true;
            bool result = mock_exporter.exportReport(report);
            EXPECT_TRUE(result);
        }

        TEST(ExportStrategyTest, GenerateFileNameFormats) {
            FileExportStrategy exporter("/tmp");

            // Просто проверяем, что функция возвращает непустую строку
            // с правильным расширением для разных типов
            std::string html_name = exporter.generateFileName("text/html");
            EXPECT_TRUE(html_name.find(".html") != std::string::npos);

            std::string pdf_name = exporter.generateFileName("application/pdf");
            EXPECT_TRUE(pdf_name.find(".pdf") != std::string::npos);

            std::string txt_name = exporter.generateFileName("text/plain");
            EXPECT_TRUE(txt_name.find(".txt") != std::string::npos);

            std::string md_name = exporter.generateFileName("text/markdown");
            EXPECT_TRUE(md_name.find(".md") != std::string::npos);

            std::string unknown_name = exporter.generateFileName("unknown/type");
            EXPECT_TRUE(unknown_name.find(".out") != std::string::npos);
        }

    } // namespace test
} // namespace report_system
