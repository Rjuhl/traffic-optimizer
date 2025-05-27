#pragma once
#include <vector>
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <utility>
#define UI_SET_MAX_OBJ 256

template<typename T>
struct WithId {
    uint32_t id;
    T value;
    WithId(uint32_t id, const T& value) : id(id), value(value) {};
};


template<typename T>
class ui_set {
    private:
        uint32_t nextId = 0;
        std::vector<WithId<T>> components;

        uint32_t getId() {
            if (nextId == UINT32_MAX) throw std::runtime_error("ID overflow");
            return ++nextId;
        };

    public:
        
        ui_set() {
            components.reserve(UI_SET_MAX_OBJ);
        };

        template<typename U>
        uint32_t add(U&& obj, uint32_t parent) {
            uint32_t id = getId();
            if (parent == 0) {
                components.emplace_back(id, std::forward<U>(obj));
            } else {
                auto it = std::find_if(components.begin(), components.end(),
                    [parent](const WithId<T>& elem) {
                        return elem.id == parent;
                    });
        
                if (it != components.end()) {
                    components.emplace(it + 1, id, std::forward<U>(obj));
                } else {
                    components.emplace_back(id, std::forward<U>(obj));
                }
            }
            return id;
        }
        
        
        void remove(uint32_t id) {
            components.erase(
                std::remove_if(components.begin(), components.end(),
                    [id](const WithId<T>& elem) {
                        return elem.id == id;
                    }),
                components.end()
            );
        };

        T* get(uint32_t id) {
            for (size_t i = 0; i < components.size(); i++) {
                if (components[i].id == id) return &components[i].value;
            }

            return nullptr;
        };

        std::vector<WithId<T>> getItems() {
            return components;
        };
    };

