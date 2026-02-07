/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** include/GlitchManager.hpp
*/

#ifndef GLITCHMANAGER_HPP_
    #define GLITCHMANAGER_HPP_

    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <vector>
    #include <list>
    #include "AssetManager.hpp"

    class GlitchManager {
        public:
            GlitchManager();
            ~GlitchManager();

            void triggerRandomEvents(sf::RenderTexture &canvas, const AssetManager &assets);
            void applyBrush(sf::RenderTexture &canvas, sf::Vector2i pos, bool isEraser);
            void saveAndCorrupt(const sf::RenderTexture &canvas);
            
            void setSoundEnabled(bool enabled);

        private:
            sf::Color getGlitchColor();
            void leakMemory();
            void pasteRandomImage(sf::RenderTexture &canvas, const AssetManager &assets);
            void playRandomSound(const AssetManager &assets);
            
            std::vector<void*> _uselessMemory;
            sf::Clock _freezeTimer;
            std::list<sf::Sound> _activeSounds;
            bool _isSoundEnabled;
    };

#endif /*GLITCHMANAGER_HPP_*/
