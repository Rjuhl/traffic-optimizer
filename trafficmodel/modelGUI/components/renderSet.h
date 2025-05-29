#pragma once
#include "components.h"
#include <unordered_map>
#define COMP_SET_MAX_OBJ 4096

template<typename T>
class render_set {
    private:
        uint32_t nextId = 0;
        std::vector<uint32_t> availableIds;
        std::unordered_map<uint32_t, int> idToIndex;
    public:
        std::vector<WithId<T>> components;
        
        render_set() {
            components.reserve(COMP_SET_MAX_OBJ);
        };

        T* get(uint32_t id) {
            auto it = idToIndex.find(id);
            if (it != idToIndex.end()) {
                return &components[it->second].value;
            }
            return nullptr;
        }
        

        uint32_t add(T obj) {
            if (components.size() >= COMP_SET_MAX_OBJ && availableIds.empty()) {
                throw std::runtime_error("render set is full");
            }            

            uint32_t id = nextId;
            if (availableIds.size() > 0) {
                id = availableIds.back();
                availableIds.pop_back();
            } else { nextId += 1; }

            idToIndex[id] = components.size();
            components.push_back(WithId(id, obj));
            return id;
        };

        void remove(uint32_t id) {
            if (idToIndex.find(id) != idToIndex.end()) {
                int elemIndx = idToIndex[id];
                std::swap(components[elemIndx], components[components.size() - 1]);
                idToIndex[components[elemIndx].id] = elemIndx;
                components.pop_back();
                idToIndex.erase(id);
                availableIds.push_back(id);
            }
        };
};

