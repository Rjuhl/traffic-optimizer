#pragma once
#include "uiComponent.h"
#include <vector>
#include <functional> 

class UIComponent;

class ComponentState {
    protected:
        UIComponent* uiComp = nullptr;
    public:

        virtual ~ComponentState() = default;
        virtual void updateState() = 0;
        virtual void setColors() const = 0;
        virtual void setTexture() const = 0;

        void setParent(UIComponent* uiComp_) { uiComp = uiComp_; };
        void update() {
            updateState();
            setColors();
            setTexture();
        };
};
