project(apps)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FILE(GLOB ProjectSources "./src/*.cpp")
FILE(GLOB ProjectHeaders "./src/*.h")

ADD_EXECUTABLE(${PROJECT_NAME}
               ${ProjectSources}
               ${ProjectHeaders}
              )

