#include "atlas.h"


Atlas::Atlas(
    const std::string& textureFile, 
    unsigned int shader, float tileSize
) : tileSize(tileSize) {
    uvMinLocation = glGetUniformLocation(shader, "uvMin");
    uvMaxLocation = glGetUniformLocation(shader, "uvMax");
    atlasLocation = glGetUniformLocation(shader, "atlas");
    colorLocation = glGetUniformLocation(shader, "color");

    stbi_set_flip_vertically_on_load(1);
    unsigned char* textureImg = stbi_load(
        textureFile.c_str(), 
        &textWidth, &textHeight, &textChannels, 0
    );

    if (!textureImg) {
        printf("Can't load texture -- %s\n", stbi_failure_reason());
        exit(0);
    };
    
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(atlasLocation, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textWidth, textHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImg);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureImg);
};

Atlas::~Atlas() { glDeleteTextures(1, &texture); };
