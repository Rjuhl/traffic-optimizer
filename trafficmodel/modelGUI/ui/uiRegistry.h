#pragma once
#include "config.h"
#include "uiComponent.h"
#include "atlas.h"
#include "camera.h"
#include "uiSet.h"
#include "textureConstants.h"
#include "datatypes.h"

class UIRegistry {
    private:
        Atlas* atlas;
        Camera* camera;
        
        ui_set<UIComponent> components;

        unsigned int EBO, VBO, VAO;
        unsigned int UV_MIN, UV_MAX, COLOR;
        std::vector<int> indices = {0, 1, 2, 1, 3, 2};

        glm::vec2 getMouse();
        glm::vec2 getWindowSize();
        glm::mat4 getTransform();
        std::vector<float> getUVMinMax(int texture);
        glm::vec3 transformPoint(const glm::mat4& transform, const glm::vec3 point);

        void sendVerticiesToGPU(const std::vector<float>& vertices);

    public:
        UIRegistry(Atlas* atlas, Camera* camera);
        ~UIRegistry();

        void removeUIComponent(uint32_t id);
        uint32_t addUIComponent(
            int texture, 
            uint32_t parent,
            glm::vec4 color,
            ComponentState* state,
            ComponentConstraint* sizeConstraint,
            ComponentConstraint* positionConstraint
        );

        void drawUI();   
};