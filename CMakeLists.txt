#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
SET(GCC_COVERAGE_COMPILE_FLAGS "-pthread -static-libgcc -static-libstdc++ -static")

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(SE3D)

#Visual Studio learning

# Turn on the ability to create folders to organize projects (.vcproj)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# Here it is setting the Visual Studio warning level to 4
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
# Useful for displaying errors, warnings, and debugging
message ("cxx Flags:" ${CMAKE_CXX_FLAGS})

#VS learning end

include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME "SE3D")
FILE (GLOB SOURCES src/*)
add_executable(${EXECUTABLE_NAME} ${SOURCES} src/thread.h)

#set(SFML_STATIC_LIBRARIES TRUE)

#Don't change this shit works
if(WIN32)
    set(SFML_ROOT "${PROJECT_SOURCE_DIR}/libs/SFML-2.4.2/")
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/libs/SFML-2.4.2/cmake/Modules")
endif()

if(APPLE)
    set(SFML_ROOT "${PROJECT_SOURCE_DIR}/libs/SFML-2.4.2-osx-clang/")
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/libs/SFML-2.4.2-osx-clang/cmake/Modules")
endif()

find_package(SFML 2.4 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SE3D ${SFML_LIBRARIES})
    target_link_libraries(SE3D ${SFML_DEPENDENCIES})
endif()

#Try for GLEW
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glew-2.0.0/build/cmake/)
include_directories(${PROJECT_SOURCE_DIR}/libs/glew-2.0.0/include)

#if this breaks windows again add a check to see if windows of not
target_link_libraries(SE3D glew)

#add_custom_command(TARGET SE3D POST_BUILD
#       COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/content $<TARGET_FILE_DIR:SE3D>/content)

#including glm
include_directories(${PROJECT_SOURCE_DIR}/libs/glm)

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

#target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_range_for)