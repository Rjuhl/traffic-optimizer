#pragma once
#include <string>

struct IntersectionData {
    int verticalThroughput;
    int horizontalThroughput;
    float verticalEfficiency; 
    float horizontalEfficiency; 

    IntersectionData() 
        : verticalThroughput(0), horizontalThroughput(0),
          verticalEfficiency(0.0f), horizontalEfficiency(0.0f) {}

    IntersectionData(
        int verticalThroughput,
        int horizontalThroughput,
        float verticalEfficiency,
        float horizontalEfficiency
    ) 
        : verticalThroughput(verticalThroughput), 
          horizontalThroughput(horizontalThroughput),
          verticalEfficiency(verticalEfficiency), 
          horizontalEfficiency(horizontalEfficiency) {}

    std::string toString() {
        return (
            "[" + 
            std::to_string(verticalThroughput) + "," +
            std::to_string(horizontalThroughput) + "," +
            std::to_string(verticalEfficiency) + "," + 
            std::to_string(horizontalEfficiency) + "]"
        );
    };

    IntersectionData operator+(const IntersectionData& other) const {
        return IntersectionData(
            verticalThroughput + other.verticalThroughput,
            horizontalThroughput + other.horizontalThroughput,
            verticalEfficiency + other.verticalEfficiency,
            horizontalEfficiency + other.horizontalEfficiency
        );
    }

    bool operator==(const IntersectionData& other) const {
        return (
            verticalThroughput == other.verticalThroughput &&
            horizontalThroughput ==  other.horizontalThroughput &&
            verticalEfficiency == other.verticalEfficiency && 
            horizontalEfficiency == other.horizontalEfficiency
        );
    };
};
