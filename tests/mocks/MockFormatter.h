#ifndef REPORTSYSTEM_MOCKFORMATTER_H
#define REPORTSYSTEM_MOCKFORMATTER_H

#include "../../include/core/Formatter.h"

#include <gmock/gmock.h>

namespace report_system {

    class MockFormatter: public Formatter {
    public:
        MOCK_METHOD(FormattedReport, format, (const DataResult& data), (override));
        MOCK_METHOD(std::string, getName, (), (const override));
        MOCK_METHOD(std::string, getOutputType, (), (const override));
    };

} // namespace report_system

#endif // REPORTSYSTEM_MOCKFORMATTER_H
