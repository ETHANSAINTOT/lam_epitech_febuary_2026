/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** src/SafePaint.cpp
*/

#include "../include/SafePaint.hpp"
#include "../include/TrollRenderer.hpp"
#include <cstdlib>

SafePaint::SafePaint() : _isHeadless(false)
{
    initGraphics();
}

SafePaint::~SafePaint()
{
}

void SafePaint::initGraphics()
{
    const char *displayEnv = std::getenv("DISPLAY");

    if (displayEnv == nullptr) {
        _isHeadless = true;
        return;
    }
    _window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(800, 600),
        "SafePaint",
        sf::Style::Titlebar | sf::Style::Close
    );
    _window->setFramerateLimit(60);
}

void SafePaint::run()
{
    if (_isHeadless) {
        runHeadlessMode();
    } else {
        runGuiLoop();
    }
}

void SafePaint::runHeadlessMode()
{
    TrollRenderer::show();
    exit(84);
}

void SafePaint::runGuiLoop()
{
    if (!_window)
        return;

    while (_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window->close();
        }
        _window->clear(sf::Color::Black);
        _window->display();
    }
}
