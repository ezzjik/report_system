#ifndef REPORTSYSTEM_MOCKDATAPROCESSOR_H
#define REPORTSYSTEM_MOCKDATAPROCESSOR_H

#include "../../include/core/DataProcessor.h"

#include <gmock/gmock.h>

namespace report_system {

    class MockDataProcessor: public DataProcessor {
    public:
        MOCK_METHOD(DataResult, process, (DataResult input), (override));
        MOCK_METHOD(std::string, getName, (), (const override));
        MOCK_METHOD(void, setProcessFunction, (ProcessFunction func), (override));
    };

} // namespace report_system

#endif // REPORTSYSTEM_MOCKDATAPROCESSOR_H
