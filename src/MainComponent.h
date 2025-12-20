#pragma once

#include <JuceHeader.h>
#include "OSINTManager.h"

//==============================================================================
/*
    MainComponent - The main GUI component for Swampify
    Integrates OSINT tools (theHarvester, sherlock-project) with JUCE UI
*/
class MainComponent : public juce::Component
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // UI Components
    juce::TextEditor targetInput;
    juce::Label targetLabel;
    juce::TextButton harvesterButton;
    juce::TextButton sherlockButton;
    juce::TextEditor resultsDisplay;
    juce::Label resultsLabel;
    juce::Label statusLabel;
    
    // OSINT Manager
    std::unique_ptr<OSINTManager> osintManager;
    
    // Button callbacks
    void runHarvester();
    void runSherlock();
    void updateResults(const juce::String& results);
    void updateStatus(const juce::String& status);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
