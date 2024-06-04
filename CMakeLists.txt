cmake_minimum_required(VERSION 3.24)

set(PROJECT_NAME Reditom)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt5 COMPONENTS PrintSupport Core Widgets Network Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport Core Widgets Network Gui REQUIRED)
find_package(nlohmann_json REQUIRED)
find_path(EXPRTK_INCLUDE_DIRS "exprtk.hpp")

qt5_add_resources(RES resources/resources.qrc)

set(W_DIR widgets)  # Widgets directory
set(SW_DIR ${W_DIR}/subwidgets)  # Subwidgets directory
set(DW_DIR devices)  # Device directory
set(SEW_DIR ${W_DIR}/settingswidgets)  # Settings widgets directory

set(PR_DIR ${DW_DIR}/programmer)

# Папка device_editor
set(PR_DEVICE_EDITOR_DIR ${PR_DIR}/device_editor)
set(PR_COMMANDS_EDITOR_DIR ${PR_DEVICE_EDITOR_DIR}/commands_editor)
set(PR_COMMAND_LINE_DIR ${PR_COMMANDS_EDITOR_DIR}/command_line)

# Папка sequence_editor
set(PR_SEQUENCE_DIR ${PR_DIR}/sequence_editor)
set(PR_ITEMS_DIR ${PR_SEQUENCE_DIR}/items)
set(PR_COMMAND_ITEMS_DIR ${PR_ITEMS_DIR}/command_items)
set(PR_COMMAND_TYPE_DIR ${PR_COMMAND_ITEMS_DIR}/command_style)
set(PR_EVENTS_DIR ${PR_ITEMS_DIR}/events)
set(PR_INTERVAL_DIR ${PR_EVENTS_DIR}/interval)

# Папка synchrodevices
set(PR_DEVICE_DIR ${PR_DIR}/synchrodevices)
set(PR_DEVICE_WIDGET_DIR ${PR_DEVICE_DIR}/syncdevicewidget)
set(PR_COMMAND_BLOCK_DIR ${PR_DEVICE_DIR}/command_block)
set(PR_COMMAND_SETTINGS_DIR ${PR_COMMAND_BLOCK_DIR}/command_settings)


set(PR_WIDGETS
    ${PR_DIR}/programmerdevicewidget.hpp                ${PR_DIR}/programmerdevicewidget.cpp

    # ------------------------------------------------------------------------------------------------ Папка device_editor
    ${PR_DEVICE_EDITOR_DIR}/editor_size.hpp           
    ${PR_DEVICE_EDITOR_DIR}/device_editor.cpp           ${PR_DEVICE_EDITOR_DIR}/device_editor.hpp

    ${PR_COMMANDS_EDITOR_DIR}/command_block_editor.cpp  ${PR_COMMANDS_EDITOR_DIR}/command_block_editor.hpp

    ${PR_COMMAND_LINE_DIR}/command_line_editor.cpp      ${PR_COMMAND_LINE_DIR}/command_line_editor.hpp

    # ------------------------------------------------------------------------------------------------ Папка sequence_editor
    ${PR_SEQUENCE_DIR}/graphics.hpp                     ${PR_SEQUENCE_DIR}/graphics.cpp
    ${PR_SEQUENCE_DIR}/graphics_view.cpp                ${PR_SEQUENCE_DIR}/graphics_view.hpp
    ${PR_SEQUENCE_DIR}/coordinates.hpp  

    ${PR_ITEMS_DIR}/device_axes.cpp                     ${PR_ITEMS_DIR}/device_axes.hpp

    ${PR_COMMAND_ITEMS_DIR}/command_area.cpp            ${PR_COMMAND_ITEMS_DIR}/command_area.hpp
    ${PR_COMMAND_ITEMS_DIR}/style_headers.hpp

    ${PR_COMMAND_TYPE_DIR}/base_command_style.cpp       ${PR_COMMAND_TYPE_DIR}/base_command_style.hpp
    ${PR_COMMAND_TYPE_DIR}/pulse_command.cpp            ${PR_COMMAND_TYPE_DIR}/pulse_command.hpp
    ${PR_COMMAND_TYPE_DIR}/lock_command.cpp             ${PR_COMMAND_TYPE_DIR}/lock_command.hpp

    ${PR_EVENTS_DIR}/baseevent.cpp                      ${PR_EVENTS_DIR}/baseevent.hpp

    ${PR_INTERVAL_DIR}/interval.cpp                     ${PR_INTERVAL_DIR}/interval.hpp
    ${PR_INTERVAL_DIR}/interval_header.cpp              ${PR_INTERVAL_DIR}/interval_header.hpp

    # ------------------------------------------------------------------------------------------------ Папка synchrodevices
    ${PR_DEVICE_DIR}/sync_basedevice.cpp                ${PR_DEVICE_DIR}/sync_basedevice.hpp
    
    ${PR_DEVICE_WIDGET_DIR}/sync_device_widget.cpp      ${PR_DEVICE_WIDGET_DIR}/sync_device_widget.hpp

    ${PR_COMMAND_BLOCK_DIR}/command_block.cpp           ${PR_COMMAND_BLOCK_DIR}/command_block.hpp
    ${PR_COMMAND_BLOCK_DIR}/block_data.cpp              ${PR_COMMAND_BLOCK_DIR}/block_data.hpp
    ${PR_COMMAND_BLOCK_DIR}/arguments.cpp               ${PR_COMMAND_BLOCK_DIR}/arguments.hpp

    ${PR_COMMAND_SETTINGS_DIR}/argument_settings_widget.cpp          ${PR_COMMAND_SETTINGS_DIR}/argument_settings_widget.hpp
    ${PR_COMMAND_SETTINGS_DIR}/block_settings_widget.cpp             ${PR_COMMAND_SETTINGS_DIR}/block_settings_widget.hpp

)

