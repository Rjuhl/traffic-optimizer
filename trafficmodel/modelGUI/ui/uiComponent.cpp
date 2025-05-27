#include "uiComponent.h"
#include "textureConstants.h"
#include "guiHelpers.h"

UIComponent::UIComponent(
    int texture,
    float level,
    uint32_t parent,
    glm::vec4 color,
    ComponentState* state,
    ComponentConstraint* sizeConstraint,
    ComponentConstraint* positionConstraint
) :
    texture(texture),
    level(level),
    parent(parent),
    color(color),
    state(state),
    sizeConstraint(sizeConstraint),
    positionConstraint(positionConstraint)
{ state->setParent(this); };

UIComponent::~UIComponent() {
    delete state;
    delete sizeConstraint;
    delete positionConstraint;
};


void UIComponent::update(
    const glm::vec2& mouse,
    const glm::vec2& parentSize,
    const glm::vec2& parentPostition
) {
    size = sizeConstraint->getElement(parentSize);
    position = positionConstraint->getElement(parentPostition);
    state->update(mouse);
};

std::vector<float> UIComponent::getVertices() {
    return {
        position.x, position.y, level, 0.f, 1.f,
        position.x, position.y - size.y, level, 0.f, 0.f,
        position.x + size.x, position.y, level, 1.f, 1.f,
        position.x + size.x, position.y - size.y, level, 1.f, 0.f
    };
};

void UIComponent::setTexture(int texture_) { texture = texture_; };
void UIComponent::setSize(glm::vec2 size_) { size = size_; };
void UIComponent::setPosition(glm::vec2 position_) { position = position_; };
void UIComponent::setColor(glm::vec4 color_) { color = color_; };

int UIComponent::getTexture() { return texture; };
uint32_t UIComponent::getParent() { return parent; };
glm::vec2 UIComponent::getSize() { return size; };
glm::vec2 UIComponent::getPosition() {return position; };
glm::vec4 UIComponent::getColor() { return color; };


// void UIComponent::bindVAO() {
//     std::vector<float> vertices = getVertices();
//     std::vector<int> indicies = {0, 1, 2, 1, 3, 2};

//     guiHelpers.printfVector(vertices);

//     //position
//     glGenBuffers(1, &VBO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//     glEnableVertexAttribArray(1);

//     //element buffer
//     glGenBuffers(1, &EBO);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(int), indicies.data(), GL_STATIC_DRAW);
// };

// std::vector<float> UIComponent::getVertices() {

//     // return {
//     //     50, 50, (float)TextId::UI, 1.f, 0.f,
//     //     50, 0, (float)TextId::UI, 1.f, 1.f,
//     //     0, 50, (float)TextId::UI, 0.f, 0.f,
//     //     0, 0, (float)TextId::UI, 0.f, 1.f
//     // };

//     std::cout << size.x << ", " << size.y << std::endl << position.x << ", " << position.y << std::endl << std::endl; 

//     return {
//         position.x, position.y, (float)TextId::UI, 1.f, 0.f,
//         position.x, position.y + size.y, (float)TextId::UI, 1.f, 1.f,
//         position.x + size.x, position.y, (float)TextId::UI, 0.f, 0.f,
//         position.x + size.x, position.y + size.y, (float)TextId::UI, 0.f, 1.f
//     };
// };

// std::vector<float> UIComponent::getUVMinMax() {
//     int blocksPerRow = atlas->textWidth / atlas->tileSize;
//     int row = texture / blocksPerRow;
//     int col = texture % blocksPerRow;

//     float uStep = atlas->tileSize / (float)atlas->textWidth;
//     float vStep = atlas->tileSize / (float)atlas->textHeight;

//     return std::vector<float>{
//         col * uStep, (1 - (row * vStep)) - vStep,
//         (col * uStep) + uStep, (1 - (row * vStep))
//     };
// };
