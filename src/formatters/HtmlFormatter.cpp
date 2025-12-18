#include "formatters/HtmlFormatter.h"

#include <sstream>

namespace report_system {

    FormattedReport HtmlFormatter::format(const DataResult& data) {
        FormattedReport report;

        if (!data.success) {
            report.content = "<html><body><h1>Error: " + data.error_message + "</h1></body></html>";
            report.mime_type = "text/html";
            report.is_valid = false;
            return report;
        }

        std::ostringstream html;
        html << "<!DOCTYPE html>\n";
        html << "<html>\n";
        html << "<head>\n";
        html << "  <meta charset=\"UTF-8\">\n";
        html << "  <title>" << title_ << "</title>\n";
        if (!table_style_.empty()) {
            html << "  <style>\n";
            html << "    table {" << table_style_ << "}\n";
            html << "  </style>\n";
        }
        html << "</head>\n";
        html << "<body>\n";
        html << "<h1>" << title_ << "</h1>\n";
        html << "<table border=\"1\">\n";

        // Здесь должна быть логика преобразования данных в строки таблицы
        // Временно заглушка
        html << "  <tr><td>Data records count:</td><td>" << data.data.size() << "</td></tr>\n";

        html << "</table>\n";
        html << "</body>\n";
        html << "</html>\n";

        report.content = html.str();
        report.mime_type = "text/html";
        report.is_valid = true;
        return report;
    }

    std::string HtmlFormatter::getName() const {
        return "HtmlFormatter";
    }

    std::string HtmlFormatter::getOutputType() const {
        return "text/html";
    }

    void HtmlFormatter::setTableStyle(const std::string& style) {
        table_style_ = style;
    }

    void HtmlFormatter::setTitle(const std::string& title) {
        title_ = title;
    }

    void HtmlFormatter::includeColumnNames(bool include) {
        include_column_names_ = include;
    }

} // namespace report_system
