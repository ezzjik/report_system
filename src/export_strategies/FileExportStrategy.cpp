#include "export_strategies/FileExportStrategy.h"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace report_system {

    FileExportStrategy::FileExportStrategy(const std::string& directory_path)
        : directory_path_(directory_path) {
        // Создаём директорию, если она не существует
        if (!directory_path.empty()) {
            std::filesystem::create_directories(directory_path);
        }
    }

    bool FileExportStrategy::exportReport(const FormattedReport& report) {
        if (!report.is_valid) {
            return false;
        }

        if (directory_path_.empty()) {
            return false;
        }

        std::string file_name = generateFileName(report.mime_type);
        std::filesystem::path file_path = std::filesystem::path(directory_path_) / file_name;

        try {
            std::ofstream file(file_path);
            if (!file.is_open()) {
                return false;
            }

            file << report.content;
            file.close();
            return true;
        } catch (const std::exception& e) {
            // В реальном коде здесь должно быть логирование ошибки
            return false;
        }
    }

    std::string FileExportStrategy::getName() const {
        return "FileExportStrategy";
    }

    std::string FileExportStrategy::getDestinationInfo() const {
        return "Directory: " + directory_path_;
    }

    void FileExportStrategy::setDirectory(const std::string& directory_path) {
        directory_path_ = directory_path;
        if (!directory_path.empty()) {
            std::filesystem::create_directories(directory_path);
        }
    }

    std::string FileExportStrategy::generateFileName(const std::string& report_type) const {
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);

        std::ostringstream oss;
        oss << "report_";
        oss << std::put_time(std::localtime(&time_t_now), "%Y%m%d_%H%M%S");

        // Добавляем расширение в зависимости от типа
        if (report_type == "text/html") {
            oss << ".html";
        } else if (report_type == "application/pdf") {
            oss << ".pdf";
        } else if (report_type == "text/plain") {
            oss << ".txt";
        } else if (report_type == "text/markdown") {
            oss << ".md";
        } else {
            oss << ".out";
        }

        return oss.str();
    }

} // namespace report_system
