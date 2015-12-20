# Copyright 2015 Anton Seliverstov (seliverstov.ad@ya.ru)
#
# This file is part of Apps.
#
# Apps is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Apps is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Apps.  If not, see <http://www.gnu.org/licenses/>.
#
project(apps)
cmake_minimum_required(VERSION 2.8)

# Configuring build type. Use "-DCMAKE_BUILD_TYPE=Release"
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the type of build, options are: Debug Release."
        FORCE)
endif(NOT CMAKE_BUILD_TYPE)
if(CMAKE_BUILD_TYPE MATCHES "Release")
    ADD_DEFINITIONS(-DQT_NO_DEBUG_OUTPUT)
endif(CMAKE_BUILD_TYPE MATCHES "Release")
message("Build type for project '${PROJECT_NAME}' set to '${CMAKE_BUILD_TYPE}'")

find_package ( Threads REQUIRED )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread")

FILE(GLOB ProjectSources "./src/*.cpp")
FILE(GLOB ProjectHeaders "./src/*.h")
FILE(GLOB ProjectSourcesSglXml "./src/SglXml/*.cpp")
FILE(GLOB ProjectHeadersSglXml "./src/SglXml/*.h")
FILE(GLOB ProjectHeadersSglStringUtils "./src/SglStringUtils/*.h")

ADD_EXECUTABLE(${PROJECT_NAME}
               ${ProjectSources}
               ${ProjectHeaders}
               ${ProjectSourcesSglXml}
               ${ProjectHeadersSglXml}
               ${ProjectHeadersSglStringUtils}
              )

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}
                   POST_BUILD
                   COMMAND rm -rfv ${CMAKE_BINARY_DIR}/man
                   COMMAND cp -vr ${PROJECT_SOURCE_DIR}/man ${CMAKE_BINARY_DIR}/man
                   COMMAND gzip -v ${CMAKE_BINARY_DIR}/man/man1/apps.1
                   COMMAND gzip -v ${CMAKE_BINARY_DIR}/man/man1/generate_apps-rc.1
                   COMMAND gzip -v ${CMAKE_BINARY_DIR}/man/man5/apps-rc.5
                   COMMAND gzip -v ${CMAKE_BINARY_DIR}/man/ru/man1/apps.1
                   COMMAND gzip -v ${CMAKE_BINARY_DIR}/man/ru/man1/generate_apps-rc.1
                   COMMAND gzip -v ${CMAKE_BINARY_DIR}/man/ru/man5/apps-rc.5
                   COMMENT "\nBuilding man pages..."
                   VERBATIM
                  )

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION /usr/bin
        CONFIGURATIONS Release
        )

install(PROGRAMS ${PROJECT_SOURCE_DIR}/script/generate_apps-rc.sh
        DESTINATION /usr/bin
        RENAME generate_apps-rc
        CONFIGURATIONS Release
        )

install(DIRECTORY ${CMAKE_BINARY_DIR}/man/ DESTINATION /usr/share/man/
        CONFIGURATIONS Release
        CONFIGURATIONS Release
        PATTERN "*"
        )