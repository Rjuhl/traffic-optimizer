#pragma once
#include "strategy.h"

class DefaultStrategy : public Strategy {
    public:
        DefaultStrategy(Map* map) : Strategy(map) {};
        int setUpdateSchedule() override;
        std::unordered_map<int, std::tuple<int, int>> updateLightTimers() override;
};