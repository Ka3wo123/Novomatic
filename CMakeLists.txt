cmake_minimum_required(VERSION 3.8)

project(Novomatic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB LIB_SOURCES_COMPRESS "Compress/*.cpp")
file(GLOB LIB_HEADERS_COMPRESS "Compress/*.hpp")

file(GLOB LIB_SOURCES_TICKETOMAT "Ticketomat/*.cpp")
file(GLOB LIB_HEADERS_TICKETOMAT "Ticetomat/*.hpp")

file(GLOB LIB_SOURCES_COLLISION "Collision/*.cpp")
file(GLOB LIB_HEADERS_COLLISION "Collision/*.hpp")

# Add custom library containing my C++ files
add_library(NOVOMATICLIB
            ${LIB_SOURCES_COMPRESS} ${LIB_HEADERS_COMPRESS}
            ${LIB_SOURCES_TICKETOMAT} ${LIB_HEADERS_TICKETOMAT}
            ${LIB_SOURCES_COLLISION} ${LIB_HEADERS_COLLISION}
            )

file(GLOB APP_SOURCES "*.cpp")

# Add executable for each task, link libraries and include directories
foreach(testsourcefile ${APP_SOURCES})
    get_filename_component(testname ${testsourcefile} NAME_WE)
    add_executable(${testname} ${testsourcefile})
    target_link_libraries(${testname} NOVOMATICLIB)
    target_include_directories(${testname} PUBLIC NOVOMATICLIB)    
endforeach(testsourcefile ${APP_SOURCES})


# Include SFML directories and link libraries
target_link_libraries(NOVOMATICLIB ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-graphics.lib)
target_link_libraries(NOVOMATICLIB ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-audio.lib)
target_link_libraries(NOVOMATICLIB ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-network.lib)
target_link_libraries(NOVOMATICLIB ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-system.lib)
target_link_libraries(NOVOMATICLIB ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-window.lib)

include_directories(${CMAKE_SOURCE_DIR}/SFML/include)



# Copy .dll files into build/x64-Debug
file(GLOB SFML_BIN_FILES ${CMAKE_SOURCE_DIR}/SFML/bin/*)

foreach(sfml_bin_file ${SFML_BIN_FILES})
    get_filename_component(filename ${sfml_bin_file} NAME)
    configure_file(${CMAKE_SOURCE_DIR}/SFML/bin/${filename} ${CMAKE_SOURCE_DIR}/out/build/x64-Debug/ COPYONLY)
endforeach(sfml_bin_file ${SFML_BIN_FILES})