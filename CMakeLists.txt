project(tres)
add_executable(${PROJECT_NAME} src/tres.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC PocoNet PocoFoundation)
