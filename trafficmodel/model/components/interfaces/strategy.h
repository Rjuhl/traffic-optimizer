#pragma once
#include "map.h"
#include <memory>
#include <unordered_map>
#include <tuple>

class Map; 

class Strategy {
public:
    std::shared_ptr<Map> map;

    Strategy(Map* map) : map(std::unique_ptr<Map>(map)) {};
    virtual ~Strategy() = default;
    virtual int setUpdateSchedule() = 0;
    virtual std::unordered_map<int, std::tuple<int, int>> updateLightTimers() = 0;
};
