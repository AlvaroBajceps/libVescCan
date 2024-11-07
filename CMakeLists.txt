cmake_minimum_required(VERSION 3.10)

project(libVescCan C)

# Set C and C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Remove lib prefix
set(CMAKE_STATIC_LIBRARY_PREFIX "")

# build lib
add_library(libVescCan STATIC
	src/libVescCan/VESC_Convert.c
	src/libVescCan/VESC_Endian.c
)

target_include_directories(libVescCan PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

# install lib
install(TARGETS libVescCan
	EXPORT libVescCan
	ARCHIVE DESTINATION lib
)

# install headers
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
	DESTINATION include
)

# Export the target to a CMake configuration file
install(EXPORT libVescCan
    FILE libVescCanConfig.cmake
    NAMESPACE libVescCan::
    DESTINATION lib/cmake/libVescCan
)
