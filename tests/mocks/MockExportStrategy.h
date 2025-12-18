#ifndef REPORTSYSTEM_MOCKEXPORTSTRATEGY_H
#define REPORTSYSTEM_MOCKEXPORTSTRATEGY_H

#include "../../include/core/ExportStrategy.h"

#include <gmock/gmock.h>

namespace report_system {

    class MockExportStrategy: public ExportStrategy {
    public:
        MOCK_METHOD(bool, exportReport, (const FormattedReport& report), (override));
        MOCK_METHOD(std::string, getName, (), (const override));
        MOCK_METHOD(std::string, getDestinationInfo, (), (const override));
    };

} // namespace report_system

#endif // REPORTSYSTEM_MOCKEXPORTSTRATEGY_H
