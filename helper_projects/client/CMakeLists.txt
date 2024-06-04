set(PROJECT_NAME client)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CLIENT_SOURCES
    client.cpp           client.hpp
    main_client.cpp
)

add_executable(${PROJECT_NAME} ${CLIENT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)