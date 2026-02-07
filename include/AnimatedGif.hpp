#ifndef ANIMATEDGIF_HPP
    #define ANIMATEDGIF_HPP

    #include <SFML/Graphics.hpp>
    #include <vector>
    #include <string>
    #include <gif_lib.h>

    class AnimatedGif {
        public:
            AnimatedGif();
            bool loadFromFile(const std::string& filename);
            void update();
            const sf::Texture& getCurrentTexture() const;
            bool isLoaded() const;
            size_t getFrameCount() const;
            sf::Vector2u getSize() const;
        private:
            std::vector<sf::Texture> frames;
            std::vector<int> delays;
            size_t currentFrame;
            sf::Clock clock;
            bool loaded;
            struct FrameInfo {
                int transparentIndex;
                int delay;
            };
            ColorMapObject* getColorMap(const SavedImage& image, GifFileType* gif) const;
            FrameInfo extractFrameInfo(const SavedImage& image) const;
            sf::Image createFrameImage(const SavedImage& image, GifFileType* gif, const ColorMapObject* colorMap, int transparentIndex) const;
            bool isPixelValid(int x, int y, int index, const SavedImage& image, GifFileType* gif, const ColorMapObject* colorMap, int transparentIndex) const;
    };

#endif