#include "helpers.h"

void DebugHelpers::printDirections(std::vector<Direction> directions) {
    std::cout << "Directions ";
    for (int i = 0; i < directions.size(); i++) {
        Direction direction = directions[i];
        switch (direction) {
            case Direction::TOP: std::cout << "Top "; break;
            case Direction::BOTTOM: std::cout << "Bottom"; break;
            case Direction::LEFT: std::cout << "Left "; break;
            case Direction::RIGHT: std::cout << "Right "; break;
            default: std::cout << "Unknown "; break;
        }
    }
    std::cout << std::endl;
};