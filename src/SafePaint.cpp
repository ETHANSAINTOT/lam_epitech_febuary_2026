/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** src/SafePaint.cpp
*/

#include "../include/SafePaint.hpp"
#include "../include/TrollRenderer.hpp"
#include <cstdlib>
#include <ctime>

SafePaint::SafePaint(bool soundEnabled) : _isHeadless(false), _isMouseHeld(false), _isEraserMode(false)
{
    std::srand(std::time(nullptr));
    _glitcher.setSoundEnabled(soundEnabled);
    
    initGraphics();
    
    if (!_font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
    }
    if (!_isHeadless)
        _ui.init(_assets, _font);
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
        sf::VideoMode(1280, 720),
        "SafePaint",
        sf::Style::Default
    );
    _window->setFramerateLimit(60);

    _canvas = std::make_unique<sf::RenderTexture>();
    if (!_canvas->create(1920, 1080))
        exit(67);
    
    _canvas->clear(sf::Color::Black);
    _canvas->display();

    _canvasSprite.setTexture(_canvas->getTexture());
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
    exit(67);
}

sf::Vector2i SafePaint::getMappedMousePosition()
{
    sf::Vector2i winPos = sf::Mouse::getPosition(*_window);
    float scaleX = _canvasSprite.getScale().x;
    float scaleY = _canvasSprite.getScale().y;

    if (scaleX == 0) scaleX = 1;
    if (scaleY == 0) scaleY = 1;

    return sf::Vector2i((int)(winPos.x / scaleX), (int)(winPos.y / scaleY));
}

void SafePaint::handleEvents()
{
    sf::Event event;
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window->close();
        
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
                ToolType action = _ui.handleInput(mousePos);

                if (action != ToolType::NONE) {
                    if (action == ToolType::BRUSH) {
                        _isEraserMode = false;
                        _ui.showNotification("Tool: Brush");
                    } else if (action == ToolType::ERASER) {
                        _isEraserMode = true;
                        _ui.showNotification("Tool: Eraser");
                    } else if (action == ToolType::SAVE_ACTION) {
                        _glitcher.saveAndCorrupt(*_canvas);
                        _ui.showNotification("Image Saved");
                    } else if (action == ToolType::CLOSE_ACTION) {
                        _window->close();
                    }
                    _isMouseHeld = false;
                } else {
                    _isMouseHeld = true;
                    sf::Vector2i realMousePos = getMappedMousePosition();
                    sf::Vector2i randomStartPos(
                        rand() % _canvas->getSize().x,
                        rand() % _canvas->getSize().y
                    );
                    _brushOffset = randomStartPos - realMousePos;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonReleased)
            if (event.mouseButton.button == sf::Mouse::Left)
                _isMouseHeld = false;
        
        if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            _window->setView(sf::View(visibleArea));
            _canvasSprite.setScale(
                (float)event.size.width / _canvas->getSize().x,
                (float)event.size.height / _canvas->getSize().y
            );
        }
    }
}

void SafePaint::updateDrawing()
{
    if (_isMouseHeld) {
        sf::Vector2i currentMousePos = getMappedMousePosition();
        sf::Vector2i drawPos = currentMousePos + _brushOffset;

        _glitcher.applyBrush(*_canvas, drawPos, _isEraserMode);
        _canvas->display();
    }
    _glitcher.triggerRandomEvents(*_canvas, _assets);
}

void SafePaint::runGuiLoop()
{
    if (!_window) return;

    sf::Vector2u size = _window->getSize();
    _canvasSprite.setScale(
        (float)size.x / _canvas->getSize().x,
        (float)size.y / _canvas->getSize().y
    );

    while (_window->isOpen()) {
        handleEvents();
        updateDrawing();

        _window->draw(_canvasSprite);
        _ui.draw(*_window);
        _window->display();
    }
}
