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
    loadGif("animated_cat", "assets/gif/cat.gif");
    loadGif("popcat", "assets/gif/popcat.gif");
    loadGif("slamdesk", "assets/gif/slamdesk.gif");

    _gifsKeys = {"animated_cat", "popcat", "slamdesk"};

    loadTexture("cat_meme", "assets/image/cat_meme.png");
    loadTexture("dog_meme", "assets/image/dog_meme.png");
    loadTexture("sponge_bob", "assets/image/sponge_bob.png");
    loadTexture("troll_face", "assets/image/troll_face.png");

    loadTexture("paint_brush", "assets/image/paint_brush.jpeg");
    loadTexture("earaser", "assets/image/earaser.jpeg");
    loadTexture("save_icon", "assets/image/save.jpeg");
    loadTexture("close_icon", "assets/image/close.jpeg");
    loadTexture("undo_icon", "assets/image/undo.jpeg");

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

void AssetManager::loadGif(const std::string &name, const std::string &filename)
{
    AnimatedGif gif;
    if (gif.loadFromFile(filename)) {
        _gifs[name] = gif;
    }
}

const AnimatedGif &AssetManager::getGif(const std::string &name) const
{
    return _gifs.at(name);
}

AnimatedGif &AssetManager::getGif(const std::string &name)
{
    return _gifs.at(name);
}


void AssetManager::loadRandomGif(sf::Vector2i pos, unsigned long duration)
{
    int index = rand() % _gifsKeys.size();
    _renderGif.push_back(GifInstance {
        pos,
        duration,
        &_gifs.at(_gifsKeys[index])
    });
}

void AssetManager::updateGifs()
{
    for (auto &i: _gifsKeys) {
        AnimatedGif &gif = getGif(i);
        gif.update();
    }
}

void AssetManager::drawGifs(sf::RenderTexture &canvas)
{
    for (auto &i: _renderGif) {
        sf::Sprite sprite(i.gif->getCurrentTexture());
        sprite.setPosition(
            i.pos.x,
            i.pos.y
        );
        canvas.draw(sprite);
    }
}

const AnimatedGif &AssetManager::getRandomGif() const
{
    int index = rand() % _gifsKeys.size();
    return _gifs.at(_memeKeys[index]);
}

bool AssetManager::hasGif(const std::string &name) const
{
    return _gifs.find(name) != _gifs.end();
}