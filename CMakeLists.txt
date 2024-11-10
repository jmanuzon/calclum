cmake_minimum_required(VERSION 3.5.0)
project(calclum VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCES
main.cpp
src/calclum.cpp
src/video.cpp
src/frame.cpp
)

set(HEADERS
include/helper.h
include/calclum.h
include/ctpl_stl.h
include/ffmpeg.h
include/video.h
include/frame.h
include/container.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PRIVATE include ffmpeg/include)
target_link_directories(${PROJECT_NAME} PRIVATE ffmpeg/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE avutil avformat avcodec)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/ffmpeg/bin"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

include(CTest)
enable_testing()

