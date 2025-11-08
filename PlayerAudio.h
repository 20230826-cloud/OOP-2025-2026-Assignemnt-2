#pragma once
#include <JuceHeader.h>

class PlayerAudio
{
public:
    PlayerAudio();
    ~PlayerAudio();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    bool loadFile(const juce::File& file);
    void play();
    void pause();
    void stop();
    void setGain(float gain);
    void setPosition(double pos);
    double getPosition() const;
    double getLength() const;


    void toggleMute();
    bool isMuted() const { return isMute; }
    void setLooping(bool shouldLoop);
    bool isLooping() const { return looping; }


    void jumpForward(double seconds);
    void jumpBackward(double seconds);
    juce::String getCurrentFileName() const { return currentFileName; }
    bool isPlaying() const { return transportSource.isPlaying(); }
    bool isSourcePlaying() const { return transportSource.isPlaying() || waitingForLoop; }


    void setSpeed(double ratio);


    juce::AudioSource* getOutputSource() { return &resamplingSource; }


private:
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resamplingSource;

    bool isMute = false;
    float previousVolume = 0.5f;
    bool looping = false;
    juce::String currentFileName;
    bool waitingForLoop = false;
    double loopCheckPosition = 0.0;
};