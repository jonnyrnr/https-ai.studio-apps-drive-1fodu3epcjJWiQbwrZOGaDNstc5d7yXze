#pragma once

#include <string>
#include <JuceHeader.h>

//==============================================================================
/*
    OSINTManager - Manages integration with Python OSINT tools
    Provides interface to theHarvester and sherlock-project
*/
class OSINTManager
{
public:
    OSINTManager();
    ~OSINTManager();
    
    // Run theHarvester on a target domain
    juce::String runTheHarvester(const std::string& target);
    
    // Run Sherlock on a target username
    juce::String runSherlock(const std::string& username);
    
private:
    juce::String executeCommand(const std::string& command);
    juce::String getPythonPath();
    bool checkPythonEnvironment();
    
    juce::String pythonPath;
    bool pythonAvailable;
};
