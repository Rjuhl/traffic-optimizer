#pragma once
#include "config.h"
#include "road.h"
#include "pos.h"
#include "intersectionData.h"
#include <deque>

class Road;

class Intersection {
    private:
        std::unordered_map<Direction, Road*> outgoing;
        std::unordered_map<Road*, Direction> incoming;
        static const std::unordered_map<Direction, int> directions;

        int carsCrossed;
        int carsThatCouldCross;
        int maxQueueSize;
        std::deque<IntersectionData> intersectionData;

        Pos pos;
        int countDown;
        int verticalCountStart;
        int horizontalCountStart;

        bool verticalCrossing;
        
        void updateQueue(IntersectionData data);

    public:
        Intersection(
            Pos pos,
            int verticalCountStart, 
            int horizontalCountStart, 
            bool verticalCrossing
        );

        // Given a direction get the correct road
        Road* link(Direction dir);

        // Checks all conditions for a car to cross from one road to another and returns the new pos/road
        std::tuple<Pos, Road*> cross(Road* road, Pos pos, Direction dir);

        // returns the the set intersection times for the intersection
        std::tuple<int, int> getIntersectionTimes();

        // returns a data about travel throught intesection for X (or range) time steps ago
        IntersectionData getIntersectionData(int range);
        
        // Update light timeings 
        void updateLightTiming(int verticalTiming, int horizontalTiming);

        void update();
        void assignIncomingRoad(Road* road, Direction dir);
        void assignOutgoingRoad(Road* road, Direction dir);

        std::tuple<std::vector<float>, std::vector<Road*>> serialize();
        static const std::unordered_map<Direction, int>& DirMap();
};
