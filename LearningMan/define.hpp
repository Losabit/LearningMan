#include <SFML/Graphics.hpp>

// Paths
#define ASSETS_PATH "../assets"
#define MAP_PATH "../ressources"
#define CHARACTER_ASSETS_PATH ASSETS_PATH "/characters"
#define GUI_ASSETS_PATH ASSETS_PATH "/GUI"

// Character Settings
#define HEROS_INITIAL_POSITION sf::Vector2f(0, 583)
#define TIME_SHOOT_TO_IDLE 0.5f
#define TIME_BETWEEN_ANIMATIONS 0.4f

// Window
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 680
#define CAMERA_WIDTH 400.f
#define CAMERA_HEIGHT 250.f
#define DEFAULT_COLOR sf::Color(122, 160, 122, 0)
#define BOSS_LIFEBAR_POSITION_X -120

//Other
#define POINTS_BY_KILL 200
#define POINTS_BY_SECOND 30
#define MAX_LEVEL_TIME 120
#define SEND_HTTP_REQUEST true
#define ACTIVE_DEBUG_KEYS true

// IA
#define IA_MODE_USER_INPUTS false
#define ENNEMIES_CAN_PLAY true
#define ONLY_TRAIN_ON_BOSS false
#define AUTO_RESTART true
#define SEE_IA_LOGS true

