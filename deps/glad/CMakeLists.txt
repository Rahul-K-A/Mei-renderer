include_directories(include)
add_library(GLAD src/glad.c)

TARGET_LINK_LIBRARIES(GLAD ${CMAKE_DL_LIBS})