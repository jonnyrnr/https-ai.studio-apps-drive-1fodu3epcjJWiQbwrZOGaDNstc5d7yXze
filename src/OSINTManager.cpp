#include "OSINTManager.h"
#include <cstdlib>
#include <array>
#include <memory>

OSINTManager::OSINTManager()
    : pythonAvailable(false)
{
    pythonPath = getPythonPath();
    pythonAvailable = checkPythonEnvironment();
}

OSINTManager::~OSINTManager()
{
}

juce::String OSINTManager::getPythonPath()
{
    // Check for venv first, then system python
    juce::File venvPython("venv/bin/python3");
    if (venvPython.existsAsFile())
        return venvPython.getFullPathName();
    
    return "python3";
}

bool OSINTManager::checkPythonEnvironment()
{
    auto result = executeCommand(pythonPath.toStdString() + " --version");
    return result.isNotEmpty() && result.contains("Python");
}

juce::String OSINTManager::executeCommand(const std::string& command)
{
    std::array<char, 128> buffer;
    std::string result;
    
#ifdef _WIN32
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);
#else
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
#endif
    
    if (!pipe)
    {
        return "Error: Failed to execute command";
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    
    return juce::String(result);
}

juce::String OSINTManager::runTheHarvester(const std::string& target)
{
    if (!pythonAvailable)
    {
        return "Error: Python environment not available. Please run deploy.sh first.";
    }
    
    // Check if venv is available
    juce::File venvActivate("venv/bin/activate");
    std::string command;
    
    if (venvActivate.exists())
    {
        command = "source venv/bin/activate && theHarvester -d " + target + " -b google,bing 2>&1";
    }
    else
    {
        command = "theHarvester -d " + target + " -b google,bing 2>&1";
    }
    
    juce::String results = executeCommand(command);
    
    if (results.isEmpty())
    {
        return "No results returned. Ensure theHarvester is installed in the virtual environment.";
    }
    
    return results;
}

juce::String OSINTManager::runSherlock(const std::string& username)
{
    if (!pythonAvailable)
    {
        return "Error: Python environment not available. Please run deploy.sh first.";
    }
    
    // Check if venv is available
    juce::File venvActivate("venv/bin/activate");
    std::string command;
    
    if (venvActivate.exists())
    {
        command = "source venv/bin/activate && sherlock " + username + " 2>&1";
    }
    else
    {
        command = "sherlock " + username + " 2>&1";
    }
    
    juce::String results = executeCommand(command);
    
    if (results.isEmpty())
    {
        return "No results returned. Ensure sherlock-project is installed in the virtual environment.";
    }
    
    return results;
}
