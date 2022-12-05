cmake_minimum_required(VERSION 3.21)
project(TCPNetworking)

set(CMAKE_CXX_STANDARD 20)


find_package(Boost 1.80.0 REQUIRED COMPONENTS)

file(GLOB SOURCES src/* src/*/* src/*/*/*)
add_library(${PROJECT_NAME} ${SOURCES})


target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            ${Boost_INCLUDE_DIRS}
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            ${Boost_LIBRARIES}
            ws2_32 # БЕЗ ЭТОЙ ХУЙНИ CLION НЕ ВИДИТ КОМПОНЕНТЫ!
            wsock32 # И БЕЗ ЭТОЙ ХУЙНИ ТОЖЕ НЕ РАБОТАЕТ СЕРВЕР
        )



