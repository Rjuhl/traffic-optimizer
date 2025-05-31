#pragma once
#include "config.h"
#include "renderSet.h"
#include "rectangleMesh.h"
#include "uiComponent.h"
#include "camera.h"
#include "uiRegistry.h"
#include "atlas.h"

class Renderer {
    private:
        double mx, my;
        unsigned int COLOR;
        Atlas* atlas;
        Camera* camera;
        UIRegistry* uiRegistry;
        render_set<RectangleMesh*> gameObjs; // This needs to change to be the actual obejects

        glm::vec4 color;
        bool pointInTriangle(
            const glm::vec2& P, const glm::vec2& A, 
            const glm::vec2& B, const glm::vec2& C
        );
    public:
        Renderer(Camera* camera, Atlas* atlas);
        ~Renderer();
        void renderFrame(float dt);

        bool inFrame(const std::vector<float>& v);
        bool overlapsMouse(const std::vector<float>& vertices, const std::vector<int>& indices);
        glm::vec2 mousePos();

        // Temp functions?
        int32_t addGameObj(RectangleMesh* mesh);
        int32_t addUIObj( 
            int texture, 
            uint32_t parent,
            glm::vec4 color,
            std::shared_ptr<ComponentState> state,
            std::shared_ptr<ComponentConstraint> sizeConstraint,
            std::shared_ptr<ComponentConstraint> positionConstraint
        );
};