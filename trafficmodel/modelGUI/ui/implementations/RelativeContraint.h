#pragma once
#include "componentConstraint.h"

class RelativeContraint : public ComponentConstraint {
    private:
        glm::vec2 contraint;
    public:
        RelativeContraint(glm::vec2 contraint_) : contraint(contraint_) {};
        glm::vec2 getElement(glm::vec2 relativeVec) override {

            std::cout << "!! " << relativeVec.x << ", " << relativeVec.y << " " << contraint.x << ", " << contraint.y << std::endl;

            return relativeVec * contraint;
        };
};