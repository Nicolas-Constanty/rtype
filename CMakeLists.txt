cmake_minimum_required(VERSION 3.6)
project(rtype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("include")

file(GLOB Networksrc src/Network/*/*.cpp)
file(GLOB Networkinc include/Network/*/*.hpp)

file(GLOB Commoninc include/Common/*.hpp)

file(GLOB Protocolsrc src/Protocol/*.cpp)
file(GLOB Protocolinc include/Protocol/*.hpp)

file(GLOB SaltyEnginesrc src/SaltyEngine/*.cpp)
file(GLOB SaltyEngineinc include/SaltyEngine/*.hpp)

file(GLOB allsrc src/*/*.cpp src/*/*/*.cpp)
file(GLOB allinc src/*/*.hpp src/*/*/*.hpp)

add_executable(rtype
        ${Networksrc} ${Networkinc}
        ${Commoninc}
        ${Protocolsrc} ${Protocolinc}
        ${SaltyEnginesrc} ${SaltyEngineinc})

add_executable(udpserv-1 ${Networksrc} ${Networkinc} Tests/Network/udpserv-1.cpp)
add_executable(tcpserv-1 ${Networksrc} ${Networkinc} Tests/Network/tcpserv-1.cpp)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(udpserv-1 -lWs2_32)
    target_link_libraries(tcpserv-1 -lWs2_32)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")