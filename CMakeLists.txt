cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

project(DoveDispatch
    VERSION 0.0.1
    DESCRIPTION "Event Library"
    LANGUAGES CXX
)

find_program(LCOV lcov)
find_program(GENHTML genhtml)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    find_program(GCOV gcov)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    find_program(GCOV llvm-cov)
endif()

#find_program(SCCACHE sccache)
#if(SCCACHE)
#    message("sccache found")
#    set(CMAKE_C_COMPILER_LAUNCHER ${SCCACHE})
#    set(CMAKE_CXX_COMPILER_LAUNCHER ${SCCACHE})
#    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT Embedded)
#else()
#    message("sccache not found. No caching.")
#endif()

find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(documentation
        COMMAND "doxygen"
        WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
        COMMENT "Generating Doxygen Documentation"
        VERBARIM
    )
else()
    message("Doxygen required to build Doxygen Documentation")
endif()

add_library(${PROJECT_NAME}
    source/Event.cpp
    source/EventEmitter.cpp
)
target_include_directories(${PROJECT_NAME}
    PUBLIC include
)
if(GCOV AND LCOV AND GENHTML)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    endif()
else()
    if(NOT GCOV)
        message("gcov not found. No coverage report will be generated.")
    endif()
    if(NOT LCOV)
        message("lcov not found. No coverage report will be generated.")
    endif()
    if(NOT GENHTML)
        message("genhtml not found. No coverage report will be generated.")
    endif()
endif()

set(TTEVENT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# tests:
enable_testing()
add_subdirectory(tests)
