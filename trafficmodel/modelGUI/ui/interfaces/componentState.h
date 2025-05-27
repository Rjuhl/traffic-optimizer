#pragma once
#include "config.h"
#include "uiComponent.h"
#include <vector>
#include <functional> 

class UIComponent;

class ComponentState {
    protected:
        UIComponent* uiComp = nullptr;
    public:

        virtual ~ComponentState() = default;
        virtual void updateState(glm::vec2 mouse) = 0;
        virtual void setColors(glm::vec2 mouse) = 0;
        virtual void setTexture(glm::vec2 mouse) = 0;

        void setParent(UIComponent* uiComp_) { uiComp = uiComp_; };
        void update(glm::vec2 mouse) {
            updateState(mouse);
            setColors(mouse);
            setTexture(mouse);
        };
};

