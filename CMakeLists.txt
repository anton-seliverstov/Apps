project(apps)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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
                   COMMAND gzip -v ${CMAKE_BINARY_DIR}/man/man5/apps-rc.5
                   COMMAND gzip -v ${CMAKE_BINARY_DIR}/man/ru/man1/apps.1
                   COMMAND gzip -v ${CMAKE_BINARY_DIR}/man/ru/man5/apps-rc.5
                   COMMENT "\nBuilding man pages..."
                   VERBATIM
                  )

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION /usr/bin
        )

install(DIRECTORY ${CMAKE_BINARY_DIR}/man/ DESTINATION /usr/share/man/
        CONFIGURATIONS Release
        PATTERN "*"
        )