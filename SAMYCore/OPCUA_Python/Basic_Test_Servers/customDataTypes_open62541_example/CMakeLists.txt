cmake_minimum_required(VERSION 3.0...3.12)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Unions_example VERSION 0.1 LANGUAGES C CXX)
# open62541 v1.2 must be installed!
# If in custom path, then use -DCMAKE_PREFIX_PATH=/home/user/installcmake_minimum_required(VERSION 3.2)
find_package(open62541 1.2 REQUIRED COMPONENTS FullNamespace)

set(GENERATE_OUTPUT_DIR "${CMAKE_BINARY_DIR}/src_generated/")
include_directories("${GENERATE_OUTPUT_DIR}")
file(MAKE_DIRECTORY "${GENERATE_OUTPUT_DIR}")

add_executable(client
               "client_types_custom.c"
               )

add_executable(server
               "server_types_custom.c"
               )

target_link_libraries(client PRIVATE open62541::open62541)
target_link_libraries(server PRIVATE open62541::open62541)

