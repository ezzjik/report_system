#include <gtest/gtest.h>
#include "export_strategies/FileExportStrategy.h"
#include "core/Formatter.h"

TEST(ErrorHandlingTest, ExportStrategyFailure) {
    // Используем путь, который является файлом, а не директорией
    // Сначала создадим файл
    std::string temp_file = "/tmp/test_file_not_dir.txt";
    FILE* f = fopen(temp_file.c_str(), "w");
    if (f) {
        fclose(f);
    }

    // Конструктор FileExportStrategy пытается создать директорию,
    // но путь указывает на файл - должно выбросить исключение
    EXPECT_THROW(std::make_unique<report_system::FileExportStrategy>(temp_file), std::exception);

    // Удаляем временный файл
    remove(temp_file.c_str());
}
