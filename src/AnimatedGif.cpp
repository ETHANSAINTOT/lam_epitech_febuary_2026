#include "AnimatedGif.hpp"
#include <iostream>

AnimatedGif::AnimatedGif() : currentFrame(0), loaded(false)
{}

ColorMapObject* AnimatedGif::getColorMap(const SavedImage& image, GifFileType* gif) const
{
    return image.ImageDesc.ColorMap ? image.ImageDesc.ColorMap : gif->SColorMap;
}

AnimatedGif::FrameInfo AnimatedGif::extractFrameInfo(const SavedImage& image) const
{
    FrameInfo info = {-1, 10};
    
    for (int j = 0; j < image.ExtensionBlockCount; ++j) {
        if (image.ExtensionBlocks[j].Function == GRAPHICS_EXT_FUNC_CODE) {
            unsigned char* bytes = (unsigned char*)image.ExtensionBlocks[j].Bytes;
            unsigned char flags = bytes[0];
            info.delay = bytes[1] | (bytes[2] << 8);
            
            if (flags & 0x01) {
                info.transparentIndex = bytes[3];
            }
            break;
        }
    }
    
    return info;
}

bool AnimatedGif::isPixelValid(int x, int y, int index, const SavedImage& image, GifFileType* gif, const ColorMapObject* colorMap, int transparentIndex) const
{
    if (index >= colorMap->ColorCount) return false;
    if (image.ImageDesc.Left + x >= gif->SWidth) return false;
    if (image.ImageDesc.Top + y >= gif->SHeight) return false;
    if (index == transparentIndex) return false;
    
    return true;
}

sf::Image AnimatedGif::createFrameImage(const SavedImage& image, GifFileType* gif, const ColorMapObject* colorMap, int transparentIndex) const
{
    sf::Image sfImage;
    sfImage.create(gif->SWidth, gif->SHeight, sf::Color::Transparent);
    
    for (int y = 0; y < image.ImageDesc.Height; ++y) {
        for (int x = 0; x < image.ImageDesc.Width; ++x) {
            int index = image.RasterBits[y * image.ImageDesc.Width + x];
            
            if (!isPixelValid(x, y, index, image, gif, colorMap, transparentIndex)) {
                continue;
            }
            
            GifColorType& color = colorMap->Colors[index];
            sfImage.setPixel(
                image.ImageDesc.Left + x,
                image.ImageDesc.Top + y,
                sf::Color(color.Red, color.Green, color.Blue)
            );
        }
    }
    
    return sfImage;
}

bool AnimatedGif::loadFromFile(const std::string& filename)
{
    frames.clear();
    delays.clear();
    currentFrame = 0;
    loaded = false;
    int error;
    GifFileType* gif = DGifOpenFileName(filename.c_str(), &error);
    if (!gif) {
        std::cerr << "File dosent exist: " << GifErrorString(error) << std::endl;
        return false;
    }
    if (DGifSlurp(gif) == GIF_ERROR) {
        std::cerr << "Invalid file: " << GifErrorString(gif->Error) << std::endl;
        DGifCloseFile(gif, &error);
        return false;
    }
    if (gif->ImageCount == 0) {
        std::cerr << "Empty gif" << std::endl;
        DGifCloseFile(gif, &error);
        return false;
    }
    for (int i = 0; i < gif->ImageCount; ++i) {
        SavedImage& image = gif->SavedImages[i];
        ColorMapObject* colorMap = getColorMap(image, gif);
        if (!colorMap) {
            std::cerr << "No palette found" << std::endl;
            continue;
        }
        FrameInfo info = extractFrameInfo(image);
        sf::Image sfImage = createFrameImage(image, gif, colorMap, info.transparentIndex);
        sf::Texture texture;
        if (!texture.loadFromImage(sfImage)) {
            std::cerr << "Memory error ?" << std::endl;
            continue;
        }
        frames.push_back(texture);
        delays.push_back(info.delay == 0 ? 100 : info.delay * 10);
    }
    DGifCloseFile(gif, &error);
    if (frames.empty()) {
        std::cerr << "No frame found" << std::endl;
        return false;
    }
    currentFrame = 0;
    loaded = true;
    clock.restart();
    std::cout << "GIF Loaded: " << filename << std::endl;
    return true;
}

void AnimatedGif::update()
{
    if (!loaded || frames.empty())
        return;
    if (currentFrame >= frames.size()) {
        currentFrame = 0;
    }
    if (clock.getElapsedTime().asMilliseconds() >= delays[currentFrame]) {
        currentFrame = (currentFrame + 1) % frames.size();
        clock.restart();
    }
}

const sf::Texture& AnimatedGif::getCurrentTexture() const
{
    if (!loaded || frames.empty()) {
        static sf::Texture emptyTexture;
        return emptyTexture;
    }
    if (currentFrame >= frames.size()) {
        return frames[0];
    }
    return frames[currentFrame];
}

bool AnimatedGif::isLoaded() const
{
    return loaded && !frames.empty();
}

size_t AnimatedGif::getFrameCount() const
{
    return frames.size();
}

sf::Vector2u AnimatedGif::getSize() const
{
    if (frames.empty()) return sf::Vector2u(0, 0);
    return frames[0].getSize();
}