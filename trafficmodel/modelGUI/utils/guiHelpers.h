#pragma once
#include "config.h"

class GUIHelpers {
    public:
        void printVertex(std::vector<float> verticies);
        void printfVector(std::vector<float> vec);
        void printMat4(const glm::mat4& mat);
};

extern GUIHelpers guiHelpers;