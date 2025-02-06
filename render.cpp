#include "render.hpp"
#include "config.hpp"
#include <SFML/Graphics.hpp>
using namespace config;

void renderMenu(RenderWindow& app, const Sprite& background, const Font& font) {
    app.clear();
    app.draw(background);

    Text menuText("Menu", font, 100);
    menuText.setFillColor(Color::Black);
    menuText.setPosition(325, 150);
    app.draw(menuText);

    Vector2i mousePos = Mouse::getPosition(app);


    bool isStartHovering = (mousePos.x >= 350 && mousePos.x <= 440 && mousePos.y >= 300 && mousePos.y <= 350);
    Text startText("Start", font, 50);
    startText.setFillColor(isStartHovering ? Color::Yellow : Color::Green);
    startText.setOutlineThickness(3);
    startText.setOutlineColor(Color::Black);
    startText.setPosition(350, 300);
    app.draw(startText);


    bool isExitHovering = (mousePos.x >= 367 && mousePos.x <= 425 && mousePos.y >= 450 && mousePos.y <= 500);
    Text exitText("Exit", font, 50);
    exitText.setFillColor(isExitHovering ? Color::Yellow : Color::Green);
    exitText.setOutlineThickness(3);
    exitText.setOutlineColor(Color::Black);
    exitText.setPosition(367, 450);
    app.draw(exitText);

    bool isSettingsHovering = (mousePos.x >= 330 && mousePos.x <= 470 && mousePos.y >= 380 && mousePos.y <= 425);
    Text settingsText("settings", font, 50);
    settingsText.setFillColor(isSettingsHovering ? Color::Yellow : Color::Green);
    settingsText.setOutlineThickness(3);
    settingsText.setOutlineColor(Color::Black);
    settingsText.setPosition(330, 370);
    app.draw(settingsText);



    app.display();
}


void renderGameOver(RenderWindow& app, const Sprite& background, const Font& font, int score, int maxScore) {
    app.clear();
    app.draw(background);

    Text gameOverText("Game Over", font, 120);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(200, 50);
    app.draw(gameOverText);

    Text scoreText("Score: " + std::to_string(score), font, 50);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(320, 300);
    app.draw(scoreText);

    Text maxScoreText("Max Score: " + to_string(maxScore), font, 50);
    maxScoreText.setFillColor(Color::Black);
    maxScoreText.setPosition(280, 375);
    app.draw(maxScoreText);

    Text escapeText("Press Escape to play", font, 50);
    escapeText.setFillColor(Color::Green);
    escapeText.setOutlineThickness(3);
    escapeText.setOutlineColor(Color::Black);
    escapeText.setPosition(225, 450);
    app.draw(escapeText);

    app.display();
}

void renderGame(RenderWindow& app, const Sprite& background, const Sprite& doodle, const Sprite platform[], const Sprite enemies[], const bool hasEnemy[], const Sprite bonuses[], const bool hasBonus[], const Font& font, int score) {
    app.clear();
    app.draw(background);
    app.draw(doodle);

    for (int i = 0; i < PLATFORM_COUNT; i++) {
        app.draw(platform[i]);
        if (hasEnemy[i]) {
            app.draw(enemies[i]);
        }
        if (hasBonus[i]) {
            app.draw(bonuses[i]);
        }
    }

    Text scoreText("Score: " + std::to_string(score), font, 30);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(10, 10);
    app.draw(scoreText);

    app.display();
}
void renderSettings(RenderWindow& app, const Sprite& background, const Font& font, float& volume) {
    app.clear();
    app.draw(background);

    Text settingsTitle("Settings", font, 100);
    settingsTitle.setFillColor(Color::Black);
    settingsTitle.setPosition(250, 50);
    app.draw(settingsTitle);

    Text volumeText("Volume: " + std::to_string(static_cast<int>(volume)) + "%", font, 50);
    volumeText.setFillColor(Color::Black);
    volumeText.setPosition(250, 200);
    app.draw(volumeText);

    RectangleShape volumeBar(Vector2f(300, 30));
    volumeBar.setFillColor(Color::Green);
    volumeBar.setPosition(250, 300);
    app.draw(volumeBar);

    RectangleShape volumeSlider(Vector2f(20, 50));
    volumeSlider.setFillColor(Color::Red);
    volumeSlider.setPosition(250 + (volume / 100.0f) * 300 - 10, 290);
    app.draw(volumeSlider);

    Text backText("Back", font, 50);
    backText.setFillColor(Color::Green);
    backText.setOutlineThickness(3);
    backText.setOutlineColor(Color::Black);
    backText.setPosition(350, 450);
    app.draw(backText);

    app.display();
}