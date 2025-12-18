# Простой пример использования фабрики
add_executable(SimpleFactoryExample
    simple/SimpleFactoryExample.cpp
)

target_include_directories(SimpleFactoryExample
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(SimpleFactoryExample
    ReportSystem
)

# Продвинутый пример с использованием строителя
add_executable(AdvancedBuilderExample
    advanced/AdvancedBuilderExample.cpp
)

target_include_directories(AdvancedBuilderExample
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(AdvancedBuilderExample
    ReportSystem
)

# Пример с декораторами
add_executable(DecoratorExample
    advanced/DecoratorExample.cpp
)

target_include_directories(DecoratorExample
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(DecoratorExample
    ReportSystem
)

# Установка примеров в bin/examples
install(TARGETS
    SimpleFactoryExample
    AdvancedBuilderExample
    DecoratorExample
    DESTINATION bin/examples
)
