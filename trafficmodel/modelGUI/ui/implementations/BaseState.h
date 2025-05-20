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
                uiComp->getPosition().x <= mouseX <= uiComp->getPosition().x + uiComp->getSize().x &&
                uiComp->getPosition().y <= mouseY <= uiComp->getPosition().y + uiComp->getSize().y
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
                float xDiff = (uiComp->getSize().x * hoverGrowth) - uiComp->getSize().x;
                float yDiff = (uiComp->getSize().y * hoverGrowth) - uiComp->getSize().y;
                uiComp->setPosition(glm::vec2(
                    uiComp->getPosition().x - (xDiff / 2), 
                    uiComp->getPosition().y - (xDiff / 2)
                ));
                uiComp->setSize(glm::vec2(
                    uiComp->getSize().x  * hoverGrowth,
                    uiComp->getSize().y * hoverGrowth
                ));
            }
        };

        void setColors() override {
            uiComp->setColor(baseColor);
        };

        void setTexture() override {
            isOverlap() ? uiComp->setTexture(baseTexture + 1) : uiComp->setTexture(baseTexture);
        };

};