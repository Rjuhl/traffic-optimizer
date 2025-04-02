#pragma once

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

    IntersectionData operator+(const IntersectionData& other) const {
        return IntersectionData(
            verticalThroughput + other.verticalThroughput,
            horizontalThroughput + other.horizontalThroughput,
            verticalEfficiency + other.verticalEfficiency,
            horizontalEfficiency + other.horizontalEfficiency
        );
    }
};
