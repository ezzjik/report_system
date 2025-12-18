#ifndef REPORTSYSTEM_FILEEXPORTSTRATEGY_H
#define REPORTSYSTEM_FILEEXPORTSTRATEGY_H

#include "../core/ExportStrategy.h"

#include <memory>
#include <string>

namespace report_system {

    // Стратегия экспорта в файл
    class FileExportStrategy: public ExportStrategy {
    public:
        explicit FileExportStrategy(const std::string& directory_path);

        // Реализация абстрактных методов
        bool exportReport(const FormattedReport& report) override;
        std::string getName() const override;
        std::string getDestinationInfo() const override;

        // Установить путь к директории
        void setDirectory(const std::string& directory_path);

        // Генерация имени файла
        std::string generateFileName(const std::string& report_type) const;

    private:
        std::string directory_path_;
    };

} // namespace report_system

#endif // REPORTSYSTEM_FILEEXPORTSTRATEGY_H
