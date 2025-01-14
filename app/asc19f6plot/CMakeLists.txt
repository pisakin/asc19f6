cmake_minimum_required(VERSION 3.1.0)

project(ascemspline 
    VERSION 1.0.0 
    DESCRIPTION "Template for C++ library built with CMake"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core REQUIRED)


add_executable(ascemspline
    ../../src/cascem.h
    ../../src/cascem.cpp 
    ../../src/cascemex.h
    ../../src/cascemex.cpp 
    ../../src/cascemdevice.h
    ../../src/cascemdevice.cpp 
    ../../src/casceminput.h
    ../../src/casceminput.cpp 
    ../../src/cascemthread.h
    ../../src/cascemthread.cpp 
    ../../src/cascemspline.h
    ../../src/cascemspline.cpp 
    main.cpp
)

qt5_use_modules(ascemspline Core  Xml PrintSupport Charts)


# add_subdirectory(QCustomPlot-library) # Or if library is put in a folder "dependencies" : 
# add_subdirectory(dependencies/QCustomPlot-library)
# Link needed libraries
# QCustomPlot library
target_link_libraries(ascemspline qcustomplot)

# Compile needed definitions
# target_compile_definitions(ascemspline PRIVATE QCUSTOMPLOT_USE_LIBRARY)

target_link_libraries(ascemspline qwt-qt5)

install(TARGETS ascemspline)