#pragma once
#include <vector>
#include <stdexcept>

template<typename T>
class IMap {
private:
    std::vector<T> map;

public:
    IMap() = default;

    IMap(const std::vector<T>& initMap) : map(initMap) {
        if (map.size() % 2 != 0) {
            throw std::invalid_argument("Flat map must have an even number of elements (key-value pairs)");
        }
    }

    int size() const {
        return map.size() / 2;
    }

    void add(T key, T val) {
        map.push_back(key);
        map.push_back(val);
    }

    T get(T key) const {
        for (size_t i = 0; i < map.size(); i += 2) {
            if (map[i] == key) return map[i + 1];
        }
        throw std::out_of_range("Key not found");
    }

};
