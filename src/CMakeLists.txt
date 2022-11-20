set (SOURCE_FILES
    spaceport/Main.cpp

    spaceport/core/Spaceport.cpp

    spaceport/data/Config.cpp

    spaceport/modules/Module.cpp
    spaceport/modules/DataStorageModule.cpp

    spaceport/frontend/Dashboard.cpp

)

add_executable(spaceport ${SOURCE_FILES})
target_include_directories(spaceport PUBLIC ./)
target_include_directories(spaceport PUBLIC ${CONAN_INCLUDE_DIRS})

target_link_libraries(spaceport ${CONAN_LIBS})

add_custom_target(webcontent
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/www
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/www ${CMAKE_BINARY_DIR}/www
    COMMENT "Copying web to output dir"
)
add_custom_target(webcontentdebug
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/www ${CMAKE_BINARY_DIR}/www-debug
    COMMENT "Symlink debug symlink repo"
)
add_dependencies(spaceport webcontent webcontentdebug)

# vim:ft=cmake
