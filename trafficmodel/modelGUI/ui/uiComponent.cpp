#include "uiComponent.h"
#include "textureConstants.h"

UIComponent::UIComponent(
    Atlas* atlas,
    GLFWwindow* window,
    UIComponent* parent,
    ComponentState* state,
    ComponentConstraint* sizeConstraint,
    ComponentConstraint* positionContraint
) : 
atlas(atlas),
window(window),
parent(parent),
state(state),
sizeConstraint(sizeConstraint),
positionContraint(positionContraint)
{};

UIComponent::~UIComponent() {
    delete state;
    delete sizeConstraint;
    delete positionContraint;
};

void UIComponent::Init() {
    state->setParent(this);
    sizeConstraint->setParent(this);
    positionContraint->setParent(this);
};

void UIComponent::update() {
    size = sizeConstraint->getElement();
    position = positionContraint->getElement();
    state->update();
};

void UIComponent::updateAndDraw() {
    update();
    draw();
}

void UIComponent::bindVAO() {
    std::vector<float> vertices = getVertices();
    std::vector<int> indicies = {0, 1, 2, 1, 3, 2};

    //position
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //element buffer
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(int), indicies.data(), GL_STATIC_DRAW);
};

std::vector<float> UIComponent::getVertices() {
    return {
        position.x, position.y, (float)TextId::UI, 0.f, 1.f,
        position.x, position.y + size.y, (float)TextId::UI, 0.f, 0.f,
        position.x + size.x, position.y, (float)TextId::UI, 1.f, 1.f,
        position.x + size.x, position.y + size.y, (float)TextId::UI, 1.f, 0.f
    };
};

std::vector<float> UIComponent::getUVMinMax() {
    int blocksPerRow = atlas->textWidth / atlas->tileSize;
    int row = texture / blocksPerRow;
    int col = texture % blocksPerRow;

    float uStep = atlas->tileSize / (float)atlas->textWidth;
    float vStep = atlas->tileSize / (float)atlas->textHeight;

    return std::vector<float>{
        col * uStep, (1 - (row * vStep)) - vStep,
        (col * uStep) + uStep, (1 - (row * vStep))
    };
};

void UIComponent::draw() {
    /*
        Note that when the UI draw is called we expect the renderer 
        to have set the view matrix to the I and the projection matrix 
        to "glm::mat4 ortho = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight)" 
        to put us into screen space. 
    */

    std::vector<float> uvs = getUVMinMax();

    bindVAO();
    glBindVertexArray(VAO);
    glUniform2f(atlas->uvMinLocation, uvs[0], uvs[1]);
    glUniform2f(atlas->uvMaxLocation, uvs[0], uvs[1]);
    glUniform4fv(atlas->colorLocation, 1, glm::value_ptr(color));
    glDrawElements(GL_TRIANGLES, ELEM_COUNT, GL_UNSIGNED_INT, 0);
};

void UIComponent::setTexture(int texture_) { texture = texture_; };
void UIComponent::setParent(UIComponent* parent_) { parent = parent_; };
void UIComponent::setWindow(GLFWwindow* window_) { window = window_; };
void UIComponent::setPosition(glm::vec2 position_) { position = position_; };
void UIComponent::setSize(glm::vec2 size_) { size = size_; };
void UIComponent::setColor(glm::vec4 color_) { color = color_; };

int UIComponent::getTexture() { return texture; };
UIComponent* UIComponent::getParent() { return parent; };
GLFWwindow* UIComponent::getWindow() { return window; };
glm::vec2 UIComponent::getPosition() { return position; };
glm::vec2 UIComponent::getSize() { return size; };
glm::vec4 UIComponent::getColor() { return color; };