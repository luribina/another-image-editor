add_library(BMPFormat SHARED BMPFormat.cpp)
target_include_directories(BMPFormat PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(BMPFormat PUBLIC ImageLib)