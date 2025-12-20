# Swampify Deployment Guide

## Production Deployment

This guide covers deploying Swampify in production environments.

## Prerequisites

- CMake 3.21 or higher
- C++ compiler with C++17 support
- Python 3.8 or higher
- Git
- Linux/macOS/Windows environment

## Deployment Options

### Option 1: Native Deployment

Use the provided deployment script for a native installation:

```bash
chmod +x deploy.sh
./deploy.sh
```

This will:
1. Build the application in Release mode
2. Create a Python virtual environment
3. Install Python dependencies
4. Install the application to `/opt/swampify`

### Option 2: Docker Deployment

For containerized deployment:

```bash
chmod +x deploy-docker.sh
./deploy-docker.sh
```

Or manually:

```bash
docker build -t swampify:production .
docker run -d --name swampify swampify:production
```

### Option 3: Manual Build

For custom deployment:

```bash
# Build the application
chmod +x build.sh
./build.sh

# Install Python dependencies
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
```

## Production Configuration

The CMakeLists.txt includes production-ready settings:
- Release build type with O3 optimization
- NDEBUG compilation flag
- C++17 standard
- Install targets configured

## Environment Variables

Set these environment variables for production:

```bash
export SWAMPIFY_ENV=production
export SWAMPIFY_LOG_LEVEL=info
```

## Security Considerations

1. Run Python tools in a virtual environment
2. Use least-privilege user accounts
3. Keep dependencies updated
4. Review OSINT tool configurations before use

## Monitoring

Monitor the following:
- Application logs in `/var/log/swampify/`
- System resource usage
- Python virtual environment status

## Troubleshooting

### Build Failures
- Ensure all dependencies are installed
- Check CMake version (3.21+)
- Verify compiler supports C++17

### Python Dependencies
- Activate virtual environment before running Python tools
- Update pip: `pip install --upgrade pip`

## Updates

To update the deployment:

```bash
git pull
./deploy.sh
```

## Support

For issues, check the project repository or documentation.
