cmake_minimum_required(VERSION 3.16)
project(TodoList VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt")
find_package(Qt6 COMPONENTS Widgets Sql REQUIRED)

# Define executable
add_executable(TodoList
    src/main.cpp
    src/controller/EventManager.h
    src/controller/EventManager.cpp
    src/database/DatabaseManager.h
    src/database/DatabaseManager.cpp
    src/view/MainWindow.h
    src/view/MainWindow.cpp
    src/model/Models.h
)

target_include_directories(TodoList PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/model
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database
    ${CMAKE_CURRENT_SOURCE_DIR}/src/controller
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view
    )

target_link_libraries(TodoList PRIVATE Qt6::Widgets Qt6::Sql)