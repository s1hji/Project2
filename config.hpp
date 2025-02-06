#ifndef VERIABLS_HPP
#define VERIABLS_HPP

#include <string>

using namespace std;

namespace config {

    const int WINDOW_PATH = 800;
    const int WINDOW_HEIGHT = 600;
    const int PLATFORM_COUNT = 10;

    const float GRAVITY = 0.35f;
    const float JUMP_SPEED = -10.0f;
    const float PLATFORM_SPEED = 3.0f;
    const float PERS_HORIZONTAL_SPEED = 8.0;

    const string FONT_PATH = "fonts/arial.ttf";
    const string BACKGROUND_IMAGE = "images/background.png";
    const string DOODLE_IMAGE = "images/doodle.png";
    const string PLATFORM_IMAGE = "images/platform.png";
    const string JUMP_SOUND = "sounds/doodle.wav";
    const string MAX_SCORE_FILE = "max_score.txt";
    const string ENEMY_IMAGE = "images/enemy.png";
    const string GAME_OVER_SOUND = "sounds/game_over.wav";
    const string BONUS_IMAGE = "images/bonus.png";
    const string BONUS_SOUND = "sounds/bonus.wav";

    const int BONUS_POINTS = 100;
}

#endif