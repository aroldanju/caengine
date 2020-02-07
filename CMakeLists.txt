project(caengine C)

add_definitions(-D__CAENGINE_DEBUG__)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/vendor/sdl2)
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_package(LibXml2 REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${LIBXML2_INCLUDE_DIR})

file(GLOB SOURCES_ENGINE src/*.h src/*.c)

add_library(${PROJECT_NAME} ${SOURCES_ENGINE})
add_library(dependencies::caengine ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(caengine ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARY} ${SDL2_TTF_LIBRARY} -lm)