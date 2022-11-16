set (SOURCE_FILES
    spaceport/Main.cpp

    spaceport/core/Spaceport.cpp

    spaceport/data/Config.cpp

    spaceport/modules/Module.cpp
    spaceport/modules/DataStorageModule.cpp

)

add_executable(spaceport ${SOURCE_FILES})
target_include_directories(spaceport PUBLIC ./)
target_include_directories(spaceport PUBLIC ${CONAN_INCLUDE_DIRS})

target_link_libraries(spaceport ${CONAN_LIBS})

# vim:ft=cmake
