#pragma once
#include "uiComponent.h"
#include <stdexcept>
#include <vector>

class ComponentConstraint {
    protected:
        UIComponent* uiComp = nullptr;
    public:
        virtual ~ComponentConstraint() = default;
        void setParent(UIComponent* uiComp_) { uiComp = uiComp_; };
        void isValid() const { if (uiComp == nullptr) throw std::logic_error("Contraint is orphaned"); };
        virtual glm::vec2 getElement() = 0;
};