qt5_wrap_ui(UI_HEADERS
    ${DW_DIR}/samplepositioning/samplepositioningdevicewidget.ui
    ${DW_DIR}/adc/adcdevicewidget.ui
)

set(WIDGETS
    ${SEW_DIR}/settingswindow.hpp               ${SEW_DIR}/settingswindow.cpp
    ${SEW_DIR}/baseconnectionsettingswidget.hpp ${SEW_DIR}/baseconnectionsettingswidget.cpp
    ${SEW_DIR}/udpsettingswidget.hpp            ${SEW_DIR}/udpsettingswidget.cpp  

    ${W_DIR}/mainwindow.hpp                     ${W_DIR}/mainwindow.cpp
    ${W_DIR}/mainwidget.hpp                     ${W_DIR}/mainwidget.cpp
    ${W_DIR}/sidemenuwidget.hpp                 ${W_DIR}/sidemenuwidget.cpp

    ${SW_DIR}/horizontaltabbar.hpp              ${SW_DIR}/horizontaltabbar.cpp
    ${SW_DIR}/customlistwidget.hpp              ${SW_DIR}/customlistwidget.cpp

    ${DW_DIR}/base/basedevicewidget.hpp                             ${DW_DIR}/base/basedevicewidget.cpp
    ${DW_DIR}/universal/universaldevicewidget.hpp                   ${DW_DIR}/universal/universaldevicewidget.cpp
    #${DW_DIR}/thermoblock/thermoblockdevicewidget.hpp               ${DW_DIR}/thermoblock/thermoblockdevicewidget.cpp
    ${DW_DIR}/rf/rfdevicewidget.hpp                                 ${DW_DIR}/rf/rfdevicewidget.cpp
    ${DW_DIR}/samplepositioning/spd_tickmarkslider.hpp              ${DW_DIR}/samplepositioning/spd_tickmarkslider.cpp
    ${DW_DIR}/samplepositioning/samplepositioningdevicewidget.hpp   ${DW_DIR}/samplepositioning/samplepositioningdevicewidget.cpp

    #${DW_DIR}/adc/qcustomplot.h                                      ${DW_DIR}/adc/qcustomplot.cpp
    #${DW_DIR}/adc/adcdevicewidget.hpp                               ${DW_DIR}/adc/adcdevicewidget.cpp

    ${DW_DIR}/scheduler/schedulerdevicewidget.hpp                   ${DW_DIR}/scheduler/schedulerdevicewidget.cpp
    ${DW_DIR}/scheduler/taskwidget.hpp                              ${DW_DIR}/scheduler/taskwidget.cpp
    ${DW_DIR}/scheduler/task.hpp                                    ${DW_DIR}/scheduler/task.cpp
    #${DW_DIR}/scheduler/timertask.hpp                               ${DW_DIR}/scheduler/timertask.cpp
    #${DW_DIR}/scheduler/singlefieldtask.hpp                         ${DW_DIR}/scheduler/singlefieldtask.cpp


    ${PR_WIDGETS}
)

set(OP_DIR operator)  # Operator files directory
set(OP_CON_DIR ${OP_DIR}/connection)  # Connection classes directory
set(OP_F_DIR ${OP_DIR}/formatter)  # Sended data formatter directory
set(OP_DL_DIR ${OP_DIR}/deviceloader)  # Device Loader/Saver directory

set(OPERATOR
    ${OP_DIR}/operator.hpp                          ${OP_DIR}/operator.cpp

    ${OP_CON_DIR}/baseconnection.hpp                ${OP_CON_DIR}/baseconnection.cpp
    ${OP_CON_DIR}/udpconnection.hpp                 ${OP_CON_DIR}/udpconnection.cpp

    ${OP_F_DIR}/basecommandformatter.hpp
    ${OP_F_DIR}/controlbyteformatter.hpp            ${OP_F_DIR}/controlbyteformatter.cpp
    ${OP_F_DIR}/requestformatter.hpp                ${OP_F_DIR}/requestformatter.cpp

    ${OP_DL_DIR}/basesavable.hpp                    ${OP_DL_DIR}/basesavable.cpp
    ${OP_DL_DIR}/deviceloader.hpp                   ${OP_DL_DIR}/deviceloader.cpp
    )

set(PROJECT_SOURCES
    main.cpp
            
    devices/base/command.hpp                        devices/base/command.cpp
    
    helpers/ipvalidator.hpp                         helpers/ipvalidator.cpp
    ${WIDGETS}
    ${OPERATOR}
    ${RES}
    ${UI_HEADERS}
)

add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::PrintSupport
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Core
    nlohmann_json::nlohmann_json
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    widgets/
    devices/
    ${EXPRTK_INCLUDE_DIRS}
)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_compile_options(${PROJECT_NAME} PRIVATE 
         "/bigobj"
    )
endif()

#set(HP_DIR helper_projects)

#add_subdirectory(${HP_DIR}/messenger)
#add_subdirectory(${HP_DIR}/client)
#add_subdirectory(${HP_DIR}/server)
#add_subdirectory(${HP_DIR}/scratch)
#add_subdirectory(${HP_DIR}/expressions)

#add_subdirectory(${HP_DIR}/commands_block)
