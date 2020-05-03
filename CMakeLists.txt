cmake_minimum_required(VERSION 3.7)
project(jeu)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets CONFIG REQUIRED)

add_executable(jeu src/main.cpp src/scenes/Scene.cpp src/Window.cpp src/objects/Player.cpp src/scenes/GameScene.cpp src/objects/Obstacle.cpp src/objects/Floor.cpp src/scenes/levels/FirstLevel.cpp src/scenes/SettingsScene.cpp src/scenes/StartScene.cpp src/widgets/PauseWidget.cpp src/widgets/EndWidget.cpp src/scenes/ScoresScene.cpp src/widgets/ChoiceWidget.cpp src/objects/MovingFloor.cpp src/objects/MovingObstacle.cpp src/scenes/levels/SecondLevel.cpp src/utils.cpp src/scenes/levels/ThirdLevel.cpp)
target_link_libraries(jeu Qt5::Widgets)