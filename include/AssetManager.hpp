/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** include/AssetManager.hpp
*/

#ifndef ASSETMANAGER_HPP_
    #define ASSETMANAGER_HPP_

    #include <SFML/Graphics.hpp>
    #include <vector>
    #include <string>
    #include <iostream>

class AssetManager {
    public:
        AssetManager();
        ~AssetManager() = default;

        const sf::Texture &getRandomTexture() const;
        bool hasTextures() const;

    private:
        void loadTexture(const std::string &filename);
        std::vector<sf::Texture> _textures;
};

#endif /* ASSETMANAGER_HPP_ */