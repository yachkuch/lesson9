cmake_minimum_required(VERSION 3.20.0)
project(logger VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(HEAD async/async.h)
set(SOURCES async/async.cpp)

add_library(asynce SHARED ${HEAD} ${SOURCES})

add_executable(logger main.cpp)

set_target_properties(logger   PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

#target_include_directories( logger PRIVATE async)
target_link_libraries(logger PRIVATE asynce)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})



include(CPack)
