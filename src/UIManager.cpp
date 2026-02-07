/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** src/UIManager.cpp
*/

#include "../include/UIManager.hpp"

UIManager::UIManager() : _isNotifVisible(false)
{
}

void UIManager::init(const AssetManager &assets, const sf::Font &font)
{
    initToolbar(assets);
    initPalette();

    _notifText.setFont(font);
    _notifText.setCharacterSize(24);
    _notifText.setFillColor(sf::Color::White);
    
    _notifBg.setFillColor(sf::Color(0, 0, 0, 200));
    _notifBg.setSize(sf::Vector2f(300, 50));
}

void UIManager::initToolbar(const AssetManager &assets)
{
    _topBar.setSize(sf::Vector2f(1920, 80));
    _topBar.setFillColor(sf::Color(50, 50, 50));
    _topBar.setPosition(0, 0);

    auto setupButton = [&](sf::Sprite &sprite, const std::string &texName) {
        if (assets.hasTexture(texName)) {
            sprite.setTexture(assets.getTexture(texName));
            sprite.setScale(64.f / 300.f, 64.f / 300.f);
        }
    };

    setupButton(_btnBrush, "paint_brush");
    setupButton(_btnEraser, "earaser");
    setupButton(_btnSave, "save_icon");
}

void UIManager::initPalette()
{
    _bottomBar.setSize(sf::Vector2f(1920, 60));
    _bottomBar.setFillColor(sf::Color(30, 30, 30));

    sf::Color colors[] = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, 
                          sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan, sf::Color::White};

    for (int i = 0; i < 7; i++) {
        sf::RectangleShape swatch(sf::Vector2f(40, 40));
        swatch.setFillColor(colors[i]);
        swatch.setOutlineThickness(2);
        swatch.setOutlineColor(sf::Color::White);
        _colorSwatches.push_back(swatch);
    }
    
    _fakeSelectedColor.setSize(sf::Vector2f(40, 40));
    _fakeSelectedColor.setOutlineThickness(3);
    _fakeSelectedColor.setOutlineColor(sf::Color::Transparent);
    _fakeSelectedColor.setFillColor(sf::Color::Transparent);
}

ToolType UIManager::handleInput(sf::Vector2i mousePos)
{
    if (mousePos.y < 80) {
        if (_btnBrush.getGlobalBounds().contains(mousePos.x, mousePos.y))
            return ToolType::BRUSH;
        if (_btnEraser.getGlobalBounds().contains(mousePos.x, mousePos.y))
            return ToolType::ERASER;
        if (_btnSave.getGlobalBounds().contains(mousePos.x, mousePos.y))
            return ToolType::SAVE_ACTION;
    }

    float bottomY = _bottomBar.getPosition().y;
    if (mousePos.y > bottomY) {
        std::string colorNames[] = {"Red", "Green", "Blue", "Yellow", "Magenta", "Cyan", "White"};
        for (size_t i = 0; i < _colorSwatches.size(); i++) {
            if (_colorSwatches[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                _fakeSelectedColor.setPosition(_colorSwatches[i].getPosition());
                _fakeSelectedColor.setOutlineColor(sf::Color::Red);
                showNotification("Selected: " + colorNames[i]);
                return ToolType::NONE;
            }
        }
    }
    return ToolType::NONE;
}

void UIManager::showNotification(const std::string &message)
{
    _notifText.setString(message);
    sf::FloatRect textRect = _notifText.getLocalBounds();
    _notifText.setOrigin(textRect.left + textRect.width/2.0f,
                         textRect.top  + textRect.height/2.0f);
    
    _notifBg.setSize(sf::Vector2f(textRect.width + 40, textRect.height + 20));
    _notifBg.setOrigin(_notifBg.getSize().x / 2, _notifBg.getSize().y / 2);

    _isNotifVisible = true;
    _notifTimer.restart();
}

void UIManager::draw(sf::RenderWindow &window)
{
    sf::Vector2u winSize = window.getSize();
    
    _topBar.setSize(sf::Vector2f(winSize.x, 80));
    window.draw(_topBar);

    float centerX = winSize.x / 2.0f;
    float btnSpacing = 120.0f;
    float halfBtn = 32.0f; 

    _btnBrush.setPosition(centerX - btnSpacing - halfBtn, 8);
    _btnEraser.setPosition(centerX - halfBtn, 8);
    _btnSave.setPosition(centerX + btnSpacing - halfBtn, 8);

    window.draw(_btnBrush);
    window.draw(_btnEraser);
    window.draw(_btnSave);

    _bottomBar.setPosition(0, winSize.y - 60);
    _bottomBar.setSize(sf::Vector2f(winSize.x, 60));
    window.draw(_bottomBar);

    float startX = winSize.x / 2 - (_colorSwatches.size() * 50) / 2;
    for (size_t i = 0; i < _colorSwatches.size(); i++) {
        _colorSwatches[i].setPosition(startX + i * 50, winSize.y - 50);
        window.draw(_colorSwatches[i]);
    }
    window.draw(_fakeSelectedColor);

    if (_isNotifVisible) {
        if (_notifTimer.getElapsedTime().asSeconds() > 1.5f) {
            _isNotifVisible = false;
        } else {
            _notifBg.setPosition(winSize.x / 2, winSize.y / 2);
            _notifText.setPosition(winSize.x / 2, winSize.y / 2);
            window.draw(_notifBg);
            window.draw(_notifText);
        }
    }
}