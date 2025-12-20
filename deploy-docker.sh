#!/bin/bash
set -e

# Swampify Docker Production Deployment Script
echo "======================================"
echo "Swampify Docker Deployment"
echo "======================================"

# Build Docker image
echo "Building Docker image..."
docker build -t swampify:latest -f Dockerfile .

# Tag for production
echo "Tagging image for production..."
docker tag swampify:latest swampify:production

# Optional: Push to registry (uncomment and configure)
# REGISTRY="your-registry.com"
# docker tag swampify:latest ${REGISTRY}/swampify:latest
# docker push ${REGISTRY}/swampify:latest

echo "======================================"
echo "Docker build completed successfully!"
echo "======================================"
echo "To run the container:"
echo "docker run -d --name swampify swampify:production"
