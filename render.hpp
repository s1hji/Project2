/*функции для отрисовки*/

#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "config.hpp"
using namespace sf;
using namespace std;

void renderMenu(RenderWindow& app, const Sprite& background, const Font& font);
void renderGameOver(RenderWindow& app, const Sprite& background, const Font& font, int score, int maxScore);
void renderGame(RenderWindow& app, const Sprite& background, const Sprite& doodle, const Sprite platform[], const Sprite enemies[], const bool hasEnemy[], const Sprite bonuses[], const bool hasBonus[], const Font& font, int score);
void renderSettings(RenderWindow& app, const Sprite& background, const Font& font, float& volume);
#endif // GAME_HPP