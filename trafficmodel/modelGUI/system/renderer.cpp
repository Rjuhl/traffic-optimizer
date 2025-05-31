#include "renderer.h"
#include "guiHelpers.h"

Renderer::Renderer(Camera* camera, Atlas* atlas) : 
camera(camera), atlas(atlas), COLOR(atlas->colorLocation) { 
    uiRegistry = new UIRegistry(atlas, camera);
};

Renderer::~Renderer() {
    // Delete gamObj and uiObjs
    delete uiRegistry;
};

void Renderer::renderFrame(float dt) {

    //render game objects with camera projection
    // for each
        // Discard if not inframe()
        // Otherwise check if cursor is over it and draw 

    //render ui objests after with ortho projection (same as above)

    camera->update(dt);
    for (int i = 0; i < gameObjs.components.size(); i++) {
        std::vector<float> vertices = gameObjs.components[i].value->getVertices();
        if (inFrame(vertices)) {
            // Setup color
            glm::vec4 objColor = overlapsMouse(vertices, gameObjs.components[i].value->getIndicies()) ? 
                gameObjs.components[0].value->getHighlight() : glm::vec4(0.f, 0.f, 0.f, 0.f);
            if (objColor != color) {
                color = objColor;
                glUniform4fv(COLOR, 1, glm::value_ptr(color));
            }

            // Draw component
            gameObjs.components[i].value->draw();
            
        }
    };

    uiRegistry->drawUI();
    std::cout << "UI drawn" << std::endl;
};



glm::vec2 Renderer::mousePos() {
    glfwGetCursorPos(camera->getWindow(), &mx, &my);
    glm::vec2 windowSize = camera->getScreenSize();
    return glm::vec2((2.f * mx) / windowSize.x - 1.f, 1.f - (2.f * my) / windowSize.y);
}

bool Renderer::inFrame(const std::vector<float>& v) {
    float minX = std::numeric_limits<float>::infinity();
    float maxX = -std::numeric_limits<float>::infinity();
    float minY = std::numeric_limits<float>::infinity();
    float maxY = -std::numeric_limits<float>::infinity();
    for (int i = 0; i < 4 * 5; i += 5) {
        glm::vec4 p = camera->getScreenSpace() * glm::vec4(v[i], v[i + 1], 0.f, 1.f);
        if (p.x < minX) minX = p.x;
        if (p.x > maxX) maxX = p.x;
        if (p.y < minY) minY = p.y;
        if (p.y > maxY) maxY = p.y;
    };

    return ((minX >= -1.f && minX <= 1.f) || (maxX >= -1.f && maxX <= 1.f)) &&
           ((minY >= -1.f && minY <= 1.f) || (maxY >= -1.f && maxY <= 1.f));
    
};

bool Renderer::overlapsMouse(const std::vector<float>& vertices, const std::vector<int>& indices) {

    glm::vec2 mouse = mousePos();
    glm::mat4 ss = camera->getScreenSpace();

    glm::vec4 p1 = ss * glm::vec4(vertices[indices[0] * 5], vertices[(indices[0] * 5) + 1], 0.f, 1.f);
    glm::vec4 p2 = ss * glm::vec4(vertices[indices[1] * 5], vertices[(indices[1] * 5) + 1], 0.f, 1.f);
    glm::vec4 p3 = ss * glm::vec4(vertices[indices[2] * 5], vertices[(indices[2] * 5) + 1], 0.f, 1.f);
    glm::vec4 p4 = ss * glm::vec4(vertices[indices[3] * 5], vertices[(indices[3] * 5) + 1], 0.f, 1.f);
    glm::vec4 p5 = ss * glm::vec4(vertices[indices[4] * 5], vertices[(indices[4] * 5) + 1], 0.f, 1.f);
    glm::vec4 p6 = ss * glm::vec4(vertices[indices[5] * 5], vertices[(indices[5] * 5) + 1], 0.f, 1.f);

    if (pointInTriangle(
        mouse, 
        glm::vec2(p1.x, p1.y), 
        glm::vec2(p2.x, p2.y), 
        glm::vec2(p3.x, p3.y)
    )) return true; 

    if (pointInTriangle(
        mouse, 
        glm::vec2(p4.x, p4.y), 
        glm::vec2(p5.x, p5.y), 
        glm::vec2(p6.x, p6.y)
    )) return true; 

    return false;
};


bool Renderer::pointInTriangle(const glm::vec2& P, const glm::vec2& A, const glm::vec2& B, const glm::vec2& C) {
    glm::vec2 v0 = C - A;
    glm::vec2 v1 = B - A;
    glm::vec2 v2 = P - A;

    float dot00 = glm::dot(v0, v0);
    float dot01 = glm::dot(v0, v1);
    float dot02 = glm::dot(v0, v2);
    float dot11 = glm::dot(v1, v1);
    float dot12 = glm::dot(v1, v2);

    float denom = dot00 * dot11 - dot01 * dot01;
    if (denom == 0.0f) return false;  

    float invDenom = 1.0f / denom;
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v <= 1);
}

// These add funcs should prolly foward along the argument and add the Objects and not hte pointers to make it easier for them to draw
int32_t Renderer::addGameObj(RectangleMesh* mesh){
    return gameObjs.add(mesh);
}

int32_t Renderer::addUIObj(
    int texture, 
    uint32_t parent,
    glm::vec4 color,
    std::shared_ptr<ComponentState> state,
    std::shared_ptr<ComponentConstraint> sizeConstraint,
    std::shared_ptr<ComponentConstraint> positionConstraint
) {
    return uiRegistry->addUIComponent(
        texture, parent, color,
        state, sizeConstraint, positionConstraint
    );
};