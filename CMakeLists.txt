cmake_minimum_required(VERSION 3.5)

project(toojpeg_omp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    message(STATUS "Found OpenCV: ${OpenCV_VERSION}")
    include_directories( ${OpenCV_INCLUDE_DIRS} )
else()
    message(FATAL_ERROR "OpenCV not found. Please check the CMAKE_PREFIX_PATH.")
endif()

find_package(OpenMP REQUIRED)

add_executable(toojpeg_omp main.cpp toojpeg.cpp toojpeg.h run_test.h run_test.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/images/ DESTINATION ${CMAKE_BINARY_DIR}/images/)

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

target_link_libraries(toojpeg_omp PRIVATE ${OpenCV_LIBS})
target_link_libraries(toojpeg_omp PRIVATE OpenMP::OpenMP_CXX)

install(TARGETS toojpeg_omp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
