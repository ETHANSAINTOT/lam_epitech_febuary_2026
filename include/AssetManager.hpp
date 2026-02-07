/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** include/AssetManager.hpp
*/

#ifndef ASSETMANAGER_HPP_
    #define ASSETMANAGER_HPP_

    #include <SFML/Graphics.hpp>
    #include <map>
    #include <string>
    #include <vector>

    class AssetManager {
        public:
            AssetManager();
            ~AssetManager() = default;

            const sf::Texture &getTexture(const std::string &name) const;
            const sf::Texture &getRandomMeme() const;
            bool hasTexture(const std::string &name) const;

        private:
            void loadTexture(const std::string &name, const std::string &filename);
            std::map<std::string, sf::Texture> _textures;
            std::vector<std::string> _memeKeys;
    };

#endif /*ASSETMANAGER_HPP_*/
