add_subdirectory(formats)
add_subdirectory(effects)

target_sources(${CMAKE_PROJECT_NAME} PUBLIC
        main.cpp)

add_library(ImageLib STATIC Image.cpp)
target_include_directories(ImageLib
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )

target_include_directories(${CMAKE_PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_DL_LIBS})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ImageLib)

find_package(Boost 1.55 REQUIRED program_options)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${Boost_PROGRAM_OPTIONS_LIBRARY})
