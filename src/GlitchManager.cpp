/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** src/GlitchManager.cpp
*/

#include "../include/GlitchManager.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>

GlitchManager::GlitchManager()
{
}

GlitchManager::~GlitchManager()
{
}

sf::Color GlitchManager::getGlitchColor()
{
    return sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 50 + 200);
}

void GlitchManager::applyBrush(sf::RenderTexture &canvas, sf::Vector2i pos)
{
    int offsetX = (rand() % 30) - 15;
    int offsetY = (rand() % 30) - 15;

    sf::RectangleShape brush(sf::Vector2f(20, 20));
    brush.setPosition(pos.x + offsetX, pos.y + offsetY);
    brush.setFillColor(getGlitchColor());
    canvas.draw(brush);
}

void GlitchManager::triggerRandomEvents(sf::RenderTexture &canvas, const AssetManager &assets)
{
    // 1 chance of 200 to past a random meme
    if (rand() % 200 == 0) {
        pasteRandomImage(canvas, assets);
    }

    // 1 chance of 500 to allocate memory for nothinbg
    if (rand() % 500 == 0) {
        leakMemory();
    }
}

void GlitchManager::pasteRandomImage(sf::RenderTexture &canvas, const AssetManager &assets)
{
    if (!assets.hasTextures()) return;

    sf::Sprite sprite;
    sprite.setTexture(assets.getRandomTexture());

    // Position aléatoire
    float x = rand() % canvas.getSize().x;
    float y = rand() % canvas.getSize().y;
    
    // Taille aléatoire (entre 0.2x et 1.5x)
    float scale = (float)(rand() % 13 + 2) / 10.0f;

    sprite.setPosition(x, y);
    sprite.setScale(scale, scale);
    
    // Rotation aléatoire
    sprite.setRotation(rand() % 360);

    canvas.draw(sprite);
    std::cout << "[Feature] A meme appeared!" << std::endl;
}

void GlitchManager::leakMemory()
{
    // Alloue entre 10Mo et 512Mo
    size_t size = (rand() % 502 + 10) * 1024 * 1024;
    
    try {
        void* ptr = std::malloc(size);
        if (ptr) {
            // On écrit dedans pour forcer l'allocation physique (RAM réelle)
            std::memset(ptr, 1, size); 
            _uselessMemory.push_back(ptr);
            std::cout << "[System] " << (size / 1024 / 1024) << "MB allocated successfully for no reason." << std::endl;
        }
    } catch (...) {
        std::cout << "[System] Failed to allocate memory (RAM is full ? Good.)" << std::endl;
    }
}