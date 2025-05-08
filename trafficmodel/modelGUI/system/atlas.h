#pragma once
#include "config.h"
#include "stb/stb_image.h"

class Atlas {
    public:
        GLuint texture;
        float tileSize;
        int textWidth, textHeight, textChannels;
        unsigned int uvMinLocation, uvMaxLocation, atlasLocation, colorLocation;
        Atlas(const std::string& textureFile, unsigned int shader, float tileSize);
        ~Atlas();
};