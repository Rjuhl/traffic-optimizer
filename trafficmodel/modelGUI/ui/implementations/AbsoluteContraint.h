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
            if (uiComp->getParent() == nullptr) {
                int pw, ph;
                glfwGetWindowSize(uiComp->getWindow(), &pw, &ph);
                parentPos = {0.f, 0.f};
            } else {
                parentPos = uiComp->getParent()->getPosition();
            }

            return parentPos + glm::vec2(x, y);
        }
};
