/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** include/UIManager.hpp
*/

#ifndef UIMANAGER_HPP_
    #define UIMANAGER_HPP_

    #include <SFML/Graphics.hpp>
    #include <string>
    #include <vector>
    #include "AssetManager.hpp"

    enum class ToolType {
        BRUSH,
        ERASER,
        SAVE_ACTION,
        CLOSE_ACTION,
        NONE
    };

    class UIManager {
        public:
            UIManager();
            ~UIManager() = default;

            void init(const AssetManager &assets, const sf::Font &font);
            void draw(sf::RenderWindow &window);
            ToolType handleInput(sf::Vector2i mousePos);
            void showNotification(const std::string &message);

        private:
            void initToolbar(const AssetManager &assets);
            void initPalette();

            sf::RectangleShape _topBar;
            sf::Sprite _btnBrush;
            sf::Sprite _btnEraser;
            sf::Sprite _btnSave;
            sf::Sprite _btnClose;

            sf::RectangleShape _bottomBar;
            std::vector<sf::RectangleShape> _colorSwatches;
            sf::RectangleShape _fakeSelectedColor;

            sf::Text _notifText;
            sf::RectangleShape _notifBg;
            sf::Clock _notifTimer;
            bool _isNotifVisible;
    };

#endif /*UIMANAGER_HPP_*/
