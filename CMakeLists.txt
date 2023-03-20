cmake_minimum_required(VERSION 3.5)

project(CPPTutorials LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##### Find Packages #####

##### Includes #####
include_directories(include)

##### Libraries #####
add_library(${PROJECT_NAME}_singleton src/TestSingleton.cpp)
add_library(${PROJECT_NAME}_box src/Box.cpp)

##### Executables #####
add_executable(${PROJECT_NAME}_main
    src/nodes/main.cpp
)
target_link_libraries(${PROJECT_NAME}_main
    ${PROJECT_NAME}_singleton
    ${PROJECT_NAME}_box
)
add_dependencies(${PROJECT_NAME}_main
    ${PROJECT_NAME}_singleton
    ${PROJECT_NAME}_box
)

add_executable(${PROJECT_NAME}_concurrency_main
    src/nodes/concurrency_main.cpp
)
target_link_libraries(${PROJECT_NAME}_concurrency_main
    ${PROJECT_NAME}_singleton
    ${PROJECT_NAME}_box
)
add_dependencies(${PROJECT_NAME}_concurrency_main
    ${PROJECT_NAME}_singleton
    ${PROJECT_NAME}_box
)

##### Install #####
install(TARGETS ${PROJECT_NAME}_main
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS ${PROJECT_NAME}_concurrency_main
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
