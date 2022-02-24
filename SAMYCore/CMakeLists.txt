cmake_minimum_required(VERSION 3.0...3.12)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

#macro(print_all_variables)
#    message(STATUS "print_all_variables------------------------------------------{")
#    get_cmake_property(_variableNames VARIABLES)
#    foreach (_variableName ${_variableNames})
#        message(STATUS "${_variableName}=${${_variableName}}")
#    endforeach()
#    message(STATUS "print_all_variables------------------------------------------}")
#endmacro()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#SET(CMAKE_CXX_FLAGS "-Wno-write-strings")

project(SAMYCore VERSION 0.1 LANGUAGES C CXX)
# open62541 v1.2 must be installed!
# If in custom path, then use -DCMAKE_PREFIX_PATH=/home/user/installcmake_minimum_required(VERSION 3.2)
find_package(open62541 REQUIRED COMPONENTS FullNamespace)
find_package( yaml-cpp REQUIRED )
find_package(Catch2 REQUIRED)
find_package(spdlog REQUIRED)

set(CMAKE_C_COMPILER "g++")
#set(CMAKE_CXX_COMPILER "g++")

#set(CMAKE_VERBOSE_MAKEFILE on)

set(GENERATE_OUTPUT_DIR "${CMAKE_BINARY_DIR}/src_generated/")
include_directories("${GENERATE_OUTPUT_DIR}")
file(MAKE_DIRECTORY "${GENERATE_OUTPUT_DIR}")

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src/OPCUA_Server/pubsub")
include_directories("${PROJECT_SOURCE_DIR}/src/OPCUA_Server/deps")
include_directories("${PROJECT_SOURCE_DIR}/src/OPCUA_Server/include")
include_directories("${PROJECT_SOURCE_DIR}/src/OPCUA_Server/include/open62541/plugin")
include_directories("${PROJECT_SOURCE_DIR}/src/OPCUA_Server/plugins/")
include_directories("${PROJECT_SOURCE_DIR}/src/OPCUA_Server/logging/include")
include_directories("${PROJECT_SOURCE_DIR}/src/Helpers/include")
include_directories("${PROJECT_SOURCE_DIR}/src/SAMYSkill/include")
include_directories("${PROJECT_SOURCE_DIR}/src/SAMYRobot/include")
include_directories("${PROJECT_SOURCE_DIR}/src/SAMYCoreInterfaceGenerator/include")
include_directories("${PROJECT_SOURCE_DIR}/src/SAMYCoreConfig/include")
include_directories("${PROJECT_SOURCE_DIR}/src/Parsers/include")
include_directories("${PROJECT_SOURCE_DIR}/src/Logging/include")
include_directories("${PROJECT_SOURCE_DIR}/src/InformationSource/include")
include_directories("${PROJECT_SOURCE_DIR}/src/Core/include")

include_directories("${PROJECT_SOURCE_DIR}/OPCUA_Models")

# The generated files are: "namespace_${NAMESPACE_NAME}_... .c/.h"
set(NAMESPACE_NAME_CRCL "crcl")
set(NAMESPACE_NAME_DI "di")
set(NAMESPACE_NAME_ROBOTICS "robotics")
set(NAMESPACE_NAME_FORTISS_DI "fortiss_di")
set(NAMESPACE_NAME_FORTISS_ROBOTICS "fortiss_robotics")
set(NAMESPACE_NAME_FORTISS_KUKA_IIWA "kuka_iiwa")

# The compiled namespace is: "${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME}"
set(NAMESPACE_PREFIX "pref")

ua_generate_nodeset_and_datatypes(
        INTERNAL
        NAME "${NAMESPACE_NAME_CRCL}"
        FILE_NS "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/CRCL/CRCL.NodeSet2.xml"
        TARGET_PREFIX "${NAMESPACE_PREFIX}"
        FILE_CSV "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/CRCL/CRCL.csv"
        FILE_BSD "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/CRCL/CRCL.Types.bsd"
        OUTPUT_DIR "${GENERATE_OUTPUT_DIR}"
    # This namespace index must match the order in which you are adding the nodeset in the source code
        NAMESPACE_MAP 2:https://crcl.org
)

