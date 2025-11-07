#include "MainComponent.h"



MainComponent::MainComponent()
{
    
    addAndMakeVisible(playerGUI1);
    addAndMakeVisible(playerGUI2);

    
    mixerSource.addInputSource(playerGUI1.getAudioSource()->getTransportSource(), false);
    mixerSource.addInputSource(playerGUI2.getAudioSource()->getTransportSource(), false);

    
    

    
    setSize(800, 600);
    setAudioChannels(0, 2);

    
}

MainComponent::~MainComponent()
{
    
    mixerSource.removeAllInputs();
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    mixerSource.releaseResources();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff1e1e1e));
}

void MainComponent::resized()
{
    auto area = getLocalBounds();

    
    

    
    playerGUI1.setBounds(area.removeFromTop(area.getHeight() / 2));
    playerGUI2.setBounds(area); 
}


