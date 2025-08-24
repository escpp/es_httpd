cmake_minimum_required(VERSION 3.10)
project(es_admin)

set(CMAKE_CXX_STANDARD 17)

# Find libhv
message(STATUS "Looking for libhv in: /usr/local/lib/cmake")
set(libhv_DIR /usr/local/lib/cmake)
find_package(libhv REQUIRED)
if(libhv_FOUND)
  message(STATUS "Found libhv includes: ${LIBHV_INCLUDE_DIRS}")
  message(STATUS "Found libhv libraries: ${LIBHV_LIBRARIES}")
  message(STATUS "Library paths: ${LIBHV_LIBRARY_DIRS}")
endif()

include_directories(include ${LIBHV_INCLUDE_DIRS})

# 静态库
add_library(es_httpd_static STATIC src/es_httpd/server.cc)
set_target_properties(es_httpd_static PROPERTIES OUTPUT_NAME "es_httpd")

# 动态库
add_library(es_httpd_shared SHARED src/es_httpd/server.cc)
set_target_properties(es_httpd_shared PROPERTIES OUTPUT_NAME "es_httpd")

# Example executable
add_executable(es_httpd example/es_httpd.cc)
target_link_libraries(es_httpd es_httpd_static /usr/local/lib/libhv.so pthread)

# Install headers
install(DIRECTORY include/es_httpd
        DESTINATION include
        FILES_MATCHING PATTERN "*.h")

# Install shared library
install(TARGETS es_httpd_shared
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

# Install static library
install(TARGETS es_httpd_static
        ARCHIVE DESTINATION lib)
