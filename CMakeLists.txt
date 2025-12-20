cmake_minimum_required(VERSION 3.21)
project(Swampify VERSION 0.1.0)

# Production build configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Production compiler flags
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
    add_compile_definitions(NDEBUG)
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(JUCE_ENABLE_MODULE_SOURCE_GROUPS ON CACHE BOOL "" FORCE)
FetchContent_Declare(
 juce
 GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
 GIT_TAG 7.0.11
)
FetchContent_MakeAvailable(juce)

# Add JUCE GUI application target
juce_add_gui_app(Swampify
    PRODUCT_NAME "Swampify"
    COMPANY_NAME "SwampifyDev"
    BUNDLE_ID "com.swampify.app"
    VERSION 0.1.0)

# Add source files
target_sources(Swampify PRIVATE
    src/Main.cpp
    src/MainComponent.cpp
    src/MainComponent.h
    src/OSINTManager.cpp
    src/OSINTManager.h)

# Link JUCE modules
target_link_libraries(Swampify PRIVATE
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_core
    juce::juce_data_structures
    juce::juce_events
    juce::juce_graphics)

# Set compile definitions
target_compile_definitions(Swampify PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:Swampify,JUCE_PRODUCT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:Swampify,JUCE_VERSION>")

# Install configuration for production deployment
install(TARGETS Swampify
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)