set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define Nasal core files
set(HEADERS 
    naref.h
    nasal.h
    iolib.h
)

set(SOURCES 
    bitslib.c
    code.c
    debug.c
    codegen.c
    gc.c
    hash.c
    iolib.c
    lex.c
    lib.c
    mathlib.c
    misc.c
    parse.c
    string.c
    thread-posix.c
    thread-win32.c
    threadlib.c
    utf8lib.c
    vector.c
    code.h
    data.h
    parse.h
    util.h
)

if (NOT WIN32)
  set(SOURCES ${SOURCES}
      unixlib.c
  )
endif()

# Create a nasal core library
add_library(nasal ${SOURCES} ${HEADERS})

# Define the SOURCE_DIR macro and the nasal-bin executable
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

# Option for verbose debugging output
option(NASAL_DEBUG "Enable verbose debugging output" OFF)

if(NASAL_DEBUG)
    add_definitions(-DNASAL_DEBUG)
endif()

option(ENABLE_PROFILING "Enable performance profiling" OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ENABLE_PROFILING)
    message(STATUS "Profiling enabled for debug build")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -g")
endif()


add_executable(nasal-bin nasal-bin.c)
target_link_libraries(nasal-bin nasal m )
