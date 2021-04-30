cmake_minimum_required(VERSION 3.17)
project(LearningMan)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 14)
find_package(SFML 2.5 COMPONENTS system window graphics audio)

add_executable(LearningMan main.cpp define.hpp characters/Character.cpp characters/Character.hpp controllers/PlayerController.cpp controllers/PlayerController.hpp controllers/Controller.cpp controllers/Controller.hpp characters/Heros.cpp characters/Heros.hpp controllers/IAController.cpp controllers/IAController.hpp characters/Shotgunner.cpp characters/Shotgunner.hpp utils/TextureManager.cpp utils/TextureManager.hpp utils/SoundPlayer.cpp utils/SoundPlayer.hpp Map/Map.cpp Map/Map.h utils/BulletManager.cpp utils/BulletManager.hpp)
target_link_libraries(LearningMan sfml-system sfml-window sfml-graphics sfml-audio -static)