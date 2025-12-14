cmake_minimum_required(VERSION 3.20)
project(TortureOfSisyphus VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

add_executable(torture-of-sisyphus
  src/main.cpp
  src/core/AppTimer.cpp
  src/ui/MainWindow.cpp
)

target_link_libraries(torture-of-sisyphus Qt6::Core Qt6::Widgets)
target_include_directories(torture-of-sisyphus PRIVATE src)
