cmake_minimum_required(VERSION 3.11)

project(MyApp)

#compiler adjustments
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#prepare conan
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.14/conan.cmake"
				 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

#resolve dependencies
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP CMAKE_TARGETS BUILD missing BUILD_TYPE ${CONAN_BUILD_TYPE})

#find locations
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#list cpp files
set(SlibModuleName SApp)
add_library(${SlibModuleName} src/slib.cpp)
target_include_directories(${SlibModuleName} PUBLIC include)
target_link_libraries(${SlibModuleName} PRIVATE
    CONAN_PKG::fmt
)

set(DlibModuleName DApp)
add_library(${DlibModuleName} SHARED src/dlib.cpp)
target_include_directories(${DlibModuleName} PUBLIC include)
target_link_libraries(${DlibModuleName} PRIVATE ${SlibModuleName})

#add exe module with include folder and source files above
set(ExeModuleName MyApp)
add_executable(${ExeModuleName} src/exec.cpp)
target_include_directories(${ExeModuleName} PRIVATE include)
target_link_libraries(${ExeModuleName} PRIVATE ${DlibModuleName})
