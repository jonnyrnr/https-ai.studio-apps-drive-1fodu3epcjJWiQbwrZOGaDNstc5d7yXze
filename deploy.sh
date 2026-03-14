#!/bin/bash
set -e

# Swampify Production Deployment Script
echo "======================================"
echo "Swampify Production Deployment"
echo "======================================"

# Configuration
BUILD_DIR="build"
INSTALL_DIR="/opt/swampify"
PYTHON_VENV="venv"

# Clean previous build
echo "Cleaning previous build..."
rm -rf ${BUILD_DIR}

# Create build directory
echo "Creating build directory..."
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

# Configure with CMake for production
echo "Configuring CMake for production build..."
cmake .. -DCMAKE_BUILD_TYPE=Release \
         -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}

# Build the project
echo "Building project..."
cmake --build . --config Release -j$(nproc)

# Install Python dependencies
echo "Installing Python dependencies..."
cd ..
if [ ! -d "${PYTHON_VENV}" ]; then
    python3 -m venv ${PYTHON_VENV}
fi
source ${PYTHON_VENV}/bin/activate
pip install --upgrade pip
pip install -r requirements.txt

# Install the application (requires sudo)
echo "Installing application to ${INSTALL_DIR}..."
cd ${BUILD_DIR}
sudo cmake --install .

echo "======================================"
echo "Deployment completed successfully!"
echo "======================================"
echo "Application installed to: ${INSTALL_DIR}"
echo "Python environment: ${PYTHON_VENV}"
