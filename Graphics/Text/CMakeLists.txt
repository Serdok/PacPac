add_executable(Text)
target_sources(Text PRIVATE main.cpp)

target_link_libraries(Text PRIVATE ${PROJECT_NAME})