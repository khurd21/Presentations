cmake_minimum_required(VERSION 3.10)
project(Presentations LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

set(sources
        src/main.cpp
        src/MainWindow.cpp
        src/CanvasView.cpp
        src/SlideWidget.cpp
        src/SlidePreviewDelegate.cpp
        src/SlidePreviewListView.cpp
        src/ThemeManager.cpp
)

set(includes
        include/presentations/MainWindow.hpp
        include/presentations/CanvasView.hpp
        include/presentations/SlideWidget.hpp
        include/presentations/SlidePreviewDelegate.hpp
        include/presentations/SlidePreviewListView.hpp
        include/presentations/ThemeManager.hpp
)

set(ui
        src/MainWindow.ui
)

set(resources
        resources/themes/themes.json
        resources/themes/themes.qrc
)

qt_add_executable(Presentations ${sources} ${includes} ${ui} ${resources})
qt_add_resources(Presentations
        FILES
        resources/themes/themes.qrc
)

target_include_directories(Presentations PRIVATE include)

target_link_libraries(Presentations PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)