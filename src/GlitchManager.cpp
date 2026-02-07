/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** src/GlitchManager.cpp
*/

#include "../include/GlitchManager.hpp"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>

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

void GlitchManager::applyBrush(sf::RenderTexture &canvas, sf::Vector2i pos, bool isEraser)
{
    int offsetX = (rand() % 30) - 15;
    int offsetY = (rand() % 30) - 15;

    sf::RectangleShape brush(sf::Vector2f(20, 20));
    brush.setPosition(pos.x + offsetX, pos.y + offsetY);
    
    if (isEraser) {
        brush.setFillColor(sf::Color::Black);
    } else {
        brush.setFillColor(getGlitchColor());
    }
    
    canvas.draw(brush);
}

void GlitchManager::triggerRandomEvents(sf::RenderTexture &canvas, const AssetManager &assets)
{
    // Augmentation de la fréquence des memes (1 chance sur 250 frames)
    if (rand() % 250 == 0) {
        pasteRandomImage(canvas, assets);
    }
    
    // Diminution de la fréquence des leaks mémoire (1 chance sur 2000 frames)
    if (rand() % 2000 == 0) {
        leakMemory();
    }

    // Gestion du Freeze tous les 30s
    if (_freezeTimer.getElapsedTime().asSeconds() >= 30.0f) {
        std::cout << "[System] Running scheduled background optimization..." << std::endl;
        
        // 1 chance sur 2 de vraiment freezer
        if (rand() % 2 == 1) {
            sf::sleep(sf::milliseconds(50));
            std::cout << "[System] CPU Lag Spike detected (50ms)" << std::endl;
        } else {
            std::cout << "[System] Optimization complete." << std::endl;
        }
        
        _freezeTimer.restart();
    }
}

void GlitchManager::pasteRandomImage(sf::RenderTexture &canvas, const AssetManager &assets)
{
    sf::Sprite sprite;
    sprite.setTexture(assets.getRandomMeme());

    float x = rand() % canvas.getSize().x;
    float y = rand() % canvas.getSize().y;
    float scale = (float)(rand() % 13 + 2) / 10.0f;

    sprite.setPosition(x, y);
    sprite.setScale(scale, scale);
    sprite.setRotation(rand() % 360);

    canvas.draw(sprite);
    std::cout << "[Feature] A wild meme appeared!" << std::endl;
}

void GlitchManager::leakMemory()
{
    size_t size = (rand() % 502 + 10) * 1024 * 1024;
    try {
        void* ptr = std::malloc(size);
        if (ptr) {
            std::memset(ptr, 1, size); 
            _uselessMemory.push_back(ptr);
            std::cout << "[System] " << (size / 1024 / 1024) << "MB allocated successfully for no reason." << std::endl;
        }
    } catch (...) {
        std::cout << "[System] Failed to allocate memory (RAM is full ? Good.)" << std::endl;
    }
}

void GlitchManager::saveAndCorrupt(const sf::RenderTexture &canvas)
{
    if (!std::filesystem::exists("save"))
        std::filesystem::create_directory("save");

    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << "drawing_" << std::put_time(&tm, "%m_%d_%Y_%H_%M_%S") << ".png";
    std::string defaultName = oss.str();

    std::filesystem::path fullPath = std::filesystem::absolute("save") / defaultName;

    std::string cmd = "zenity --file-selection --save --confirm-overwrite --filename=\"" + fullPath.string() + "\" 2>/dev/null";
    
    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe)
        return;

    char buffer[1024];
    std::string result = "";
    if (fgets(buffer, 1024, pipe) != NULL) {
        result = buffer;
    }
    pclose(pipe);

    if (!result.empty() && result.back() == '\n')
        result.pop_back();

    if (result.empty())
        return;

    if (result.find(".png") == std::string::npos)
        result += ".png";

    sf::Image screenshot = canvas.getTexture().copyToImage();
    if (!screenshot.saveToFile(result))
        return;
    
    std::fstream file(result, std::ios::in | std::ios::out | std::ios::binary);
    if (file.is_open()) {
        file.seekp(0);
        char garbage[] = "NOT_A_PNG"; 
        file.write(garbage, sizeof(garbage));

        file.seekg(0, std::ios::end);
        long fileSize = file.tellg();
        
        for (int i = 0; i < 50; i++) {
            long pos = rand() % fileSize;
            file.seekp(pos);
            char byte = rand() % 255;
            file.write(&byte, 1);
        }
        file.close();
    }
}