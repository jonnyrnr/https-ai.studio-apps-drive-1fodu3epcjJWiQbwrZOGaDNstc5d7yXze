# Swampify - OSINT Content Research Tool

Swampify is a cross-platform desktop application that combines JUCE framework with Python OSINT tools for content research and intelligence gathering.

## Features

- **JUCE-based GUI**: Native cross-platform desktop interface
- **theHarvester Integration**: Gather emails, subdomains, IPs, and URLs from public sources
- **Sherlock Integration**: Search for usernames across 300+ social networks
- **Production Ready**: Optimized build configurations and deployment scripts

## Components

### C++ Application (JUCE)
- Modern GUI interface built with JUCE 7.0.11
- Real-time OSINT tool execution
- Results display and management

### Python OSINT Tools
- **theHarvester v0.0.1**: Email and subdomain harvesting
- **sherlock-project v0.16.0**: Username enumeration across social platforms

## Building

### Quick Build
```bash
./build.sh
```

### Manual Build
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

## Deployment

See [DEPLOYMENT.md](DEPLOYMENT.md) for detailed deployment instructions.

### Quick Deploy
```bash
./deploy.sh
```

### Docker Deploy
```bash
./deploy-docker.sh
```

## Usage

1. Launch the Swampify application
2. Enter a target domain or username
3. Click "Run theHarvester" for domain reconnaissance
4. Click "Run Sherlock" for username searches
5. View results in the application window

## Development

### Prerequisites
- CMake 3.21+
- C++17 compiler
- Python 3.8+
- JUCE dependencies (installed automatically)

### Project Structure
```
.
├── src/                  # C++ source files
│   ├── Main.cpp         # Application entry point
│   ├── MainComponent.*  # Main GUI component
│   └── OSINTManager.*   # Python integration layer
├── scripts/             # Python wrapper scripts
├── build.sh            # Build script
├── deploy.sh           # Deployment script
└── CMakeLists.txt      # CMake configuration
```

## License

See project repository for license information. 