ua_generate_nodeset_and_datatypes(
        INTERNAL
        NAME "${NAMESPACE_NAME_DI}"
        FILE_NS "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/DI/Opc.Ua.Di.NodeSet2.xml"
        TARGET_PREFIX "${NAMESPACE_PREFIX}"
        FILE_CSV "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/DI/OpcUaDiModel.csv"
        FILE_BSD "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/DI/Opc.Ua.Di.Types.bsd"
        OUTPUT_DIR "${GENERATE_OUTPUT_DIR}"
    # This namespace index must match the order in which you are adding the nodeset in the source code
        NAMESPACE_MAP 3:http://opcfoundation.org/UA/DI/
)

ua_generate_nodeset_and_datatypes(
        INTERNAL
        NAME "${NAMESPACE_NAME_ROBOTICS}"
        FILE_NS "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/Robotics/Opc.Ua.Robotics.NodeSet2.xml"
        TARGET_PREFIX "${NAMESPACE_PREFIX}"
        FILE_CSV "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/Robotics/OpcUaRoboticsModel.csv"
        FILE_BSD "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/Robotics/Opc.Ua.Robotics.Types.bsd"
        OUTPUT_DIR "${GENERATE_OUTPUT_DIR}"
    # This namespace index must match the order in which you are adding the nodeset in the source code
        NAMESPACE_MAP 4:http://opcfoundation.org/UA/Robotics/
        DEPENDS "${NAMESPACE_NAME_DI}"
)

ua_generate_nodeset_and_datatypes(
        INTERNAL
        NAME "${NAMESPACE_NAME_FORTISS_DI}"
        FILE_NS "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/fortiss_di/fortiss.Di.NodeSet2.xml"
        TARGET_PREFIX "${NAMESPACE_PREFIX}"
        FILE_CSV "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/fortiss_di/fortissDiModel.csv"
        FILE_BSD "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/fortiss_di/fortiss.Di.Types.bsd"
        OUTPUT_DIR "${GENERATE_OUTPUT_DIR}"
    # This namespace index must match the order in which you are adding the nodeset in the source code
        NAMESPACE_MAP 5:https://fortiss.org/UA/DI/
        DEPENDS "${NAMESPACE_NAME_ROBOTICS}"
)

ua_generate_nodeset_and_datatypes(
        INTERNAL
        NAME "${NAMESPACE_NAME_FORTISS_ROBOTICS}"
        FILE_NS "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/fortiss_robotics/fortiss.Robotics.NodeSet2.xml"
        TARGET_PREFIX "${NAMESPACE_PREFIX}"
        FILE_CSV "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/fortiss_robotics/fortissRoboticsModel.csv"
        FILE_BSD "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/fortiss_robotics/fortiss.Robotics.Types.bsd"
        OUTPUT_DIR "${GENERATE_OUTPUT_DIR}"
    # This namespace index must match the order in which you are adding the nodeset in the source code
        NAMESPACE_MAP 6:https://fortiss.org/UA/Robotics/
        DEPENDS "${NAMESPACE_NAME_FORTISS_DI}"
)

ua_generate_nodeset_and_datatypes(
        INTERNAL
        NAME "${NAMESPACE_NAME_FORTISS_KUKA_IIWA}"
        FILE_NS "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/kuka_iiwa/Kuka.iiwa.NodeSet2.xml"
        TARGET_PREFIX "${NAMESPACE_PREFIX}"
        FILE_CSV "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/kuka_iiwa/kukaIiwaModel.csv"
        FILE_BSD "${CMAKE_CURRENT_LIST_DIR}/OPCUA_Models/all_models/Published/kuka_iiwa/Kuka.iiwa.Types.bsd"
        OUTPUT_DIR "${GENERATE_OUTPUT_DIR}"
    # This namespace index must match the order in which you are adding the nodeset in the source code
        NAMESPACE_MAP 7:https://fortiss.org/UA/kuka_iiwa/
        DEPENDS "${NAMESPACE_NAME_FORTISS_ROBOTICS}"
)

