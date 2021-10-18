add_library(SepiaEffect SHARED SepiaEffect.cpp)
target_include_directories(SepiaEffect PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(SepiaEffect PUBLIC ImageLib)

add_library(NegativeEffect SHARED NegativeEffect.cpp)
target_include_directories(NegativeEffect PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(NegativeEffect PUBLIC ImageLib)