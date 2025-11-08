#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlayerGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::Timer
{
public:
    PlayerGUI();
    ~PlayerGUI();

    void resized() override;
    void paint(juce::Graphics& g) override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();


    PlayerAudio* getAudioSource() { return &playerAudio; }



private:
    PlayerAudio playerAudio;



    juce::TextButton loadButton{ "Load File" };
    juce::TextButton playPauseButton{ "Play" };
    juce::TextButton stopButton{ "Stop" };
    juce::TextButton loopButton{ "Loop: Off" };
    juce::TextButton muteButton{ "Mute" };
    juce::TextButton jumpBack10sButton{ "«10s" };
    juce::TextButton jumpForward10sButton{ "10s»" };
    juce::Slider volumeSlider;
    juce::Slider positionSlider;
    juce::Slider speedSlider;
    juce::Label titleLabel;
    juce::Label timeLabel;
    juce::Label fileNameLabel;
    juce::Label volumeLabel;
    juce::Label positionLabel;
    juce::Label speedLabel;
    std::unique_ptr<juce::FileChooser> fileChooser;

    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void timerCallback() override;

    void updateUI();
    juce::String formatTime(double seconds);
};