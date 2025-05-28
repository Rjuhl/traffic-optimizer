#pragma once
#include "config.h"
#include <cstdint>

struct ParentInfo {
    uint32_t id;
    glm::vec2 size;
    glm::vec2 position;

    ParentInfo(uint32_t id, const glm::vec2& size, const glm::vec2& position)
        : id(id), size(size), position(position) {}

    bool operator==(const uint32_t otherId) const {
        return id == otherId;
    }
    bool operator!=(const uint32_t otherId) const {
        return id != otherId;
    }
};
