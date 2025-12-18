#ifndef REPORTSYSTEM_MOCKDATAPROVIDER_H
#define REPORTSYSTEM_MOCKDATAPROVIDER_H

#include "../../include/core/DataProvider.h"

#include <gmock/gmock.h>

namespace report_system {

    class MockDataProvider: public DataProvider {
    public:
        MOCK_METHOD(DataResult, fetchData, (), (override));
        MOCK_METHOD(std::string, getName, (), (const override));
        MOCK_METHOD(bool, isAvailable, (), (const override));
    };

} // namespace report_system

#endif // REPORTSYSTEM_MOCKDATAPROVIDER_H
