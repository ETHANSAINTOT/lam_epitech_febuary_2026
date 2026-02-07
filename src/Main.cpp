/*
** EPITECH PROJECT, 2026
** JAM #1
** File description:
** src/Main.cpp
*/

#include "../include/SafePaint.hpp"
#include <cstring>
#include <iostream>

static void print_help(const char *binary_name)
{
    std::cout << "USAGE: " << binary_name << " [OPTIONS]" << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << "\t--no-sound\tDisable sound effects" << std::endl;
    std::cout << "\t-h, --help\tDisplay this help" << std::endl;
}

int main(int argc, char **argv)
{
    bool soundEnabled = true;

    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "-h") == 0 || std::strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        }
        if (std::strcmp(argv[i], "--no-sound") == 0) {
            soundEnabled = false;
        }
    }

    if (soundEnabled) {
        std::cout << "🔊 Pensez a porter un casque, les sons sont activés." << std::endl;
    }

    SafePaint app(soundEnabled);
    app.run();
    return 0;
}