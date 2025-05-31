#pragma once
#include "config.h"
#include "componentConstraint.h"
#include "componentState.h"


class UIComponent{
    private:
        uint32_t parent;
        std::shared_ptr<ComponentState> state;
        std::shared_ptr<ComponentConstraint> sizeConstraint;
        std::shared_ptr<ComponentConstraint> positionConstraint;

        int texture;
        float level;
        glm::vec2 size;
        glm::vec2 position;
        glm::vec4 color;

    public:
        UIComponent(
            int texture, 
            float level,
            uint32_t parent,
            glm::vec4 color,
            std::shared_ptr<ComponentState> state,
            std::shared_ptr<ComponentConstraint> sizeConstraint,
            std::shared_ptr<ComponentConstraint> positionConstraint
        );
        ~UIComponent();

        void update(
            const glm::vec2& mouse,
            const glm::vec2& parentSize,
            const glm::vec2& parentPostition
        );

        std::vector<float> getVertices();
        
        int getTexture();
        int getLevel();
        uint32_t getParent();
        glm::vec2 getSize();
        glm::vec2 getPosition();
        glm::vec4 getColor();

        void setTexture(int texture_);
        void setSize(glm::vec2 size_);
        void setPosition(glm::vec2 position_);
        void setColor(glm::vec4 color_);
};