add_library(SAMYCore_Library STATIC
                ${UA_NODESET_DI_SOURCES}
                ${UA_TYPES_DI_SOURCES}
                ${UA_NODESET_ROBOTICS_SOURCES}
                ${UA_TYPES_ROBOTICS_SOURCES}
                ${UA_NODESET_FORTISS_DI_SOURCES}
                ${UA_TYPES_FORTISS_DI_SOURCES}
                ${UA_NODESET_FORTISS_ROBOTICS_SOURCES}
                ${UA_TYPES_FORTISS_ROBOTICS_SOURCES}
                ${UA_NODESET_KUKA_IIWA_SOURCES}
                ${UA_TYPES_KUKA_IIWA_SOURCES}
                ${UA_NODESET_CRCL_SOURCES}
                ${UA_TYPES_CRCL_SOURCES}
                "./src/Helpers/helpers.cpp"
                "./src/SAMYSkill/samyskill.cpp"
                "./src/InformationSource/informationSource.cpp"
                "./src/Parsers/informationSourcesParser.cpp"
                "./src/Parsers/samycoreConfigParser.cpp"
                "./src/Parsers/robotsParser.cpp"
                "./src/Parsers/skillsParser.cpp"
                "./src/Parsers/dataBaseParser.cpp"
                "./src/OPCUA_Server/OpcUaServer.cpp"
                "./src/SAMYCoreInterfaceGenerator/skillsMethodsCallbacks.cpp"
                "./src/SAMYCoreInterfaceGenerator/skillsNodesAddition.cpp"
                "./src/SAMYCoreInterfaceGenerator/robotsNodesAddition.cpp"
                "./src/SAMYCoreInterfaceGenerator/samycoreInterfaceGenerator.cpp"
                "./src/SAMYCoreInterfaceGenerator/systemStatusNodes.cpp"
                "./src/SAMYRobot/Publisher.c"
                "./src/SAMYRobot/Subscriber.c"
                "./src/SAMYRobot/SAMYRobot.cpp"
                "./src/Core/samycore.cpp"
                )


add_executable(${PROJECT_NAME}
               "./src/main.cpp"
               )


add_executable(testsClient
               "./Tests/CRCLnamespace_tests/testsClient.cpp"
               )

add_executable(testsServer
               "./Tests/CRCLnamespace_tests/testsServer.cpp"
               )


# Make sure the nodeset compiler is executed before compiling the SAMYCore_Library
add_dependencies(SAMYCore_Library
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_DI}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_ROBOTICS}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_FORTISS_DI}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_FORTISS_ROBOTICS}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_FORTISS_KUKA_IIWA}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_CRCL}
                 )

# Make sure the nodeset compiler is executed before compiling the main file
add_dependencies(${PROJECT_NAME}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_DI}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_ROBOTICS}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_FORTISS_DI}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_FORTISS_ROBOTICS}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_FORTISS_KUKA_IIWA}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_CRCL}
                 )

# Make sure the nodeset compiler is executed before compiling the testsClient
add_dependencies(testsClient
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_DI}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_ROBOTICS}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_FORTISS_DI}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_FORTISS_ROBOTICS}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_FORTISS_KUKA_IIWA}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_CRCL}
                 )

# Make sure the nodeset compiler is executed before compiling the testsServer
add_dependencies(testsServer
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_DI}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_ROBOTICS}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_FORTISS_DI}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_FORTISS_ROBOTICS}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_FORTISS_KUKA_IIWA}
                 ${NAMESPACE_PREFIX}-ns-${NAMESPACE_NAME_CRCL}
                 )

target_link_libraries(SAMYCore_Library PRIVATE open62541::open62541 yaml-cpp spdlog::spdlog spdlog::spdlog)
target_link_libraries(testsClient PRIVATE Catch2::Catch2 Catch2::Catch2WithMain SAMYCore_Library)
target_link_libraries(testsServer PRIVATE Catch2::Catch2 Catch2::Catch2WithMain SAMYCore_Library spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} SAMYCore_Library spdlog::spdlog)
