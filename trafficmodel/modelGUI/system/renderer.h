#pragma once
#include "config.h"
#include "renderSet.h"
#include "rectangleMesh.h"
#include "uiComponent.h"
#include "camera.h"

class Renderer {
    private:
        double mx, my;
        unsigned int COLOR;
        Camera* camera;
        render_set<UIComponent*> uiObjs;
        render_set<RectangleMesh*> gameObjs;

        glm::vec4 color;
        bool pointInTriangle(
            const glm::vec2& P, const glm::vec2& A, 
            const glm::vec2& B, const glm::vec2& C
        );
    public:
        Renderer(Camera* camera, unsigned int shader);
        ~Renderer();
        void renderFrame(float dt);

        bool inFrame(const std::vector<float>& v);
        bool overlapsMouse(const std::vector<float>& vertices, const std::vector<int>& indices);
        glm::vec2 mousePos();

        // Temp functions?
        int32_t addGameObj(RectangleMesh* mesh);

};