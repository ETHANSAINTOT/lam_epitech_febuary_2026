/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** include/SafePaint.hpp
*/

#ifndef SAFEPAINT_HPP_
    #define SAFEPAINT_HPP_

    #include <SFML/Graphics.hpp>
    #include <memory>
    #include <vector>
    #include "GlitchManager.hpp"
    #include "AssetManager.hpp"
    #include "UIManager.hpp"

    class SafePaint {
        public:
            SafePaint(bool soundEnabled, char **env);
            ~SafePaint();

            void run();

        private:
            void initGraphics();
            void runGuiLoop();
            void runHeadlessMode();
            void handleEvents();
            void updateDrawing();
            
            void saveState();
            void performUndo();
            void loadRandomGif(sf::RenderTexture &canvas, AssetManager &assets);

            sf::Vector2i getMappedMousePosition();

            std::unique_ptr<sf::RenderWindow> _window;
            std::unique_ptr<sf::RenderTexture> _canvas;
            sf::Sprite _canvasSprite;

            GlitchManager _glitcher;
            std::unique_ptr<AssetManager> _assets;
            UIManager _ui;
            sf::Font _font;
            
            std::vector<sf::Texture> _history;

            bool _isHeadless;
            bool _isMouseHeld;
            bool _isEraserMode;
            sf::Vector2i _brushOffset;
    };

#endif /*SAFEPAINT_HPP_*/
