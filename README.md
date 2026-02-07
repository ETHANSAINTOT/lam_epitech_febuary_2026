[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/epitech/SafePaint)
[![Platform](https://img.shields.io/badge/platform-linux-lightgrey.svg)](https://www.kernel.org/)
[![C++](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![SFML](https://img.shields.io/badge/SFML-2.6.1-green.svg)](https://www.sfml-dev.org/)

# 🎨 SafePaint

**SafePaint** is an experimental drawing application designed to challenge the user's patience. Unlike traditional tools that prioritize stability and precision, SafePaint embraces chaos, memory leaks, and unpredictable behavior as core design principles.

> **"It's not a bug, it's a feature."**

---

## 🇬🇧 English Documentation

### 📋 System Requirements

The project is strictly built for **Linux** environments using standard C++ tools.

| Component | Requirement | Version |
|:----------:|:-----------------:|:-----------:|
| **OS** | Linux | Ubuntu/Fedora/Arch |
| **Language** | C++ | Standard 20 (C++20) |
| **Compiler** | clang++ | Latest Stable |
| **Graphics** | SFML | 2.6.1 |
| **Build System** | Makefile | GNU Make |
| **UI Tools** | Zenity | Standard (Required for save dialogs & notifications) |

### 🛠️ Build & Run

Use the provided `Makefile` to manage the project compilation.

| Command | Description |
|:-------:|:-----------:|
| `make` | Compiles the source code and generates the `./SafePaint` binary. |
| `./SafePaint` | Launches the application. Use `--no-sound` to disable audio. |
| `make clean` | Removes object files (`.o`) to clean up the directory. |
| `make fclean` | Removes object files and the binary executable. |
| `make re` | Forces a full recompilation of the project. |

### ✨ Features & Probabilities

SafePaint includes several "advanced" features designed to disrupt your workflow, occurring at specific intervals:

* **Unstable & Morphing Brush:** The cursor position is intentionally offset, and **the brush size and aspect ratio mutate randomly** with every stroke. Drawing a consistent line is statistically impossible.
* **Fake System Notifications:** The app triggers native OS notifications (GNOME/KDE via Zenity) claiming your battery is at **-67%**, your data has been leaked, or your hardware temperature is **-854°C**. Occurs approximately **every 25 seconds** (1/1500 chance per frame).
* **Unreliable Eraser:** Works exactly like the brush (with the same random offset and size logic), but paints in black.
* **Corrupted Save System:** The app opens a native file explorer (Zenity) to let you choose a save location. It then saves the image, rewrites the file header to `NOT_A_PNG`, and corrupts random bytes to ensure the file is unreadable.
* **Placebo Color Palette:** A fully interactive color bar. Clicking a color confirms the selection with a notification, but the brush continues to paint in random colors.
* **Intrusive Memes:** Random images appear on your canvas approximately **every 4 seconds** (1/250 chance per frame).
* **Dynamic Memory Leaks:** Approximately **every 33 seconds** (1/2000 chance per frame), the application allocates large chunks of RAM (up to 512MB) to "warm up" your system.
* **Random Audio Events:** Random sound effects play approximately **every 33 seconds** (1/2000 chance per frame). Can be disabled via the `--no-sound` flag.
* **Scheduled Lag Spikes:** Every **30 seconds** (fixed timer), a background optimization task runs. It has a 50% chance of freezing the application for 50ms to simulate realistic CPU struggle.
* **TTY Troll Mode:** If launched without a display server (TTY), the app displays ASCII art and exits with error code **67**.

---

## 🇫🇷 Documentation Française

### 📋 Prérequis Système

Le projet est conçu exclusivement pour les environnements **Linux**.

| Composant | Requis | Version |
|:----------:|:-----------------:|:-----------:|
| **OS** | Linux | Ubuntu/Fedora/Arch |
| **Langage** | C++ | Standard 20 (C++20) |
| **Compilateur** | clang++ | Dernière version stable |
| **Graphismes** | SFML | 2.6.1 |
| **Build** | Makefile | GNU Make |
| **Outils UI** | Zenity | Standard (Requis pour la sauvegarde & notifications) |

### 🛠️ Compilation et Exécution

Utilisez le `Makefile` fourni pour gérer la compilation.

| Commande | Description |
|:-------:|:-----------:|
| `make` | Compile le code source et génère le binaire `./SafePaint`. |
| `./SafePaint` | Lance l'application. Utilisez `--no-sound` pour couper le son. |
| `make clean` | Supprime les fichiers objets (`.o`) pour nettoyer le dossier. |
| `make fclean` | Supprime les fichiers objets et l'exécutable. |
| `make re` | Force une recompilation complète du projet. |

### ✨ Fonctionnalités et Probabilités

SafePaint inclut plusieurs fonctionnalités "avancées", réglées sur des fréquences précises :

* **Pinceau Instable et Mutant :** Le curseur est décalé, mais surtout, **la taille et le ratio du pinceau changent aléatoirement** à chaque trait. Tracer une ligne cohérente est impossible.
* **Fausses Notifications Système :** L'application déclenche des notifications natives (GNOME/KDE via Zenity) prétendant que votre batterie est à **-67%**, que vos données ont fuité ou que la température est à **-854°C**. Environ **toutes les 25 secondes** (1 chance sur 1500 par frame).
* **Gomme Instable :** Fonctionne exactement comme le pinceau (taille aléatoire), mais peint en noir.
* **Sauvegarde Corrompue :** L'application ouvre un explorateur de fichiers (Zenity). Elle sauvegarde ensuite l'image, réécrit l'en-tête du fichier en `NOT_A_PNG` et corrompt des octets au hasard pour rendre le fichier illisible.
* **Palette Placebo :** Une barre de couleur interactive. Cliquer sur une couleur confirme la sélection, mais le pinceau continue de peindre avec des couleurs aléatoires.
* **Mèmes Intrusifs :** Des images aléatoires apparaissent sur votre toile environ **toutes les 4 secondes** (1 chance sur 250 par frame).
* **Fuites de Mémoire :** Environ **toutes les 33 secondes** (1 chance sur 2000 par frame), l'application alloue de gros blocs de RAM (jusqu'à 512 Mo).
* **Événements Sonores :** Des sons aléatoires sont joués environ **toutes les 33 secondes** (1 chance sur 2000 par frame). Désactivable avec `--no-sound`.
* **Lags Programmés :** Toutes les **30 secondes** (fixe), une tâche de fond se lance avec 50% de chance de geler l'application pendant 50ms.
* **Mode Troll TTY :** Si lancé sans serveur d'affichage (TTY), l'application affiche un ASCII art et quitte avec le code d'erreur **67**.