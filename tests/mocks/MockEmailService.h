#ifndef REPORTSYSTEM_MOCKEMAILSERVICE_H
#define REPORTSYSTEM_MOCKEMAILSERVICE_H

#include <string>

#include <gmock/gmock.h>

namespace report_system {

    class EmailService {
    public:
        virtual ~EmailService() = default;
        virtual bool send(const std::string& content, const std::string& recipient) = 0;
        virtual std::string getServiceName() const = 0;
    };

    class MockEmailService: public EmailService {
    public:
        MOCK_METHOD(bool, send, (const std::string& content, const std::string& recipient), (override));
        MOCK_METHOD(std::string, getServiceName, (), (const override));
    };

} // namespace report_system

#endif // REPORTSYSTEM_MOCKEMAILSERVICE_H
