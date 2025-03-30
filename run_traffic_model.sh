#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Set default build type
BUILD_TYPE=${1:-Debug}

# Define the project root and build directory
PROJECT_ROOT="$(pwd)"
BUILD_DIR="${PROJECT_ROOT}/build"

echo "Build type: ${BUILD_TYPE}"

# Create or recreate the build directory
if [ ! -d "${BUILD_DIR}" ]; then
    echo "Creating build directory..."
    mkdir "${BUILD_DIR}"
else
    echo "Recreating build directory..."
    rm -rf "${BUILD_DIR}"
    mkdir "${BUILD_DIR}"
fi

# Navigate to the build directory
cd "${BUILD_DIR}"

# Run CMake with the specified build type
cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} "../trafficmodel"

# Build the project
cmake --build .

# Run the tests and main application
ctest --output-on-failure
./traffic_model
