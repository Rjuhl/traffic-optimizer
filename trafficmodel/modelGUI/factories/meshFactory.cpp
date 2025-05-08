#include "meshFactory.h"
#include "mymath.h"

const IMap<int> MeshFactory::zMap({
    TextId::ONE_WAY_ROAD, 1, TextId::TWO_WAY_ROAD, 1, 
    TextId::INTERSECTION, 2, 
    TextId::GARAGE, 3, TextId::DESTINATION, 3, 
    TextId::RED_CAR, 4, TextId::GREEN_CAR, 4, TextId::BLUE_CAR, 4
});

MeshFactory::MeshFactory(
    Atlas* atlas
) : 
textWidth(atlas->textWidth), textHeight(atlas->textHeight), 
UV_MIN(atlas->uvMinLocation), UV_MAX(atlas->uvMaxLocation)
{};

MeshFactory::~MeshFactory(){};

RectangleMesh* MeshFactory::makeIntersection(Pos p) {
    return new RectangleMesh(
        p,
        INTERSECTION_HEIGHT, INTERSECTION_WIDTH, 
        zMap.get(TextId::INTERSECTION),
        TextId::INTERSECTION, textWidth, textHeight,
        UV_MIN, UV_MAX
    );
};

RectangleMesh* MeshFactory::makeGarage(Pos p) {
    return new RectangleMesh(
        p,
        GARAGE_HEIGHT, GARAGE_WIDTH,
        zMap.get(TextId::GARAGE),
        TextId::GARAGE, textWidth, textHeight,
        UV_MIN, UV_MAX
    );
};
RectangleMesh* MeshFactory::makeDestination(Pos p) {
    return new RectangleMesh(
        p,
        DESTINATION_HEIGHT, DESTINATION_WIDTH, 
        zMap.get(TextId::DESTINATION),
        TextId::DESTINATION, textWidth, textHeight,
        UV_MIN, UV_MAX
    );
};

RectangleMesh* MeshFactory::makeOneWayRoad(Pos p1, Pos p2) {
    return new RectangleMesh (
        p1, p2,
        ROAD_WIDTH, zMap.get(TextId::ONE_WAY_ROAD), true,
        TextId::ONE_WAY_ROAD, textWidth, textHeight,
        UV_MIN, UV_MAX
    );
}

RectangleMesh* MeshFactory::makeTwoWayRoad(Pos p1, Pos p2) {
    return new RectangleMesh(
        p1, p2,
        ROAD_WIDTH, zMap.get(TextId::TWO_WAY_ROAD), true,
        TextId::TWO_WAY_ROAD, textWidth, textHeight,
        UV_MIN, UV_MAX
    );
}

RectangleMesh* MeshFactory::makeCar(Pos c, Pos rStart, Pos rEnd, int color) {
    float M, Z;
    glm::vec2 car = {c.x, c.y};
    glm::vec2 XYBar;
    glm::vec2 OffsetXYBar;
    if (std::abs(rEnd.y - rStart.y) < 1e-6) {
        XYBar = {CAR_HEIGHT / 2, 0.f};
        OffsetXYBar = {0.f, CAR_OFFSET};
    } else if (std::abs(rEnd.x - rStart.x) < 1e-6) {
        XYBar = {0.f, CAR_HEIGHT / 2};
        OffsetXYBar = {CAR_OFFSET, 0.f};
    } else {
        M = slope(rStart, rEnd);
        Z = -1 / M;

        XYBar = {std::sqrt(std::pow(CAR_HEIGHT / 2, 2) / (1 + std::pow(M, 2))), 0.f};
        XYBar.y = std::abs(M * XYBar.x);

        OffsetXYBar = {std::sqrt(std::pow(CAR_OFFSET, 2) / (1 + std::pow(Z, 2))), 0.f};
        OffsetXYBar.y = std::abs(Z * OffsetXYBar.x);
    }

    glm::vec2 roadDir = {rEnd.x - rStart.x, rEnd.y - rStart.y};
    glm::vec2 exspansionDir = {std::copysign(1.0f, roadDir.x), std::copysign(1.0f, roadDir.y)};
    
    //Update direction of XYBar and XYBarOffset
    OffsetXYBar.x *= exspansionDir.y;
    OffsetXYBar.y *= -1 * exspansionDir.x;

    glm::vec2 p1 = (car - (XYBar * exspansionDir)) + OffsetXYBar;
    glm::vec2 p2 = (car + (XYBar * exspansionDir)) + OffsetXYBar;

    return new RectangleMesh(
        Pos(p1.x, p1.y), Pos(p2.x, p2.y),
        CAR_WIDTH, zMap.get(TextId::BLUE_CAR), false,
        TextId::RED_CAR + color, textWidth, textHeight,
        UV_MIN, UV_MAX
    );

}