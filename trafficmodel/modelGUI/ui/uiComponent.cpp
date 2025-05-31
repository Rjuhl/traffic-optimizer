#include "uiComponent.h"
#include "textureConstants.h"
#include "guiHelpers.h"

UIComponent::UIComponent(
    int texture,
    float level,
    uint32_t parent,
    glm::vec4 color,
    std::shared_ptr<ComponentState> state,
    std::shared_ptr<ComponentConstraint> sizeConstraint,
    std::shared_ptr<ComponentConstraint> positionConstraint
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
};


void UIComponent::update(
    const glm::vec2& mouse,
    const glm::vec2& parentSize,
    const glm::vec2& parentPostition
) {
    size = sizeConstraint->getElement(parentSize);
    position = positionConstraint->getElement(parentPostition);
    // state->update(mouse);
    // std::cout << "State updated" << std::endl;
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

int UIComponent::getLevel() { return level; };
int UIComponent::getTexture() { return texture; };
uint32_t UIComponent::getParent() { return parent; };
glm::vec2 UIComponent::getSize() { return size; };
glm::vec2 UIComponent::getPosition() {return position; };
glm::vec4 UIComponent::getColor() { return color; };

