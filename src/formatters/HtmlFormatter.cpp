#include "formatters/HtmlFormatter.h"
#include "data_providers/CsvDataProvider.h"

#include <sstream>
#include <memory>

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

        // Начинаем таблицу
        html << "<table border=\"1\">\n";

        // Определяем имена колонок для CSV данных
        std::vector<std::string> column_names;

        if (!data.data.empty()) {
            const CsvDataRecord* csv_record = dynamic_cast<const CsvDataRecord*>(data.data[0].get());
            if (csv_record && csv_record->size() > 0 && include_column_names_) {
                // Используем стандартные имена колонок для CSV
                // Предполагаем структуру: quarter, region, product, sales, profit
                std::vector<std::string> default_names = {"Quarter", "Region", "Product", "Sales", "Profit"};
                for (size_t i = 0; i < std::min(csv_record->size(), default_names.size()); ++i) {
                    column_names.push_back(default_names[i]);
                }
                // Если колонок больше, чем стандартных имен
                for (size_t i = default_names.size(); i < csv_record->size(); ++i) {
                    column_names.push_back("Column " + std::to_string(i + 1));
                }
            }
        }

        // Добавляем заголовок таблицы, если нужно
        if (!column_names.empty()) {
            html << "  <tr>\n";
            for (const auto& col_name : column_names) {
                html << "    <th>" << col_name << "</th>\n";
            }
            html << "  </tr>\n";
        }

        // Добавляем строки данных
        size_t record_count = 0;
        for (const auto& record_ptr : data.data) {
            const CsvDataRecord* csv_record = dynamic_cast<const CsvDataRecord*>(record_ptr.get());
            if (csv_record) {
                html << "  <tr>\n";
                for (size_t i = 0; i < csv_record->size(); ++i) {
                    html << "    <td>" << csv_record->getField(i) << "</td>\n";
                }
                html << "  </tr>\n";
                record_count++;
            }
        }

        // Если данных нет, показываем сообщение
        if (record_count == 0) {
            html << "  <tr><td colspan=\"" << (column_names.empty() ? 1 : column_names.size())
                 << "\">No data available after filtering</td></tr>\n";
        }

        html << "</table>\n";

        // Добавляем статистику
        html << "<p>Total records: " << record_count << "</p>\n";

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
