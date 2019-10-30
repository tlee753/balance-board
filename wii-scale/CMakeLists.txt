cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS program_options)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GIOMM REQUIRED giomm-2.4)

INCLUDE_DIRECTORIES(${GIOMM_INCLUDE_DIRS})

add_executable(wii-scale wii-scale.cpp XWiiMonitor.cpp XWiiIface.cpp UDev.cpp
                         UDevDevice.cpp BlueZDevice.cpp)

set_property(TARGET wii-scale PROPERTY CXX_STANDARD 11)
set_property(TARGET wii-scale PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(wii-scale ${Boost_LIBRARIES} pthread xwiimote
                                udev ${GIOMM_LIBRARIES})

file(GLOB CPP_FILES *.cpp)

add_custom_target(cppcheck ALL COMMAND cppcheck --quiet --error-exitcode=2
                  --enable=all --suppress=missingIncludeSystem --std=c++11
                  ${CPP_FILES}
                  DEPENDS wii-scale VERBATIM)
