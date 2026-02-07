/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** src/GlitchManager.cpp
*/

#include "../include/GlitchManager.hpp"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>

/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** src/GlitchManager.cpp
*/

#include "../include/GlitchManager.hpp"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <string>

GlitchManager::GlitchManager() : _isSoundEnabled(true), _isLagMode(false), _isInvisibleMode(false)
{
}

GlitchManager::~GlitchManager()
{
}

void GlitchManager::setSoundEnabled(bool enabled)
{
    _isSoundEnabled = enabled;
}

sf::Color GlitchManager::getGlitchColor()
{
    return sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 50 + 200);
}

void GlitchManager::applyBrush(sf::RenderTexture &canvas, sf::Vector2i pos, bool isEraser)
{
    if (_isLagMode) {
        _delayedStrokes.push_back({pos, isEraser, _chaosClock.getElapsedTime()});
        return;
    }

    if (_isInvisibleMode) {
        return;
    }

    int offsetX = (rand() % 30) - 15;
    int offsetY = (rand() % 30) - 15;

    // Logique de taille de pinceau complètement cassée et aléatoire
    int w = (rand() % 200) + 4;
    int h = (rand() % 200) + 4;
    
    // Division par un nombre random pour varier les ratios
    float divW = ((rand() + 1) % 10) + 1;
    float divH = ((rand() + 1) % 10) + 1;

    sf::RectangleShape brush(sf::Vector2f(w / divW, h / divH));
    brush.setPosition(pos.x + offsetX, pos.y + offsetY);
    
    if (isEraser) {
        brush.setFillColor(sf::Color::Black);
    } else {
        brush.setFillColor(getGlitchColor());
    }
    
    canvas.draw(brush);
}

void GlitchManager::triggerRandomEvents(sf::RenderTexture &canvas, const AssetManager &assets)
{
    // Nettoyage des sons terminés
    _activeSounds.remove_if([](const sf::Sound &s) {
        return s.getStatus() == sf::Sound::Stopped;
    });

    // MEMES : 1 chance sur 250 (toutes les ~4 sec)
    if (rand() % 250 == 0) {
        pasteRandomImage(canvas, assets);
    }
    
    // MEMORY LEAK : 1 chance sur 2000 (toutes les ~33 sec)
    if (rand() % 2000 == 0) {
        leakMemory();
    }

    // SON : 1 chance sur 2000 (toutes les ~33 sec)
    if (rand() % 2000 == 0) {
        playRandomSound(assets);
    }

    // NOTIFICATIONS SYSTEME : 1 chance sur 1500 (toutes les ~25 sec)
    if (rand() % 1500 == 0) {
        triggerFakeNotification();
    }

    // FREEZE : Fixe toutes les 30 sec
    if (_freezeTimer.getElapsedTime().asSeconds() >= 30.0f) {
        std::cout << "[System] Running scheduled background optimization..." << std::endl;
        
        if (rand() % 2 == 1) {
            sf::sleep(sf::milliseconds(50));
            std::cout << "[System] CPU Lag Spike detected (50ms)" << std::endl;
        } else {
            std::cout << "[System] Optimization complete." << std::endl;
        }
        
        _freezeTimer.restart();
    }

    // Gestion des modes chaotiques (Lag / Invisible)
    updateChaosModes();
    processDelayedStrokes(canvas);
}

void GlitchManager::updateChaosModes()
{
    // Si aucun mode n'est actif, petite chance d'en activer un
    if (!_isLagMode && !_isInvisibleMode) {
        if (rand() % 1000 == 0) { // ~Toutes les 16 secondes
            _isLagMode = true;
            _modeDuration = sf::seconds((rand() % 5) + 2); // 2 à 7 sec
            _chaosClock.restart();
            std::cout << "[Chaos] Lag Mode Activated!" << std::endl;
        } else if (rand() % 2000 == 0) { // ~Toutes les 33 secondes
            _isInvisibleMode = true;
            _modeDuration = sf::seconds((rand() % 3) + 2); // 2 à 5 sec
            _chaosClock.restart();
            std::cout << "[Chaos] Invisible Mode Activated!" << std::endl;
        }
    } else {
        // Si un mode est actif, on vérifie s'il doit s'arrêter
        if (_chaosClock.getElapsedTime() > _modeDuration) {
            _isLagMode = false;
            _isInvisibleMode = false;
            std::cout << "[Chaos] Mode Deactivated." << std::endl;
        }
    }
}

