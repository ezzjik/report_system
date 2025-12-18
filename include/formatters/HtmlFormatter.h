#ifndef REPORTSYSTEM_HTMLFORMATTER_H
#define REPORTSYSTEM_HTMLFORMATTER_H

#include "../core/Formatter.h"

#include <memory>
#include <string>

namespace report_system {

    // Форматировщик в HTML
    class HtmlFormatter: public Formatter {
    public:
        HtmlFormatter() = default;

        // Реализация абстрактных методов
        FormattedReport format(const DataResult& data) override;
        std::string getName() const override;
        std::string getOutputType() const override;

        // Дополнительные методы для настройки HTML
        void setTableStyle(const std::string& style);
        void setTitle(const std::string& title);
        void includeColumnNames(bool include);

    private:
        std::string table_style_;
        std::string title_;
        bool include_column_names_{true};
    };

} // namespace report_system

#endif // REPORTSYSTEM_HTMLFORMATTER_H
