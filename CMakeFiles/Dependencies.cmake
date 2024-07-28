include(FetchContent)
include(CheckIncludeFileCXX)

set(${PROJECT_NAME}_LIBRARIES "" CACHE INTERNAL "")

function(addExternalDependency)
    set(options "")
    set(oneValueArgs NAME TAG URL)
    set(multiValueArgs MODULES)

    cmake_parse_arguments(PREFIX "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    FetchContent_Declare(
        ${PREFIX_NAME}
        GIT_REPOSITORY ${PREFIX_URL}
        GIT_TAG ${PREFIX_TAG}
    )
    FetchContent_MakeAvailable(${PREFIX_NAME})

    if(NOT "${PREFIX_MODULES}" STREQUAL "")
        foreach(module IN LISTS PREFIX_MODULES)
            list(APPEND ${PROJECT_NAME}_LIBRARIES ${module})
        endforeach()
    else()
        list(APPEND ${PROJECT_NAME}_LIBRARIES ${PREFIX_NAME})
    endif()

    # To make changes visible outside this function
    set(${PROJECT_NAME}_LIBRARIES "${${PROJECT_NAME}_LIBRARIES}" CACHE INTERNAL "")
endfunction()
