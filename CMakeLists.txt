cmake_minimum_required(VERSION 3.21)
project(Swampify VERSION 0.1.0)

include(FetchContent)
set(JUCE_ENABLE_MODULE_SOURCE_GROUPS ON CACHE BOOL "" FORCE)
FetchContent_Declare(
 juce
 GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
 GIT_TAG 7.0.11
)
FetchContent_MakeAvailable(juce)
