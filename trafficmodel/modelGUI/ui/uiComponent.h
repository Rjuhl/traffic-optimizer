#pragma once
#include "config.h"
#include "atlas.h"
#include "componentState.h"
#include "componentConstraint.h"

class UIComponent{
    private:
        int texture;
        glm::vec4 color;
        glm::vec2 size;
        glm::vec2 position;
        unsigned int ELEM_COUNT = 6;
        unsigned int EBO, VBO, VAO;

        Atlas* atlas;
        GLFWwindow* window;
        UIComponent* parent;
        ComponentState* state;
        ComponentConstraint* sizeConstraint;
        ComponentConstraint* positionContraint;

        void bindVAO();
        std::vector<float> getVertices();
        std::vector<float> getUVMinMax();

        friend class ComponentState;
        
    public:
        UIComponent(
            Atlas* atlas,
            GLFWwindow* window,
            UIComponent* parent,
            ComponentState* state,
            ComponentConstraint* sizeConstraint,
            ComponentConstraint* positionContraint
        );
        ~UIComponent();

        void Init();
        void update();
        void draw();
        void updateAndDraw();

        void setTexture(int texture_);
        void setParent(UIComponent* parent_);
        void setWindow(GLFWwindow* window_);
        void setPosition(glm::vec2 position_);
        void setSize(glm::vec2 size_);
        void setColor(glm::vec4 color_);

        int getTexture();
        UIComponent* getParent();
        GLFWwindow* getWindow();
        glm::vec2 getPosition();
        glm::vec2 getSize();
        glm::vec4 getColor();

};