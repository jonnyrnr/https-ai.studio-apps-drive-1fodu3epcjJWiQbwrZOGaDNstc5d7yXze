#include "OSINTManager.h"
#include <cstdlib>
#include <array>
#include <memory>
#include <sstream>
#include <regex>

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

std::string OSINTManager::sanitizeInput(const std::string& input)
{
    // Remove potentially dangerous characters for shell commands
    std::string sanitized = input;
    std::regex dangerousChars("[;&|`$(){}\\[\\]<>'\"]");
    sanitized = std::regex_replace(sanitized, dangerousChars, "");
    
    // Trim whitespace
    sanitized.erase(0, sanitized.find_first_not_of(" \t\n\r"));
    sanitized.erase(sanitized.find_last_not_of(" \t\n\r") + 1);
    
    return sanitized;
}

std::string OSINTManager::buildCommand(const std::string& tool, const std::string& args)
{
    juce::File venvActivate("venv/bin/activate");
    std::ostringstream command;
    
    if (venvActivate.exists())
    {
        command << "source venv/bin/activate && " << tool << " " << args << " 2>&1";
    }
    else
    {
        command << tool << " " << args << " 2>&1";
    }
    
    return command.str();
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
    
    // Sanitize input to prevent command injection
    std::string sanitizedTarget = sanitizeInput(target);
    
    if (sanitizedTarget.empty())
    {
        return "Error: Invalid target domain provided.";
    }
    
    // Build command with sanitized input
    std::string args = "-d " + sanitizedTarget + " -b google,bing";
    std::string command = buildCommand("theHarvester", args);
    
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
    
    // Sanitize input to prevent command injection
    std::string sanitizedUsername = sanitizeInput(username);
    
    if (sanitizedUsername.empty())
    {
        return "Error: Invalid username provided.";
    }
    
    // Build command with sanitized input
    std::string command = buildCommand("sherlock", sanitizedUsername);
    
    juce::String results = executeCommand(command);
    
    if (results.isEmpty())
    {
        return "No results returned. Ensure sherlock-project is installed in the virtual environment.";
    }
    
    return results;
}
