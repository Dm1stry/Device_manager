set(PROJECT_NAME expressions)

project(${PROJECT_NAME} LANGUAGES CXX)

find_package(nlohmann_json REQUIRED)
find_path(EXPRTK_INCLUDE_DIRS "exprtk.hpp")

set(SOURCES
    expressions.cpp
    ../../devices/base/command.hpp                     ../../devices/base/command.cpp
    ../../operator/deviceloader/basesavable.hpp        ../../operator/deviceloader/basesavable.cpp
    #customlistwidget.hpp        customlistwidget.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    nlohmann_json::nlohmann_json
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${EXPRTK_INCLUDE_DIRS}
    ../../
)

target_compile_options(${PROJECT_NAME} PRIVATE 
"/bigobj"
)