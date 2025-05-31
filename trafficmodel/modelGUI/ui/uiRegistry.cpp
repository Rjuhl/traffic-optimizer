#include "uiRegistry.h"
#include "guiHelpers.h"

UIRegistry::UIRegistry(Atlas* atlas, Camera* camera)
: atlas(atlas), camera(camera),
UV_MIN(atlas->uvMinLocation),
UV_MAX(atlas->uvMaxLocation),
COLOR(atlas->colorLocation)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, MAX_VERTEX_COUNT * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    // Attribute layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Index buffer
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}; 

UIRegistry::~UIRegistry() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
};


glm::vec2 UIRegistry::getWindowSize() {
    return camera->getScreenSize();
};

glm::vec2 UIRegistry::getMouse() {
    double mx, my;
    glfwGetCursorPos(camera->getWindow(), &mx, &my);
    return glm::vec2((2.f * mx) / getWindowSize().x - 1.f, 1.f - (2.f * my) / getWindowSize().y);
};

glm::mat4 UIRegistry::getTransform() {
    guiHelpers.printMat4(camera->getScreenSpace());
    guiHelpers.printMat4(glm::inverse(camera->getScreenSpace()));
    guiHelpers.printMat4(camera->getScreenSpace() * glm::inverse(camera->getScreenSpace()));
    return glm::inverse(camera->getScreenSpace());
};

glm::vec3 UIRegistry::transformPoint(const glm::mat4& transform, const glm::vec3 point) {
    return glm::vec3(transform * glm::vec4(point, 1.f));
};

std::vector<float> UIRegistry::getUVMinMax(int texture) {
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

void UIRegistry::removeUIComponent(uint32_t id) { components.remove(id); };
uint32_t UIRegistry::addUIComponent(
    int texture, 
    uint32_t parent,
    glm::vec4 color,
    std::shared_ptr<ComponentState> state,
    std::shared_ptr<ComponentConstraint> sizeConstraint,
    std::shared_ptr<ComponentConstraint> positionConstraint
) {
    float level = TextId::UI;
    if (parent != 0) level = components.get(parent)->getLevel() + 1;
    return components.add(
        UIComponent(
            texture, level, parent, color,
            state, sizeConstraint, positionConstraint
        ), parent
    );
};

void UIRegistry::sendVerticiesToGPU(const std::vector<float>& vertices) {
    guiHelpers.printfVector(vertices);
    
    // Send data
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());

    // Draw it
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
};

void UIRegistry::transformVertices(std::vector<float>& vertices, const glm::mat4& transform) {
    for (int i = 0; i < vertices.size(); i += 5) {
        glm::vec3 transformed = glm::vec3(
            transform * glm::vec4(vertices[i], vertices[i + 1], vertices[i + 2], 1.f)
        );
        vertices[i] = transformed.x;
        vertices[i + 1] = transformed.y;
    }
}

void UIRegistry::drawUI() {
    const glm::mat4& transform = getTransform();
    const glm::vec2& windowSize = getWindowSize();
    const glm::vec2& mouse = getMouse();

    std::vector<ParentInfo> parents;
    parents.reserve(components.getItems().size() + 1);
    parents.emplace_back(0, glm::vec2(2.f, 2.f), glm::vec2(-1.f, 1.f));

    for (auto& elem : components.getItems()) {
        uint32_t id = elem.id;
        UIComponent comp = elem.value;

        while (parents.size() > 1 && parents.back() != id) parents.pop_back();
        ParentInfo parent = parents.back();

        comp.update(mouse, parent.size, parent.position);

        std::vector<float> vertices = comp.getVertices();
        const std::vector<float>& uv = getUVMinMax(comp.getTexture());
        transformVertices(vertices, transform);

        parents.emplace_back(id, comp.getSize(), comp.getPosition());

        glUniform2f(UV_MIN, uv[0], uv[1]);
        glUniform2f(UV_MAX, uv[2], uv[3]);
        glUniform4fv(COLOR, 1, glm::value_ptr(comp.getColor()));


        sendVerticiesToGPU(vertices);

    }
}