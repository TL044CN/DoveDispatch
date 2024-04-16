# Fetch Catch2
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.x
)

FetchContent_GetProperties(Catch2)
if(NOT catch2_POPULATED)
  FetchContent_Populate(Catch2)
  add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
endif()

# Add your tests
add_executable(tests
    test_main.cpp
    test_Event.cpp
    test_EventEmitter.cpp
)

target_link_libraries(tests
    PRIVATE
        Catch2::Catch2
        ${PROJECT_NAME}
)

target_include_directories(tests
    PRIVATE
        ${catch2_SOURCE_DIR}/single_include
        ${TTEVENT_INCLUDE_DIR}
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)
catch_discover_tests(tests)