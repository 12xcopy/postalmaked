cmake_minimum_required(VERSION 3.15)
project(postalmaked VERSION 1.0 LANGUAGES C CXX)

# todo: all the other stuff thats in the postal 1 makefile should be here
# terms im using: pmaked: this. postal97: original postal release (includes super postal, postal 2015, etc)

option(DEBUG "debug build" OFF)

set(BINDIR "${CMAKE_CURRENT_BINARY_DIR}/postal/bin")
set(EXDIR "${CMAKE_CURRENT_BINARY_DIR}/postal/extra")
set(SRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/postal")

#..ensure they exist
file(MAKE_DIRECTORY ${BINDIR})
file(MAKE_DIRECTORY ${EXDIR})



# im just gonna assume that Postal (1997) doesnt need c++11 > stuff
set(CMAKE_CXX_STANDARD 98)
# my fave
set(CMAKE_C_STANDARD 99)

# sets POSTAL97SRC and POSTAL97INC
include(./postal97src.cmake)
include(./postalsaucesrc.cmake)
set(SRC ${POSTAL97SRC} ${POSTALSAUCESRC})
include_directories(${POSTAL97INC} ${POSTALSAUCEINC})

# this def blocks all weird postal97 shenanigans 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPMAKED_JUST_COMPILE")


# note: postal97 uses -w to hide all warnings, im only hiding warnings that arent that bad

# force all warnings to specify the flag to hide them
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-show-option")
# make sure 'char' is signed
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsigned-char")
# TRACE() does a deprecated const char* to char* conversion, so quiet the compiler about it
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")
# assume NULL can be safely converted to integer types
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-conversion-null")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-ignored-typedef")
# ?? probably needs to be removed
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPLATFORM_UNIX")

# dangerous??
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

# target is Postal (2015)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTARGET=POSTAL_2015")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLOCALE=US")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAPP_NAME=\"postalmaked\"")




if(DEBUG)
    add_compile_definitions(DEBUG _DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
else()
    add_compile_definitions(NDEBUG _NDEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

set(CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS})

message(STATUS "sources: " ${SRC})
add_executable(postalmaked ${SRC})


find_package(SDL2)
if(SDL2_FOUND)
    target_include_directories(postalmaked PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(postalmaked PRIVATE ${SDL2_LIBRARIES})
endif()


find_package(OpenGL REQUIRED)
target_link_libraries(postalmaked PRIVATE OpenGL::GL)