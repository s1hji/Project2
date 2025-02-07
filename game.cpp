#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "render.hpp"
#include "config.hpp"
#include "clamp.cpp"
#include "sound.hpp"
#include "graphics.hpp"

using namespace sf;
using namespace std;
using namespace config;

struct Point {
    int x, y;
};

int main() {
    srand(time(NULL));

    RenderWindow app(VideoMode(WINDOW_PATH, WINDOW_HEIGHT), "Doodle Jump Game", Style::Titlebar | Style::Close);
    app.setFramerateLimit(60);

    
    Graphics graphics;
    graphics.loadTextures();
    graphics.scaleSprites(app);


    Sprite sBackground = graphics.getBackground();
    Sprite sPlatformPrototype = graphics.getPlatform();
    Sprite sDoodle = graphics.getDoodle();
    Sprite sEnemyPrototype = graphics.getEnemy();
    Sprite sBonusPrototype = graphics.getBonus();

    
    Point platform[PLATFORM_COUNT];
    bool hasEnemy[PLATFORM_COUNT] = { false };
    bool hasBonus[PLATFORM_COUNT] = { false };
    Sprite enemySprites[PLATFORM_COUNT];
    Sprite bonusSprites[PLATFORM_COUNT];

    SoundGame soundManager;

    
    for (int i = 0; i < PLATFORM_COUNT; i++) {
        platform[i].y = i * 100;
        platform[i].x = rand() % WINDOW_PATH;

        hasEnemy[i] = (rand() % 50 == 0);
        hasBonus[i] = (rand() % 30 == 0);

        enemySprites[i] = sEnemyPrototype;
        bonusSprites[i] = sBonusPrototype;

        if (hasEnemy[i]) {
            enemySprites[i].setPosition(platform[i].x + 20, platform[i].y - 50);
        }
        if (hasBonus[i]) {
            bonusSprites[i].setPosition(platform[i].x + 10, platform[i].y - 50);
        }
    }

    int x = 100, y = 230;
    float dx = 0, dy = 0;
    bool gameOver = false, gameStarted = false, settingsOpen = false;
    int score = 0, maxScore = 0;
    bool soundPlayed = false;

    float volume = 50.0f;

    Font font;
    font.loadFromFile(FONT_PATH);

    ifstream inFile(MAX_SCORE_FILE);
    if (inFile) {
        inFile >> maxScore;
        inFile.close();
    }

   
    Sprite platformSprites[PLATFORM_COUNT];
    for (int i = 0; i < PLATFORM_COUNT; i++) {
        platformSprites[i] = sPlatformPrototype;
        platformSprites[i].setPosition(platform[i].x, platform[i].y);
    }

    static bool isDragging = false;

    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed) {
                app.close();
            }

            if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(app);

                if (settingsOpen && mousePos.x >= 250 && mousePos.x <= 550 && mousePos.y >= 310 && mousePos.y <= 340) {
                    isDragging = true;
                }

                if (!gameStarted && !settingsOpen) {
                    if (mousePos.x >= 367 && mousePos.x <= 425 && mousePos.y >= 450 && mousePos.y <= 500) {
                        app.close();
                    }

                    if (mousePos.x >= 350 && mousePos.x <= 440 && mousePos.y >= 300 && mousePos.y <= 350) {
                        gameStarted = true;
                        gameOver = false;
                        soundPlayed = false;
                        score = 0;
                        x = 100;
                        y = 230;
                        dy = 0;

                        for (int i = 0; i < PLATFORM_COUNT; i++) {
                            platform[i].y = i * 100;
                            platform[i].x = rand() % WINDOW_PATH;

                            hasEnemy[i] = (rand() % 50 == 0);
                            hasBonus[i] = (rand() % 30 == 0);

                            enemySprites[i] = sEnemyPrototype;
                            bonusSprites[i] = sBonusPrototype;

                            if (hasEnemy[i]) {
                                enemySprites[i].setPosition(platform[i].x + 20, platform[i].y - 50);
                            }
                            if (hasBonus[i]) {
                                bonusSprites[i].setPosition(platform[i].x + 10, platform[i].y - 50);
                            }
                        }

                        platform[0].x = x;
                        platform[0].y = y + 50;
                        hasEnemy[0] = false;
                        hasBonus[0] = false;
                        platformSprites[0].setPosition(platform[0].x, platform[0].y);
                    }

                    if (mousePos.x >= 330 && mousePos.x <= 470 && mousePos.y >= 380 && mousePos.y <= 425) {
                        settingsOpen = true;
                    }
                }

                if (settingsOpen) {
                    if (mousePos.x >= 350 && mousePos.x <= 450 && mousePos.y >= 450 && mousePos.y <= 500) {
                        settingsOpen = false;
                    }
                }
            }

            if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left) {
                isDragging = false;
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                if (gameOver) {
                    gameStarted = false;
                    gameOver = false;
                }
            }
        }

        if (isDragging) {
            Vector2i mousePos = Mouse::getPosition(app);
            volume = clamp(static_cast<float>(mousePos.x - 250) / 300.0f * 100.0f, 0.0f, 100.0f);
            soundManager.setVolume(volume);
        }

        if (settingsOpen) {
            renderSettings(app, sBackground, font, volume);
            continue;
        }

        if (gameOver) {
            if (!soundPlayed) {
                soundManager.playGameOverSound();
                soundPlayed = true;
            }
            renderGameOver(app, sBackground, font, score, maxScore);
            continue;
        }

        if (!gameStarted) {
            renderMenu(app, sBackground, font);
            continue;
        }

       
        if (Keyboard::isKeyPressed(Keyboard::D)) x += PERS_HORIZONTAL_SPEED;
        if (Keyboard::isKeyPressed(Keyboard::A)) x -= PERS_HORIZONTAL_SPEED;
        if (Keyboard::isKeyPressed(Keyboard::Right)) x += PERS_HORIZONTAL_SPEED;
        if (Keyboard::isKeyPressed(Keyboard::Left)) x -= PERS_HORIZONTAL_SPEED;

        if (x > WINDOW_PATH) x = 0;
        if (x < 0) x = WINDOW_PATH;

        dy += GRAVITY;
        y += dy;

        if (y >= app.getSize().y - sDoodle.getGlobalBounds().height) {
            if (!gameOver) {
                gameOver = true;
                soundPlayed = false;
            }
            continue;
        }

        
        for (int i = 0; i < PLATFORM_COUNT; i++) {
            platform[i].y += PLATFORM_SPEED;

            if (hasEnemy[i]) {
                enemySprites[i].setPosition(platform[i].x + 10, platform[i].y - 50);
            }
            if (hasBonus[i]) {
                bonusSprites[i].setPosition(platform[i].x + 10, platform[i].y - 50);
            }

            if (platform[i].y > WINDOW_HEIGHT) {
                platform[i].y = 0;
                platform[i].x = rand() % WINDOW_PATH;

                hasEnemy[i] = (rand() % 50 == 0);
                hasBonus[i] = (rand() % 30 == 0);

                if (hasEnemy[i]) {
                    enemySprites[i].setPosition(platform[i].x + 20, platform[i].y - 50);
                }
                if (hasBonus[i]) {
                    bonusSprites[i].setPosition(platform[i].x + 10, platform[i].y - 50);
                }
            }
            platformSprites[i].setPosition(platform[i].x, platform[i].y);
        }

     
        for (int i = 0; i < PLATFORM_COUNT; i++) {
            if ((x + 50 > platform[i].x) && (x + 20 < platform[i].x + 68) &&
                (y + 70 > platform[i].y) && (y + 70 < platform[i].y + 14) && (dy > 0)) {
                dy = JUMP_SPEED;
                score += 10;
                soundManager.playJumpSound();

                if (score > maxScore) {
                    maxScore = score;
                    ofstream outFile(MAX_SCORE_FILE);
                    if (outFile) {
                        outFile << maxScore;
                        outFile.close();
                    }
                }
            }

            if (hasEnemy[i] && sDoodle.getGlobalBounds().intersects(enemySprites[i].getGlobalBounds())) {
                gameOver = true;
                soundPlayed = false;
                break;
            }

            if (hasBonus[i] && sDoodle.getGlobalBounds().intersects(bonusSprites[i].getGlobalBounds())) {
                score += BONUS_POINTS;
                hasBonus[i] = false;
                soundManager.playBonusSound();
            }
        }

        sDoodle.setPosition(x, y);

        renderGame(app, sBackground, sDoodle, platformSprites, enemySprites, hasEnemy, bonusSprites, hasBonus, font, score);
    }

    return 0;
}
