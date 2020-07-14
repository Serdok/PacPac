set(BUILD_TESTING FALSE)
set(BUILD_DOCS TRUE)
add_subdirectory(entt)

add_subdirectory(glm)

set(JSON_BuildTests OFF)
set(JSON_Install OFF)
add_subdirectory(json)