#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Initialize OSINT Manager
    osintManager = std::make_unique<OSINTManager>();
    
    // Setup target input
    targetLabel.setText("Target (domain/username):", juce::dontSendNotification);
    targetLabel.attachToComponent(&targetInput, true);
    addAndMakeVisible(targetLabel);
    
    targetInput.setMultiLine(false);
    targetInput.setReturnKeyStartsNewLine(false);
    targetInput.setText("example.com");
    addAndMakeVisible(targetInput);
    
    // Setup theHarvester button
    harvesterButton.setButtonText("Run theHarvester");
    harvesterButton.onClick = [this] { runHarvester(); };
    addAndMakeVisible(harvesterButton);
    
    // Setup Sherlock button
    sherlockButton.setButtonText("Run Sherlock");
    sherlockButton.onClick = [this] { runSherlock(); };
    addAndMakeVisible(sherlockButton);
    
    // Setup results display
    resultsLabel.setText("Results:", juce::dontSendNotification);
    addAndMakeVisible(resultsLabel);
    
    resultsDisplay.setMultiLine(true);
    resultsDisplay.setReadOnly(true);
    resultsDisplay.setScrollbarsShown(true);
    resultsDisplay.setCaretVisible(false);
    addAndMakeVisible(resultsDisplay);
    
    // Setup status label
    statusLabel.setText("Ready", juce::dontSendNotification);
    statusLabel.setColour(juce::Label::textColourId, juce::Colours::green);
    addAndMakeVisible(statusLabel);
    
    setSize(800, 600);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Swampify - OSINT Content Research Tool", getLocalBounds().removeFromTop(40),
               juce::Justification::centred, true);
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds().reduced(20);
    bounds.removeFromTop(50); // Title space
    
    // Target input area
    auto inputArea = bounds.removeFromTop(40);
    targetInput.setBounds(inputArea.removeFromLeft(getWidth() - 240).reduced(5));
    
    bounds.removeFromTop(10);
    
    // Buttons area
    auto buttonArea = bounds.removeFromTop(40);
    harvesterButton.setBounds(buttonArea.removeFromLeft(200).reduced(5));
    buttonArea.removeFromLeft(10);
    sherlockButton.setBounds(buttonArea.removeFromLeft(200).reduced(5));
    
    bounds.removeFromTop(10);
    
    // Results label
    resultsLabel.setBounds(bounds.removeFromTop(30));
    
    // Results display
    auto resultsArea = bounds.removeFromBottom(40);
    resultsDisplay.setBounds(bounds.reduced(5));
    
    // Status at bottom
    statusLabel.setBounds(resultsArea);
}

void MainComponent::runHarvester()
{
    updateStatus("Running theHarvester...");
    auto target = targetInput.getText();
    
    if (target.isEmpty())
    {
        updateStatus("Error: Please enter a target domain");
        return;
    }
    
    auto results = osintManager->runTheHarvester(target.toStdString());
    updateResults(results);
    updateStatus("theHarvester completed");
}

void MainComponent::runSherlock()
{
    updateStatus("Running Sherlock...");
    auto target = targetInput.getText();
    
    if (target.isEmpty())
    {
        updateStatus("Error: Please enter a target username");
        return;
    }
    
    auto results = osintManager->runSherlock(target.toStdString());
    updateResults(results);
    updateStatus("Sherlock completed");
}

void MainComponent::updateResults(const juce::String& results)
{
    resultsDisplay.setText(results);
}

void MainComponent::updateStatus(const juce::String& status)
{
    statusLabel.setText(status, juce::dontSendNotification);
    
    if (status.contains("Error"))
        statusLabel.setColour(juce::Label::textColourId, juce::Colours::red);
    else if (status.contains("Running"))
        statusLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    else
        statusLabel.setColour(juce::Label::textColourId, juce::Colours::green);
}
