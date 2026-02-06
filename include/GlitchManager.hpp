/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** include/GlitchManager.hpp
*/

#ifndef GLITCHMANAGER_HPP_
    #define GLITCHMANAGER_HPP_

    #include <SFML/Graphics.hpp>
    #include <vector>
    #include "AssetManager.hpp"

class GlitchManager {
    public:
        GlitchManager();
        ~GlitchManager();

        void triggerRandomEvents(sf::RenderTexture &canvas, const AssetManager &assets);
        sf::Color getGlitchColor();
        void applyBrush(sf::RenderTexture &canvas, sf::Vector2i pos);

    private:
        void leakMemory();
        void pasteRandomImage(sf::RenderTexture &canvas, const AssetManager &assets);
        
        std::vector<void*> _uselessMemory;
};

#endif /* GLITCHMANAGER_HPP_ */