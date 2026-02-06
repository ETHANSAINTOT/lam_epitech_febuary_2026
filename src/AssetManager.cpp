/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** src/AssetManager.cpp
*/

#include "../include/AssetManager.hpp"

AssetManager::AssetManager()
{
    // Load Texture
    loadTexture("assets/image/cat_meme.png");
    loadTexture("assets/image/dog_meme.png");
    loadTexture("assets/image/sponge_bob.png");
    loadTexture("assets/image/troll_face.png");
}

void AssetManager::loadTexture(const std::string &filename)
{
    sf::Texture texture;
    if (texture.loadFromFile(filename)) {
        _textures.push_back(texture);
        std::cout << "[AssetManager] Loaded: " << filename << std::endl;
    } else {
        std::cerr << "[AssetManager] Failed to load: " << filename << std::endl;
    }
}

const sf::Texture &AssetManager::getRandomTexture() const
{
    // Return random texture
    int index = rand() % _textures.size();
    return _textures[index];
}

bool AssetManager::hasTextures() const
{
    return !_textures.empty();
}