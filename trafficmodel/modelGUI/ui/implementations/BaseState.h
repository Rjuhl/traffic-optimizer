#pragma once
#include "config.h"
#include "componentState.h"

class BaseState : public ComponentState {
    private:
        int baseTexture;
        float hoverGrowth;
        glm::vec4 baseColor;

        bool isOverlap(glm::vec2 mouse) {

            // There is a bug here: the coordinate systems differ between mouse and uiComp here

            // return(
            //     uiComp->getPosition().x <= mouse.x <= uiComp->getPosition().x + uiComp->getSize().x &&
            //     uiComp->getPosition().y <= mouse.y <= uiComp->getPosition().y + uiComp->getSize().y
            // );

            return false;
        };

    public:

        BaseState(
            int baseTexture, 
            float hoverGrowth, 
            glm::vec4 baseColor 
        ) : 
        baseTexture(baseTexture), hoverGrowth(hoverGrowth), 
        baseColor(baseColor) {};

        void updateState(glm::vec2 mouse) override {
            if (isOverlap(mouse)) {
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

        void setColors(glm::vec2 mouse) override {
            uiComp->setColor(baseColor);
        };

        void setTexture(glm::vec2 mouse) override {
            isOverlap(mouse) ? uiComp->setTexture(baseTexture + 1) : uiComp->setTexture(baseTexture);
        };

};