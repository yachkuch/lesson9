cmake_minimum_required(VERSION 3.20.0)
project(logger VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(HEAD async/async.h
         server/Server.h)
set(SOURCES async/async.cpp
            server/Server.cpp)

find_package(Boost CONFIG REQUIRED)
link_libraries(Boost::boost)

add_library(asynce SHARED ${HEAD} ${SOURCES})

add_executable(logger main.cpp ${HEAD} ${SOURCES})

set_target_properties(logger   PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories( logger PRIVATE async server)
#target_link_libraries(logger PRIVATE asynce)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

#if(Boost_found)
target_link_libraries(logger ${Boost_LIBRARIES})
#else()
#message(FATAL_ERROR,"BOOST NOT FOUND!!")
#endif()


include(CPack)
