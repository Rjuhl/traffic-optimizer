#pragma once 
#include "componentConstraint.h"

class AbsoluteContraint : public ComponentConstraint {
    private:
        float x, y;
    public:
        AbsoluteContraint(float x_, float y_) : x(x_), y(y_) {};
        glm::vec2 getElement() override {
            isValid();

            glm::vec2 parentPos;
            if (uiComp->parent == nullptr) {
                int pw, ph;
                glfwGetWindowSize(uiComp->window, &pw, &ph);
                parentPos = {0.f, 0.f};
            } else {
                parentPos = uiComp->parent->position;
            }
        }

        return parentPos + glm::vec2(x, y);
};
