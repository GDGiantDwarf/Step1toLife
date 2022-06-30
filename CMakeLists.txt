# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
FIND_PACKAGE(raylib REQUIRED)
FIND_PACKAGE(nlohmann_json REQUIRED)

# Notre projet est étiqueté Step1toLife
project(Step1toLife)

# Crée des variables avec les fichiers à compiler
set(MAIN main.cpp)
file(GLOB helloworld_SRC "source/*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/header)

# On indique que l'on veut un exécutable "Step1toLife" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(Step1toLife ${MAIN} ${helloworld_SRC})

TARGET_LINK_LIBRARIES(Step1toLife raylib nlohmann_json::nlohmann_json)