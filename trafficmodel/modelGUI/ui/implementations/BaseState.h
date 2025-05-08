#pragma once
#include "config.h"
#include "componentState.h"

class BaseState : public ComponentState {
    private:
        int baseTexture;
        float hoverGrowth;
        glm::vec4 baseColor;
        int& mouseX, mouseY;

        bool isOverlap() {
            return(
                uiComp->poisiton.x <= mouseX <= uiComp->poisiton.x + uiComp->size.x &&
                uiComp->poisiton.y <= mouseY <= uiComp->poisiton.y + uiComp->size.y
            );
        };

    public:

        BaseState(
            int baseTexture, 
            float hoverGrowth, 
            glm::vec4 baseColor, 
            int& mouseX, int& mouseY
        ) : 
        baseTexture(baseTexture), hoverGrowth(hoverGrowth), 
        baseColor(baseColor), mouseX(mouseX), mouseY(mouseY) {};

        void updateState() override {
            if (isOverlap) {
                float xDiff = (uiComp->size.x * hoverGrowth) - uiComp->size.x;
                float yDiff = (uiComp->size.y * hoverGrowth) - uiComp->size.y;
                uiComp->position.x -= xDiff / 2;
                uiComp->position.y -= xDiff / 2;
                uiComp->size.x *= hoverGrowth;
                uiComp->size.y *= hoverGrowth;
            }
        };
        void setColors() override {
            uiComp->color = color;
        };
        void setTexture() override {
            isOverlap() ? uiComp->texture = baseTexture + 1 : uiComp->texture = baseTexture;
        };

};