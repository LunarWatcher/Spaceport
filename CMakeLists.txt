cmake_minimum_required(VERSION 3.10)
project(Spaceport)

set (CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure (REQUIRES
    # Server framework
    crowcpp-crow/1.0+3
    # JSON fuckery; crow offers some JSON facilities, but not really enough.
    # May be replaced with a faster library in the future:tm:
    nlohmann_json/3.11.2
    # Logging
    spdlog/1.10.0
    # Mainly used for tests, but also active runners
    cpr/1.9.0 
    # Database access
    libpqxx/7.7.4
    # Dependency conflict override
    zlib/1.2.13
    OPTIONS 
    boost:without_atomic=True
    boost:without_chrono=True
    boost:without_container=True
    boost:without_context=True
    boost:without_contract=True
    boost:without_coroutine=True
    boost:without_exception=True
    boost:without_fiber=True
    boost:without_filesystem=True
    boost:without_graph=True
    boost:without_graph_parallel=True
    boost:without_iostreams=True
    boost:without_json=True
    boost:without_locale=True
    boost:without_log=True
    boost:without_math=True
    boost:without_mpi=True
    boost:without_nowide=True
    boost:without_program_options=True
    boost:without_python=True
    boost:without_random=True
    boost:without_regex=True
    boost:without_serialization=True
    boost:without_stacktrace=True
    boost:without_test=True
    boost:without_thread=True
    boost:without_timer=True
    boost:without_type_erasure=True
    boost:without_wave=True

    GENERATORS cmake
)

conan_cmake_autodetect (settings)
conan_cmake_install (PATH_OR_REFERENCE . BUILD missing SETTINGS ${settings})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSPACEPORT_DEBUG")
endif()

# Set up versioning {{{
find_program(GIT git)
if (GIT)
    execute_process(COMMAND ${GIT} describe --tags --always
        OUTPUT_VARIABLE SPACEPORT_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    message(STATUS "Detected version: ${SPACEPORT_VERSION}")
else()
    message(WARNING "Git not found. Defaulting to unknown version. This will not have an effect on the program beyond a missing version")
    set(SPACEPORT_VERSION "VERSION UNKNOWN. Who doesn't have Git? It's the 2020s. Install it already")
endif()
add_definitions(-DSPACEPORT_VERSION="${SPACEPORT_VERSION}")
# }}}

add_subdirectory(src)
add_subdirectory(tests)
# vim:ft=cmake
