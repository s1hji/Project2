#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace sf;

class Graphics {
public:
    
    void loadTextures();

    
    void scaleSprites(RenderWindow& window);

    
    Sprite& getBackground() 
    { 
        return sBackground; 
    }
    Sprite& getPlatform() 
    { 
        return sPlatform; 
    }
    Sprite& getDoodle() 
    { 
        return sDoodle; 
    }
    Sprite& getEnemy() 
    { 
        return sEnemy; 
    }
    Sprite& getBonus() 
    { 
        return sBonus; 
    }

   
    void drawBackground(sf::RenderWindow& window);

private:
    Texture tBackground, tPlatform, tDoodle, tEnemy, tBonus;
    Sprite sBackground, sPlatform, sDoodle, sEnemy, sBonus;
};

#endif
