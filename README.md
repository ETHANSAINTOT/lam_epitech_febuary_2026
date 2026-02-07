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
| **UI Tools** | Zenity | Standard (Required for save dialogs) |

### 🛠️ Build & Run

Use the provided `Makefile` to manage the project compilation.

| Command | Description |
|:-------:|:-----------:|
| `make` | Compiles the source code and generates the `./SafePaint` binary. |
| `./SafePaint` | Launches the application. |
| `make clean` | Removes object files (`.o`) to clean up the directory. |
| `make fclean` | Removes object files and the binary executable. |
| `make re` | Forces a full recompilation of the project. |

### ✨ Features

SafePaint includes several "advanced" features designed to disrupt your workflow:

* **Desynchronized Brush:** The drawing cursor and the actual paint position are intentionally offset by a random vector every time you click. Precision is statistically impossible.
* **Unreliable Eraser:** Works exactly like the brush (with the same random offset logic), but paints in black.
* **Corrupted Save System:** The app opens a native file explorer (Zenity) to let you choose a save location. It then saves the image, rewrites the file header to `NOT_A_PNG`, and corrupts random bytes to ensure the file is unreadable.
* **Placebo Color Palette:** A fully interactive color bar. Clicking a color confirms the selection with a notification, but the brush continues to paint in random colors.
* **Dynamic Memory Leaks:** The application randomly allocates large chunks of RAM (up to 512MB at a time) to "warm up" your system.
* **Intrusive Memes:** Random images (memes) will appear on your canvas without your consent during the drawing process.
* **Scheduled Lag Spikes:** Every 30 seconds, a background optimization task runs. It has a 50% chance of freezing the application for 50ms to simulate realistic CPU struggle.
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
| **Outils UI** | Zenity | Standard (Requis pour la sauvegarde) |

### 🛠️ Compilation et Exécution

Utilisez le `Makefile` fourni pour gérer la compilation.

| Commande | Description |
|:-------:|:-----------:|
| `make` | Compile le code source et génère le binaire `./SafePaint`. |
| `./SafePaint` | Lance l'application. |
| `make clean` | Supprime les fichiers objets (`.o`) pour nettoyer le dossier. |
| `make fclean` | Supprime les fichiers objets et l'exécutable. |
| `make re` | Force une recompilation complète du projet. |

### ✨ Fonctionnalités

SafePaint inclut plusieurs fonctionnalités "avancées" :

* **Pinceau Désynchronisé :** Le curseur de la souris et la position réelle du dessin sont intentionnellement décalés par un vecteur aléatoire à chaque clic.
* **Gomme Instable :** Fonctionne exactement comme le pinceau, mais peint en noir.
* **Sauvegarde Corrompue :** L'application ouvre un explorateur de fichiers (Zenity). Elle sauvegarde ensuite l'image, réécrit l'en-tête du fichier en `NOT_A_PNG` et corrompt des octets au hasard pour rendre le fichier illisible.
* **Palette Placebo :** Une barre de couleur interactive. Cliquer sur une couleur confirme la sélection, mais le pinceau continue de peindre avec des couleurs aléatoires.
* **Fuites de Mémoire :** L'application alloue aléatoirement de gros blocs de RAM (jusqu'à 512 Mo à la fois).
* **Mèmes Intrusifs :** Des images aléatoires (mèmes) apparaîtront sur votre toile sans votre consentement.
* **Lags Programmés :** Toutes les 30 secondes, une tâche de fond se lance avec 50% de chance de geler l'application pendant 50ms.
* **Mode Troll TTY :** Si lancé sans serveur d'affichage (TTY), l'application affiche un ASCII art et quitte avec le code d'erreur **67**.