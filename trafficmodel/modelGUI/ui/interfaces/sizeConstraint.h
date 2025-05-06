#pragma once
#include "uiComponent.h"
#include <vector>

class SizeConstraint {
    protected:
        UIComponent* parent = nullptr;
    public:
        virtual ~SizeConstraint() = default;
        void setParent(UIComponent* parent_) { parent = parent_; };
        virtual glm::vec2 getSize() = 0;
};  