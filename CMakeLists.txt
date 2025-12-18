cmake_minimum_required(VERSION 3.16)
project(ReportSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)

find_program(CLANG_FORMAT_EXE NAMES clang-format)
if(CLANG_FORMAT_EXE)
    # Находим все файлы .h и .cpp в проекте
    file(GLOB_RECURSE ALL_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
    file(GLOB_RECURSE ALL_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
    
    # Объединяем списки файлов
    set(ALL_CODE_FILES ${ALL_HEADER_FILES} ${ALL_SOURCE_FILES})
    
    add_custom_target(check-style
        COMMAND ${CLANG_FORMAT_EXE} --dry-run -Werror --style=file:${CMAKE_CURRENT_SOURCE_DIR}/.clang-format ${ALL_CODE_FILES}
        COMMENT "Проверка стиля кода с помощью clang-format (Yandex Style)"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    
    add_custom_target(fix-style
        COMMAND ${CLANG_FORMAT_EXE} -i --style=file:${CMAKE_CURRENT_SOURCE_DIR}/.clang-format ${ALL_CODE_FILES}
        COMMENT "Автоматическое исправление стиля кода"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    
    message(STATUS "clang-format найден: ${CLANG_FORMAT_EXE}")
else()
    message(WARNING "clang-format не найден. Цели check-style и fix-style не будут доступны.")
endif()
