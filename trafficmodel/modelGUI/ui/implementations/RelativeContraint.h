#pragma once
#include "componentConstraint.h"

class RelativeContraint : public ComponentConstraint {
    private:
        float x, y;
    public:
        RelativeContraint(float x_, float y_) : x(x_), y(y_) {};
        glm::vec2 getElement() override {
            isValid();

            glm::vec2 parentPos, parentSize;
            if (uiComp->getParent() == nullptr) {
                int pw, ph;
                glfwGetWindowSize(uiComp->getWindow(), &pw, &ph);
                parentPos = {0.f, 0.f};
                parentSize = {pw, ph};
            } else {
                parentPos = uiComp->getParent()->getPosition();
                parentSize = uiComp->getParent()->getPosition();
            }

            return parentPos + (parentSize * glm::vec2(x, y));
        };
};