cmake_minimum_required(VERSION 3.17)
project(LearningMan)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 14)
find_package(SFML 2.5 COMPONENTS system window graphics audio)
<<<<<<< HEAD
set(libcurl_INCLUDE_DIR "D:/lib/curl-7.77.0_2-win32-mingw/curl-7.77.0-win32-mingw/include")

=======

set(libcurl_INCLUDE_DIR "C:/lib/curl-7.77.0_2-win32-mingw/curl-7.77.0-win32-mingw/include")
#set(libcurl_INCLUDE_DIR "D:/lib/curl-7.77.0_2-win32-mingw/curl-7.77.0-win32-mingw/include")
>>>>>>> faea1a7eef9b436363c1fcecccc4b95cf2e70e5e
include_directories(${libcurl_INCLUDE_DIR})

add_executable(LearningMan main.cpp define.hpp characters/Character.cpp characters/Character.hpp controllers/PlayerController.cpp controllers/PlayerController.hpp controllers/Controller.cpp controllers/Controller.hpp characters/Heros.cpp characters/Heros.hpp controllers/IAController.cpp controllers/IAController.hpp characters/Shotgunner.cpp characters/Shotgunner.hpp utils/TextureManager.cpp utils/TextureManager.hpp utils/SoundPlayer.cpp utils/SoundPlayer.hpp Map/Map.cpp Map/Map.h utils/BulletManager.cpp utils/BulletManager.hpp GUI/Button.cpp GUI/Button.hpp GUI/Container.cpp GUI/Container.hpp Map/Collide.cpp Map/Collide.h utils/HitboxManager.cpp utils/HitboxManager.hpp utils/CollisionManager.cpp utils/CollisionManager.hpp lib/jsoncpp.cpp lib/json/json.h lib/json/json-forwards.h Map/MapModel.cpp Map/MapModel.hpp characters/Golem.cpp characters/Golem.hpp utils/Portal.cpp utils/Portal.hpp GUI/EndLevelView.cpp GUI/EndLevelView.h characters/Healer.cpp characters/Healer.h characters/BossCharacter.cpp characters/BossCharacter.h controllers/BossController.cpp controllers/BossController.h learningAlgorithms/trainEnvironnement.cpp controllers/PredefineController.cpp controllers/PredefineController.hpp utils/RecordInputs.cpp utils/RecordInputs.h learningAlgorithms/QLearning.cpp learningAlgorithms/QLearning.hpp learningAlgorithms/Environment.cpp learningAlgorithms/Environment.h GUI/UserConfiguration.cpp GUI/UserConfiguration.hpp utils/curlFunction.cpp utils/curlFunction.h)
target_link_libraries(LearningMan sfml-system sfml-window sfml-graphics sfml-audio -static )
target_link_libraries(LearningMan C:/Users/quent/Desktop/PA/LearningMan/LearningMan/cmake-build-debug/libcurl.dll.a)
#target_link_libraries(LearningMan C:/Users/marvi/CLionProjects/LearningMan/LearningMan/cmake-build-debug/libcurl.dll.a)


