#!/bin/bash
set -e

# Swampify Production Build Script
echo "======================================"
echo "Swampify Production Build"
echo "======================================"

# Configuration
BUILD_DIR="build"
BUILD_TYPE="Release"

# Clean previous build
echo "Cleaning previous build..."
rm -rf ${BUILD_DIR}

# Create build directory
echo "Creating build directory..."
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

# Configure with CMake
echo "Configuring CMake..."
cmake .. -DCMAKE_BUILD_TYPE=${BUILD_TYPE}

# Build the project
echo "Building project..."
cmake --build . --config ${BUILD_TYPE} -j$(nproc)

# Run tests if available
if [ -f "CTestTestfile.cmake" ]; then
    echo "Running tests..."
    ctest --output-on-failure
fi

echo "======================================"
echo "Build completed successfully!"
echo "======================================"
echo "Build directory: ${BUILD_DIR}"
echo "Build type: ${BUILD_TYPE}"
