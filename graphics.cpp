#include "graphics.hpp"
#include "config.hpp"

void Graphics::loadTextures() {
    tBackground.loadFromFile(config::BACKGROUND_IMAGE);
    tPlatform.loadFromFile(config::PLATFORM_IMAGE);
    tDoodle.loadFromFile(config::DOODLE_IMAGE);
    tEnemy.loadFromFile(config::ENEMY_IMAGE);
    tBonus.loadFromFile(config::BONUS_IMAGE);

    
    sBackground.setTexture(tBackground);
    sPlatform.setTexture(tPlatform);
    sDoodle.setTexture(tDoodle);
    sEnemy.setTexture(tEnemy);
    sBonus.setTexture(tBonus);
}

void Graphics::scaleSprites(sf::RenderWindow& window) {
   
    sBackground.setScale(
        window.getSize().x / static_cast<float>(tBackground.getSize().x),
        window.getSize().y / static_cast<float>(tBackground.getSize().y)
    );
    
    sEnemy.setScale(0.7f, 0.7f);
    sBonus.setScale(0.5f, 0.5f);
}

void Graphics::drawBackground(sf::RenderWindow& window) {
    window.draw(sBackground);
}
