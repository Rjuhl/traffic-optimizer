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
            if (uiComp->parent == nullptr) {
                int pw, ph;
                glfwGetWindowSize(uiComp->window, &pw, &ph);
                parentPos = {0.f, 0.f};
                parentSize = {pw, ph};
            } else {
                parentPos = uiComp->parent->position;
                parentSize = uiComp->parent->size;
            }

            return parentPos + (parentSize * glm::vec2(x, y));
        };
};