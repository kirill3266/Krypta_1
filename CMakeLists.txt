cmake_minimum_required(VERSION 3.23)
project(Krypta_1)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost COMPONENTS locale REQUIRED)


if (Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})
endif ()

add_executable(Krypta_1 main.cpp)


target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})