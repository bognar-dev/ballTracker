cmake_minimum_required (VERSION 3.16...3.19)
set (EXECUTABLENAME EDALTPUDispenserGTest)
project(${EXECUTABLENAME})

#Append cmake dir to module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}")
list(PREPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")

#Add install to VS; set install dir to build_xxx/out

set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD OFF)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/out)
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY TRUE)

#Set temp directory for all runtime output, this is needed for the unit tests

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

set(HEADERS
)

set(SOURCE_FILES
main.cpp

)

set(RESOURCES)



find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )


add_executable(${EXECUTABLENAME} ${SOURCE_FILES} ${HEADERS} ${RESOURCES})




target_link_libraries(${EXECUTABLENAME}
${OpenCV_LIBS} 
)
