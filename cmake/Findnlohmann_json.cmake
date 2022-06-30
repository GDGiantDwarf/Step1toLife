# Usage:
# FIND_PACKAGE(json REQUIRED)
# [...]
# TARGET_LINK_LIBRARIES(target_name json)

CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

if (NOT nlohmann_json_FOUND)
    INCLUDE(FetchContent)
    FetchContent_Declare(nlohmann_json URL https://github.com/nlohmann/json/archive/refs/tags/v3.10.5.tar.gz)
    FetchContent_GetProperties(nlohmann_json)

    if (NOT nlohmann_json_POPULATED)
        SET(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(nlohmann_json)
        SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        ADD_SUBDIRECTORY(${nlohmann_json_SOURCE_DIR} ${nlohmann_json_BINARY_DIR})
        SET(nlohmann_json_FOUND TRUE)
    endif()

endif()