#pragma once
#include "uiComponent.h"
#include <stdexcept>
#include <vector>

class ComponentConstraint {
    public:
        virtual ~ComponentConstraint() = default;
        virtual glm::vec2 getElement(const glm::vec2& relativeVec) = 0;
};