#pragma once
#include "uiComponent.h"
#include <vector>
#include <functional> 

class ComponentState {
    protected:
        UIComponent* parent = nullptr;
        std::vector<std::reference_wrapper<float>> stateVector;
    public:
        ComponentState(const std::vector<std::reference_wrapper<float>>& stateVector_)
            : stateVector(stateVector_) {};

        virtual ~ComponentState() = default;
        virtual void updateState() = 0;
        virtual void setColors() const = 0;
        virtual void setTexture() const = 0;

        void setParent(UIComponent* parent_) { parent = parent_; };
        void update() {
            updateState();
            setColors();
            setTexture();
        };
};