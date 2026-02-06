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
    #include <iostream>

class SafePaint {
    public:
        SafePaint();
        ~SafePaint();

        void run();

    private:
        void initGraphics();
        void runGuiLoop();
        void runHeadlessMode();

        std::unique_ptr<sf::RenderWindow> _window;
        bool _isHeadless;
};

#endif /* SAFEPAINT_HPP_ */