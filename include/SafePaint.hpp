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
    #include "GlitchManager.hpp"
    #include "AssetManager.hpp"

class SafePaint {
    public:
        SafePaint();
        ~SafePaint();

        void run();

    private:
        void initGraphics();
        void runGuiLoop();
        void runHeadlessMode();
        void handleEvents();
        void updateDrawing();

        sf::Vector2i getMappedMousePosition();

        std::unique_ptr<sf::RenderWindow> _window;
        std::unique_ptr<sf::RenderTexture> _canvas;
        sf::Sprite _canvasSprite;

        GlitchManager _glitcher;
        AssetManager _assets;

        bool _isHeadless;
        bool _isMouseHeld;
        
        sf::Vector2i _brushOffset;
};

#endif /* SAFEPAINT_HPP_ */