add_library(${PROJECT_NAME} SHARED)
add_subdirectory(PacPac)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE EnTT)