void GlitchManager::processDelayedStrokes(sf::RenderTexture &canvas)
{
    if (_delayedStrokes.empty()) return;

    sf::Time now = _chaosClock.getElapsedTime();
    sf::Time delay = sf::milliseconds(500); // 500ms de lag

    while (!_delayedStrokes.empty()) {
        const auto& stroke = _delayedStrokes.front();
        if (now - stroke.timestamp > delay) {
            // On dessine le trait différé
            int offsetX = (rand() % 30) - 15;
            int offsetY = (rand() % 30) - 15;
            int w = (rand() % 200) + 4;
            int h = (rand() % 200) + 4;
            float divW = ((rand() + 1) % 10) + 1;
            float divH = ((rand() + 1) % 10) + 1;

            sf::RectangleShape brush(sf::Vector2f(w / divW, h / divH));
            brush.setPosition(stroke.pos.x + offsetX, stroke.pos.y + offsetY);
            
            if (stroke.isEraser) {
                brush.setFillColor(sf::Color::Black);
            } else {
                brush.setFillColor(getGlitchColor());
            }
            canvas.draw(brush);

            _delayedStrokes.pop_front();
        } else {
            break; // Les suivants sont trop récents
        }
    }
}

void GlitchManager::triggerFakeNotification()
{
    const char* messages[] = {
        "CRITICAL: Battery at -67%. CHARGE IMMEDIATELY!",
        "System Update: Restarting in 5 seconds...",
        "SECURITY ALERT: All your DATA has been leaked to hackers.",
        "WARNING: Battery Temperature at -854 C.",
        "The weather is nice outside."
    };

    int index = rand() % 5;
    
    // On ajoute '&' à la fin pour lancer zenity en arrière-plan et ne pas bloquer le programme
    std::string cmd = "zenity --notification --text=\"" + std::string(messages[index]) + "\" 2>/dev/null &";
    
    system(cmd.c_str());
    std::cout << "[System] Fake notification triggered: " << messages[index] << std::endl;
}

void GlitchManager::pasteRandomImage(sf::RenderTexture &canvas, const AssetManager &assets)
{
    sf::Sprite sprite;
    sprite.setTexture(assets.getRandomMeme());

    float x = rand() % canvas.getSize().x;
    float y = rand() % canvas.getSize().y;
    float scale = (float)(rand() % 13 + 2) / 10.0f;

    sprite.setPosition(x, y);
    sprite.setScale(scale, scale);
    sprite.setRotation(rand() % 360);

    canvas.draw(sprite);
    std::cout << "[Feature] A wild meme appeared!" << std::endl;
}

void GlitchManager::playRandomSound(const AssetManager &assets)
{
    if (!_isSoundEnabled)
        return;

    _activeSounds.emplace_back();
    sf::Sound &sound = _activeSounds.back();

    sound.setBuffer(assets.getRandomSoundBuffer());
    
    float pitch = (rand() % 40 + 80) / 100.0f;
    sound.setPitch(pitch);
    
    sound.play();

    std::cout << "[Audio] Playing random sound effect (Pitch: " << pitch << ")" << std::endl;
}

void GlitchManager::leakMemory()
{
    size_t size = (rand() % 502 + 10) * 1024 * 1024;
    try {
        void* ptr = std::malloc(size);
        if (ptr) {
            std::memset(ptr, 1, size); 
            _uselessMemory.push_back(ptr);
            std::cout << "[System] " << (size / 1024 / 1024) << "MB allocated successfully for no reason." << std::endl;
        }
    } catch (...) {
        std::cout << "[System] Failed to allocate memory (RAM is full ? Good.)" << std::endl;
    }
}

void GlitchManager::saveAndCorrupt(const sf::RenderTexture &canvas)
{
    if (!std::filesystem::exists("save"))
        std::filesystem::create_directory("save");

    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << "drawing_" << std::put_time(&tm, "%m_%d_%Y_%H_%M_%S") << ".png";
    std::string defaultName = oss.str();

    std::filesystem::path fullPath = std::filesystem::absolute("save") / defaultName;

    std::string cmd = "zenity --file-selection --save --confirm-overwrite --filename=\"" + fullPath.string() + "\" 2>/dev/null";
    
    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe)
        return;

    char buffer[1024];
    std::string result = "";
    if (fgets(buffer, 1024, pipe) != NULL) {
        result = buffer;
    }
    pclose(pipe);

    if (!result.empty() && result.back() == '\n')
        result.pop_back();

    if (result.empty())
        return;

    if (result.find(".png") == std::string::npos)
        result += ".png";

    sf::Image screenshot = canvas.getTexture().copyToImage();
    if (!screenshot.saveToFile(result))
        return;
    
    std::fstream file(result, std::ios::in | std::ios::out | std::ios::binary);
    if (file.is_open()) {
        file.seekp(0);
        char garbage[] = "NOT_A_PNG"; 
        file.write(garbage, sizeof(garbage));

        file.seekg(0, std::ios::end);
        long fileSize = file.tellg();
        
        for (int i = 0; i < 50; i++) {
            long pos = rand() % fileSize;
            file.seekp(pos);
            char byte = rand() % 255;
            file.write(&byte, 1);
        }
        file.close();
    }
}
