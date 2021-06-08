cmake_minimum_required(VERSION 3.17)
project(LearningMan)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 14)
find_package(SFML 2.5 COMPONENTS system window graphics audio)


add_executable(LearningMan main.cpp define.hpp characters/Character.cpp characters/Character.hpp controllers/PlayerController.cpp controllers/PlayerController.hpp controllers/Controller.cpp controllers/Controller.hpp characters/Heros.cpp characters/Heros.hpp controllers/IAController.cpp controllers/IAController.hpp characters/Shotgunner.cpp characters/Shotgunner.hpp utils/TextureManager.cpp utils/TextureManager.hpp utils/SoundPlayer.cpp utils/SoundPlayer.hpp Map/Map.cpp Map/Map.h utils/BulletManager.cpp utils/BulletManager.hpp GUI/Button.cpp GUI/Button.hpp GUI/Container.cpp GUI/Container.hpp Map/Collide.cpp Map/Collide.h Map/MapEnvironnement.cpp Map/MapEnvironnement.h utils/HitboxManager.cpp utils/HitboxManager.hpp utils/CollisionManager.cpp utils/CollisionManager.hpp lib/jsoncpp.cpp lib/json/json.h lib/json/json-forwards.h Map/MapModel.cpp Map/MapModel.hpp characters/Golem.cpp characters/Golem.hpp utils/Portal.cpp utils/Portal.hpp GUI/EndLevelView.cpp GUI/EndLevelView.h characters/Healer.cpp characters/Healer.h)
target_link_libraries(LearningMan sfml-system sfml-window sfml-graphics sfml-audio -static)

