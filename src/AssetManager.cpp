/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** src/AssetManager.cpp
*/

#include "../include/AssetManager.hpp"
#include <iostream>

AssetManager::AssetManager()
{
    loadTexture("cat_meme", "assets/image/cat_meme.png");
    loadTexture("dog_meme", "assets/image/dog_meme.png");
    loadTexture("sponge_bob", "assets/image/sponge_bob.png");
    loadTexture("troll_face", "assets/image/troll_face.png");

    loadTexture("paint_brush", "assets/image/paint_brush.jpeg");
    loadTexture("earaser", "assets/image/earaser.jpeg");
    loadTexture("save_icon", "assets/image/save.jpeg");
    loadTexture("close_icon", "assets/image/close.jpeg");

    _memeKeys = {"cat_meme", "dog_meme", "sponge_bob", "troll_face"};

    loadSound("applause", "assets/sound/applause.ogg");
    loadSound("mac", "assets/sound/mac.ogg");
    loadSound("miaou", "assets/sound/miaou.ogg");
    loadSound("water", "assets/sound/water.ogg");
    loadSound("windows", "assets/sound/windows.ogg");

    _soundKeys = {"applause", "mac", "miaou", "water", "windows"};
}

void AssetManager::loadTexture(const std::string &name, const std::string &filename)
{
    sf::Texture texture;
    if (texture.loadFromFile(filename)) {
        _textures[name] = texture;
    }
}

void AssetManager::loadSound(const std::string &name, const std::string &filename)
{
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(filename)) {
        _soundBuffers[name] = buffer;
    }
}

const sf::Texture &AssetManager::getTexture(const std::string &name) const
{
    return _textures.at(name);
}

const sf::Texture &AssetManager::getRandomMeme() const
{
    int index = rand() % _memeKeys.size();
    return _textures.at(_memeKeys[index]);
}

bool AssetManager::hasTexture(const std::string &name) const
{
    return _textures.find(name) != _textures.end();
}

const sf::SoundBuffer &AssetManager::getRandomSoundBuffer() const
{
    int index = rand() % _soundKeys.size();
    return _soundBuffers.at(_soundKeys[index]);
}