#pragma once
#include "uiComponent.h"
#include <vector>

class PositionConstraint {
    protected:
        UIComponent* parent = nullptr;
    public:
        virtual ~PositionConstraint() = default;
        void setParent(UIComponent* parent_) { parent = parent_; };
        virtual glm::vec2 getPosition() = 0;
};