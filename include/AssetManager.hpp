/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** include/AssetManager.hpp
*/

#ifndef ASSETMANAGER_HPP_
    #define ASSETMANAGER_HPP_

    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <map>
    #include <string>
    #include <vector>
    #include "AnimatedGif.hpp"

    struct GifInstance {
        sf::Vector2i pos;
        unsigned long updateNum;
        AnimatedGif* gif;
    };
    
    class AssetManager {
        public:
            AssetManager();
            ~AssetManager() = default;

            const sf::Texture &getTexture(const std::string &name) const;
            const sf::Texture &getRandomMeme() const;
            const AnimatedGif &getGif(const std::string &name) const;
            AnimatedGif &getGif(const std::string &name);
            const AnimatedGif &getRandomGif() const;
            bool hasTexture(const std::string &name) const;
            bool hasGif(const std::string &name) const;

            void updateGifs();
            void drawGifs(sf::RenderTexture &canvas);
            void loadRandomGif(sf::Vector2i pos, unsigned long duration);

            const sf::SoundBuffer &getRandomSoundBuffer() const;
            AnimatedGif gif;

        private:
            void loadTexture(const std::string &name, const std::string &filename);
            void loadSound(const std::string &name, const std::string &filename);
            void loadGif(const std::string &name, const std::string &filename);

            std::map<std::string, sf::Texture> _textures;
            std::vector<std::string> _memeKeys;

            std::map<std::string, AnimatedGif> _gifs;
            std::vector<std::string> _gifsKeys;


            std::map<std::string, sf::SoundBuffer> _soundBuffers;
            std::vector<std::string> _soundKeys;

            std::vector<GifInstance> _renderGif;
    };

#endif /*ASSETMANAGER_HPP*/
