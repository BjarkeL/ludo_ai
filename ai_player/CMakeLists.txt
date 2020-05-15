cmake_minimum_required(VERSION 3.10.2)

project(ai_ludo_player)


set(ludo_includes 
    ${CMAKE_CURRENT_SOURCE_DIR}/../ludo_game_code/Domain-Code/game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../ludo_game_code/Domain-Code/test_game.cpp
)

add_executable(ai_ludo_player main.cpp ai_player.cpp ${ludo_includes})

target_include_directories(ai_ludo_player PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../ludo_game_code/Domain-Code)
