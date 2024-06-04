set(PROJECT_NAME messenger)

project(${PROJECT_NAME} LANGUAGES CXX)

set(MESSENGER_SOURCES
    messenger.cpp     messenger.hpp
    main_messenger.cpp
)

add_executable(${PROJECT_NAME} WIN32 ${MESSENGER_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)