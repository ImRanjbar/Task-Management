cmake_minimum_required(VERSION 3.5)

project(TaskManagement VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        GUI/mainwindow.cpp
        GUI/mainwindow.h
        GUI/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TaskManagement
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Images/Images.qrc
        GUI/HomeWindow.h GUI/HomeWindow.cpp GUI/HomeWindow.ui
        MyBinaryTree.h MyBinaryTree.cpp
        Task.h Task.cpp
        TaskManagement.h TaskManagement.cpp
        User.h User.cpp
        SubTask.h SubTask.cpp
        FileManager.h FileManager.cpp
        Date.h Date.cpp
        GUI/TaskWindow.h GUI/TaskWindow.cpp GUI/TaskWindow.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TaskManagement APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TaskManagement SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TaskManagement
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TaskManagement PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(TaskManagement PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS TaskManagement
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TaskManagement)
endif()
