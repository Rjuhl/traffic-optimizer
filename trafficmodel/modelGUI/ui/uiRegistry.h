#pragma once
#include "config"
#include "uiComponent.h"
#include "atlas.h"
#include "cameria.h"
#include "uiSet.h"

class UIRegistry {
    private:
        Atlas* atlas;
        Camera* camera;
        
        ui_set<UIComponets> components;

        glm::vec2 getMouse();
        glm::vec2 getWindowSize();
        glm::mat4 getTransform();
        std::vector<float> getUVMinMax(int texture);
        glm::vec3 transformPoint(const glm::mat4& transform, const glm::vec3 point);

    public:
        UIRegistry(Atlas* atlas, Camera* camera);
        ~UIRegistry();

        void removeUIComponent(uint32 id);
        uint32_t addUIComponent(
            uint32_t parent,
            ComponentState* state,
            ComponentConstraint* sizeConstraint,
            ComponentConstraint* positionConstraint
        );

        void drawUI();   
}