set(PROJECT_NAME server)

project(${PROJECT_NAME} LANGUAGES CXX)

set(SERVER_SOURCES
    server.cpp           server.hpp
    main_server.cpp
)

add_executable(${PROJECT_NAME} ${SERVER_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)