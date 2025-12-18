# Библиотека ядра системы отчётов
add_library(ReportSystemCore
    core/Report.cpp
)

# Библиотека поставщиков данных
add_library(ReportSystemDataProviders
    data_providers/CsvDataProvider.cpp
)

# Библиотека обработчиков данных
add_library(ReportSystemDataProcessors
    data_processors/FilterProcessor.cpp
)

# Библиотека форматировщиков
add_library(ReportSystemFormatters
    formatters/HtmlFormatter.cpp
)

# Библиотека стратегий экспорта
add_library(ReportSystemExportStrategies
    export_strategies/FileExportStrategy.cpp
)

# Библиотека строителей
add_library(ReportSystemBuilders
    builders/ReportBuilder.cpp
)

# Библиотека фабрик
add_library(ReportSystemFactories
    factories/ReportFactory.cpp
    factories/SalesReportFactory.cpp
)

# Библиотека декораторов
add_library(ReportSystemDecorators
    decorators/LoggingDecorator.cpp
)

# Основная библиотека системы отчётов (объединяет все компоненты)
add_library(ReportSystem
    $<TARGET_OBJECTS:ReportSystemCore>
    $<TARGET_OBJECTS:ReportSystemDataProviders>
    $<TARGET_OBJECTS:ReportSystemDataProcessors>
    $<TARGET_OBJECTS:ReportSystemFormatters>
    $<TARGET_OBJECTS:ReportSystemExportStrategies>
    $<TARGET_OBJECTS:ReportSystemBuilders>
    $<TARGET_OBJECTS:ReportSystemFactories>
    $<TARGET_OBJECTS:ReportSystemDecorators>
)

# Настройка свойств библиотеки
target_include_directories(ReportSystemCore
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(ReportSystemDataProviders
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(ReportSystemDataProcessors
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(ReportSystemFormatters
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(ReportSystemExportStrategies
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(ReportSystemBuilders
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(ReportSystemFactories
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(ReportSystemDecorators
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

# Все библиотеки наследуют настройки от ReportSystemCore
target_link_libraries(ReportSystemDataProviders ReportSystemCore)
target_link_libraries(ReportSystemDataProcessors ReportSystemCore)
target_link_libraries(ReportSystemFormatters ReportSystemCore)
target_link_libraries(ReportSystemExportStrategies ReportSystemCore)
target_link_libraries(ReportSystemBuilders ReportSystemCore)
target_link_libraries(ReportSystemFactories ReportSystemCore ReportSystemBuilders)
target_link_libraries(ReportSystemDecorators ReportSystemCore)

# Основная библиотека линкует все компоненты
target_link_libraries(ReportSystem
    ReportSystemCore
    ReportSystemDataProviders
    ReportSystemDataProcessors
    ReportSystemFormatters
    ReportSystemExportStrategies
    ReportSystemBuilders
    ReportSystemFactories
    ReportSystemDecorators
)

# Настройки для C++17
target_compile_features(ReportSystem PRIVATE cxx_std_17)

# Предупреждения компилятора
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(ReportSystem PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
