#pragma once
#include "pos.h"
#include "textureConstants.h"
#include "imap.h"
#include "rectangleMesh.h"
#include "atlas.h"


class MeshFactory {
    private:
        int textWidth, textHeight;
        unsigned int UV_MIN, UV_MAX;
        static const IMap<int> zMap;

        static constexpr float ROAD_WIDTH = 2;

        static constexpr float INTERSECTION_WIDTH = 4;
        static constexpr float INTERSECTION_HEIGHT = 4;

        static constexpr float GARAGE_WIDTH = 4;
        static constexpr float GARAGE_HEIGHT = 4;

        static constexpr float DESTINATION_WIDTH = 4;
        static constexpr float DESTINATION_HEIGHT = 4;

        static constexpr float CAR_WIDTH = 2;
        static constexpr float CAR_HEIGHT = 2;
        static constexpr float CAR_OFFSET = 0.5;

        static constexpr glm::vec4 highlight = glm::vec4(1.f, 1.f, 1.f, 0.f);

    public:
        MeshFactory(Atlas* atlas);

        ~MeshFactory();

        RectangleMesh* makeOneWayRoad(Pos p1, Pos p2);
        RectangleMesh* makeTwoWayRoad(Pos p1, Pos p2);
        RectangleMesh* makeIntersection(Pos p);
        RectangleMesh* makeGarage(Pos p);
        RectangleMesh* makeDestination(Pos p);
        RectangleMesh* makeCar(Pos car, Pos rStart, Pos rEnd, int color);
};