# Define Nasal core files
set(HEADERS 
    naref.h
    nasal.h
    iolib.h
)

set(SOURCES 
    bitslib.c
    code.c
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

add_executable(nasal-bin nasal-bin.c)
target_link_libraries(nasal-bin nasal m )
