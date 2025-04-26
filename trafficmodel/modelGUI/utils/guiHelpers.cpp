#include "guiHelpers.h"

GUIHelpers guiHelpers = GUIHelpers();

void GUIHelpers::printVertex(std::vector<float> verticies) {
    for (int i = 0; i < verticies.size(); i += 3) {
        std::cout << verticies[i] << ", " << verticies[i + 1] << ", " << verticies[i + 2] << std::endl;
    }
    std::cout << std::endl;
};