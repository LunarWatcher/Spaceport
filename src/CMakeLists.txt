set (SOURCE_FILES
    spaceport/core/Spaceport.cpp

    spaceport/data/Config.cpp

    spaceport/modules/Module.cpp
    spaceport/modules/DataStorageModule.cpp

    spaceport/frontend/Dashboard.cpp
    spaceport/frontend/Easter.cpp

    spaceport/core/server/Middlewares.cpp

)

add_library(spaceportsrc ${SOURCE_FILES})
add_executable(spaceport spaceport/Main.cpp)

target_include_directories(spaceportsrc PUBLIC ./)
target_include_directories(spaceportsrc PUBLIC ${CONAN_INCLUDE_DIRS})

target_link_libraries(spaceportsrc ${CONAN_LIBS})
target_link_libraries(spaceport spaceportsrc)

add_custom_target(webcontent
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/www
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/www ${CMAKE_BINARY_DIR}/www
    COMMENT "Copying web to output dir"
)
add_custom_target(webcontentdebug
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/www ${CMAKE_BINARY_DIR}/www-debug
    COMMENT "Symlink debug symlink repo"
)
add_dependencies(spaceportsrc webcontent webcontentdebug)

# vim:ft=cmake
