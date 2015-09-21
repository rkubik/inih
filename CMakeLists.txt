cmake_minimum_required (VERSION 2.8)

project (inih)
set(CMAKE_INSTALL_PREFIX "/") 

set(MAJOR_REV 0)
set(MINOR_REV 2)
set(PATCH_REV 0)

message("Major = ${MAJOR_REV}")
message("Minor = ${MINOR_REV}")
message("Patch = ${PATCH_REV}")

add_subdirectory( include )
add_subdirectory( lib )

