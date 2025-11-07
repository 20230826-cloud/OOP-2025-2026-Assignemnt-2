#include "PlayerAudio.h"

PlayerAudio::PlayerAudio()
{
    formatManager.registerBasicFormats();
}

PlayerAudio::~PlayerAudio()
{
}

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource.get() != nullptr)
    {
        transportSource.getNextAudioBlock(bufferToFill);

        
        if (looping && transportSource.isPlaying())
        {
            double currentPosition = getPosition();
            double totalLength = getLength();

            
            if (totalLength > 0 && currentPosition >= totalLength - 0.1)
            {
                transportSource.setPosition(0.0);
                
                if (!transportSource.isPlaying())
                {
                    transportSource.start();
                }
            }
        }
    }
    else
    {
        bufferToFill.clearActiveBufferRegion();
    }
}

void PlayerAudio::releaseResources()
{
    transportSource.releaseResources();
}

bool PlayerAudio::loadFile(const juce::File& file)
{
    if (file.existsAsFile())
    {
        if (auto* reader = formatManager.createReaderFor(file))
        {
            transportSource.stop();
            transportSource.setSource(nullptr);
            readerSource.reset();

            readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
            transportSource.setSource(readerSource.get(),
                0, 
                nullptr,
                reader->sampleRate);
            currentFileName = file.getFileName();

            
            waitingForLoop = false;
            loopCheckPosition = 0.0;

            return true;
        }
    }
    return false;
}

void PlayerAudio::play()
{
    transportSource.start();
    waitingForLoop = false;
}

void PlayerAudio::pause()
{
    transportSource.stop();
}

void PlayerAudio::stop()
{
    transportSource.stop();
    transportSource.setPosition(0.0);
    waitingForLoop = false;
}

void PlayerAudio::setGain(float gain)
{
    if (!isMute)
    {
        transportSource.setGain(gain);
        previousVolume = gain;
    }
}

void PlayerAudio::setPosition(double pos)
{
    transportSource.setPosition(pos);
    loopCheckPosition = pos;
}

double PlayerAudio::getPosition() const
{
    return transportSource.getCurrentPosition();
}

double PlayerAudio::getLength() const
{
    if (readerSource && readerSource->getAudioFormatReader())
    {
        auto* reader = readerSource->getAudioFormatReader();
        return reader->lengthInSamples / reader->sampleRate;
    }
    return 0.0;
}

void PlayerAudio::toggleMute()
{
    isMute = !isMute;

    if (isMute)
    {
        previousVolume = transportSource.getGain();
        transportSource.setGain(0.0f);
    }
    else
    {
        transportSource.setGain(previousVolume);
    }
}

void PlayerAudio::setLooping(bool shouldLoop)
{
    looping = shouldLoop;

    
    if (looping && !transportSource.isPlaying())
    {
        double currentPosition = getPosition();
        double totalLength = getLength();

        if (totalLength > 0 && currentPosition >= totalLength - 0.1)
        {
            transportSource.setPosition(0.0);
        }
    }
}

void PlayerAudio::jumpForward(double seconds)
{
    double newPos = getPosition() + seconds;
    double maxPos = getLength();
    setPosition(juce::jmin(newPos, maxPos));
}

void PlayerAudio::jumpBackward(double seconds)
{
    double newPos = getPosition() - seconds;
    setPosition(juce::jmax(newPos, 0.0));
}