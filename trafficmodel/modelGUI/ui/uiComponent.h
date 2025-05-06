#pragma once
#include "config.h"
#include "componentState.h"
#include "positionConstraint.h"
#include "sizeConstraint.h"

class UIComponent{
    private:
        int textureId;
        unsigned int UV_MIN, UV_MIX, COLOR;

        glm::vec4 position;

        GLFWwindow* window;
        UIComponent* parent;
        ComponentState* state;
        PositionConstraint* position;

        friend class ComponentState;
        friend class PositionConstraint;
        friend class SizeConstraint;
        
    public:
        UIComponent();
        ~UIComponent();

        void Init();
        void draw();

        // Returns UI x, y pos and w/h
        glm::vec4 getPosition();
};