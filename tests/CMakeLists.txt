# Юнит-тесты
add_executable(UnitTests
    main.cpp
    unit/ReportFactoryTest.cpp
    unit/DataProcessorTest.cpp
    unit/ExportStrategyTest.cpp
    unit/ReportBuilderTest.cpp
    unit/ErrorHandlingTest.cpp
)

target_link_libraries(UnitTests
    ReportSystem
    gtest
    gmock
    gtest_main
)

# Интеграционные тесты
add_executable(IntegrationTests
    main.cpp
    integration/FullReportPipelineTest.cpp
    integration/DecoratorTest.cpp
)

target_link_libraries(IntegrationTests
    ReportSystem
    gtest
    gmock
    gtest_main
)

# Добавляем тесты для запуска
add_test(NAME UnitTests COMMAND UnitTests)
add_test(NAME IntegrationTests COMMAND IntegrationTests)
