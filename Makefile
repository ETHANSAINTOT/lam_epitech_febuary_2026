##
## EPITECH PROJECT, 2026
## JAM #1
## File description:
## Makefile
##

CXX = clang++

NAME = SafePaint

CXX_FLAGS = -Iinclude -Wall -Wextra -Werror -std=c++20 -g

SFML_FLAGS = -lgif -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio

SRC = src/Main.cpp \
      src/SafePaint.cpp \
      src/TrollRenderer.cpp \
      src/AssetManager.cpp \
      src/GlitchManager.cpp \
      src/UIManager.cpp \
      src/AnimatedGif.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(SFML_FLAGS)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
