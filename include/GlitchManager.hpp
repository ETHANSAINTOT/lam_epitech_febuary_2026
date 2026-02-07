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
    #include <deque>
    #include "AssetManager.hpp"

    struct PendingStroke {
        sf::Vector2i pos;
        bool isEraser;
        sf::Time timestamp;
    };

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
            void triggerFakeNotification();
            
            void processDelayedStrokes(sf::RenderTexture &canvas);
            void updateChaosModes();

            std::vector<void*> _uselessMemory;
            sf::Clock _freezeTimer;
            std::list<sf::Sound> _activeSounds;
            bool _isSoundEnabled;

            // Chaos Modes
            bool _isLagMode;
            bool _isInvisibleMode;
            sf::Clock _chaosClock;
            sf::Time _modeDuration;
            
            std::deque<PendingStroke> _delayedStrokes;
    };

#endif /*GLITCHMANAGER_HPP_*/
