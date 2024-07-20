cmake_minimum_required(VERSION 3.16)
project(fetch_compile_commands)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POSITION_INDEPENDENT_CODE ${BUILD_PIC})
set(BUILD_TESTING OFF)
FetchContent_Declare(nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.13.0)
FetchContent_Declare(spdlog
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/thirdparty/spdlog
)
FetchContent_MakeAvailable(spdlog)

add_executable(fetch_compile_commands fetch_compile_commands.cc)
target_link_libraries(fetch_compile_commands
        PRIVATE nlohmann_json::nlohmann_json
        PRIVATE spdlog::spdlog)
