cmake_minimum_required(VERSION 3.20)

project(DataLoggerGateway VERSION 1.0.0)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CppKafka REQUIRED)

file(GLOB SOURCES "*.cpp" "*.h")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/logging/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/networking/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/DL_Protocol/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  Logging
  Networking
  DataloggerProtocol
  CppKafka::cppkafka
)

install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
