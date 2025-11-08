#include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
{

    juce::Array<juce::Button*> buttons = {
        &loadButton, &playPauseButton, &stopButton,
        &loopButton, &muteButton, &jumpBack10sButton, &jumpForward10sButton
    };

    for (auto* btn : buttons)
    {
        btn->addListener(this);
        btn->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff4a4a4a));
        btn->setColour(juce::TextButton::textColourOffId, juce::Colours::white);
        btn->setColour(juce::TextButton::buttonOnColourId, juce::Colours::lightblue);
        addAndMakeVisible(btn);
    }


    playPauseButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    loadButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff6a6a6a));


    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 25);
    volumeSlider.setColour(juce::Slider::thumbColourId, juce::Colours::lightblue);
    volumeSlider.setColour(juce::Slider::trackColourId, juce::Colour(0xff5a5a5a));
    volumeSlider.setColour(juce::Slider::backgroundColourId, juce::Colour(0xff3a3a3a));
    volumeSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    volumeSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    volumeSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(volumeSlider);


    speedSlider.setRange(0.5, 2.0, 0.01);
    speedSlider.setValue(1.0);
    speedSlider.addListener(this);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 25);
    speedSlider.setColour(juce::Slider::thumbColourId, juce::Colours::lightblue);
    speedSlider.setColour(juce::Slider::trackColourId, juce::Colour(0xff5a5a5a));
    speedSlider.setColour(juce::Slider::backgroundColourId, juce::Colour(0xff3a3a3a));
    speedSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    speedSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    speedSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(speedSlider);


    positionSlider.setRange(0.0, 1.0, 0.001);
    positionSlider.addListener(this);
    positionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    positionSlider.setColour(juce::Slider::thumbColourId, juce::Colours::red);
    positionSlider.setColour(juce::Slider::trackColourId, juce::Colour(0xff6a6a6a));
    positionSlider.setColour(juce::Slider::backgroundColourId, juce::Colour(0xff4a4a4a));
    addAndMakeVisible(positionSlider);


    titleLabel.setText("Professional Audio Player", juce::dontSendNotification);
    titleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    titleLabel.setFont(juce::Font(24.0f, juce::Font::bold));
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    fileNameLabel.setText("No file loaded", juce::dontSendNotification);
    fileNameLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    fileNameLabel.setFont(juce::Font(16.0f));
    fileNameLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(fileNameLabel);

    timeLabel.setText("00:00 / 00:00", juce::dontSendNotification);
    timeLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    timeLabel.setFont(juce::Font(14.0f, juce::Font::bold));
    timeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(timeLabel);

    volumeLabel.setText("Volume:", juce::dontSendNotification);
    volumeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    volumeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(volumeLabel);


    speedLabel.setText("Speed:", juce::dontSendNotification);
    speedLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    speedLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(speedLabel);

    positionLabel.setText("Progress:", juce::dontSendNotification);
    positionLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    positionLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(positionLabel);


    startTimer(100);
}

PlayerGUI::~PlayerGUI()
{
    stopTimer();
}

void PlayerGUI::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerAudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerGUI::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playerAudio.getNextAudioBlock(bufferToFill);
}

void PlayerGUI::releaseResources()
{
    playerAudio.releaseResources();
}

void PlayerGUI::paint(juce::Graphics& g)
{

    g.setGradientFill(juce::ColourGradient(
        juce::Colour(0xff3a3a3a), 0, 0,
        juce::Colour(0xff2a2a2a), 0, getHeight(), false));
    g.fillAll();


    g.setColour(juce::Colour(0xff5a5a5a));
    g.drawRect(getLocalBounds(), 2);


    auto mainArea = getLocalBounds().reduced(20, 20);
    g.setColour(juce::Colour(0xff4a4a4a).withAlpha(0.3f));
    g.fillRoundedRectangle(mainArea.toFloat(), 10.0f);

    g.setColour(juce::Colour(0xff6a6a6a));
    g.drawRoundedRectangle(mainArea.toFloat(), 10.0f, 2.0f);


    if (playerAudio.isLooping())
    {
        g.setColour(juce::Colours::lightgreen.withAlpha(0.2f));
        g.fillRect(getLocalBounds());

        g.setColour(juce::Colours::lightgreen);
        g.setFont(juce::Font(16.0f, juce::Font::bold));
        g.drawText("LOOP ACTIVE", getLocalBounds().removeFromTop(30),
            juce::Justification::centred);
    }
}

// *** الدالة الوحيدة التي تم تغييرها هي هذه ***
void PlayerGUI::resized()
{
    // المساحة المتاحة هي 260 بكسل (300 - 40 padding)
    auto area = getLocalBounds().reduced(20);

    // 1. العنوان: 40 بكسل
    titleLabel.setBounds(area.removeFromTop(40));

    // 2. اسم الملف: 30 بكسل
    fileNameLabel.setBounds(area.removeFromTop(30));

    // 3. شريط التقدم: 50 بكسل
    auto progressArea = area.removeFromTop(50);
    positionLabel.setBounds(progressArea.removeFromTop(20)); // ملصق أصغر
    positionSlider.setBounds(progressArea.reduced(10, 0));

    // 4. ملصق الوقت: 30 بكسل
    timeLabel.setBounds(area.removeFromTop(30));

    // 5. الأزرار: 50 بكسل
    auto controlRow1 = area.removeFromTop(50);
    int buttonWidth = controlRow1.getWidth() / 7;
    loadButton.setBounds(controlRow1.removeFromLeft(buttonWidth).reduced(5)); // تقليل الحشو
    playPauseButton.setBounds(controlRow1.removeFromLeft(buttonWidth).reduced(5));
    stopButton.setBounds(controlRow1.removeFromLeft(buttonWidth).reduced(5));
    loopButton.setBounds(controlRow1.removeFromLeft(buttonWidth).reduced(5));
    muteButton.setBounds(controlRow1.removeFromLeft(buttonWidth).reduced(5));
    jumpBack10sButton.setBounds(controlRow1.removeFromLeft(buttonWidth).reduced(5));
    jumpForward10sButton.setBounds(controlRow1.removeFromLeft(buttonWidth).reduced(5));

    // 6. أشرطة التمرير: 60 بكسل (المساحة المتبقية)
    auto slidersArea = area; // نأخذ ما تبقى من المساحة
    auto volumeArea = slidersArea.removeFromLeft(slidersArea.getWidth() / 2);
    auto speedArea = slidersArea;

    volumeLabel.setBounds(volumeArea.removeFromTop(25).reduced(10, 0));
    volumeSlider.setBounds(volumeArea.reduced(20, 5));

    speedLabel.setBounds(speedArea.removeFromTop(25).reduced(10, 0));
    speedSlider.setBounds(speedArea.reduced(20, 5));
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select audio file",
            juce::File{},
            "*.wav;*.mp3;*.aiff;*.flac");

        fileChooser->launchAsync(juce::FileBrowserComponent::openMode |
            juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file.existsAsFile())
                {
                    if (playerAudio.loadFile(file))
                    {
                        fileNameLabel.setText(file.getFileName(), juce::dontSendNotification);
                        speedSlider.setValue(1.0, juce::sendNotification);
                        updateUI();
                    }
                }
            });
    }
    else if (button == &playPauseButton)
    {
        if (playerAudio.isPlaying())
        {
            playerAudio.pause();
        }
        else
        {
            playerAudio.play();
        }
    }
    else if (button == &stopButton)
    {
        playerAudio.stop();
    }
    else if (button == &loopButton)
    {
        bool currentLoop = playerAudio.isLooping();
        playerAudio.setLooping(!currentLoop);


        if (!currentLoop)
        {
            loopButton.setButtonText("🔁 Loop: On");
            loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightgreen);


            double current = playerAudio.getPosition();
            double total = playerAudio.getLength();
            if (total > 0 && current >= total - 0.1)
            {
                playerAudio.setPosition(0.0);
                if (!playerAudio.isPlaying())
                {
                    playerAudio.play();
                }
            }
        }
        else
        {
            loopButton.setButtonText("➡️ Loop: Off");
            loopButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff4a4a4a));
        }
    }
    else if (button == &muteButton)
    {
        playerAudio.toggleMute();
        muteButton.setButtonText(playerAudio.isMuted() ? "🔇 Unmute" : "🔊 Mute");
        muteButton.setColour(juce::TextButton::buttonColourId,
            playerAudio.isMuted() ? juce::Colours::darkred : juce::Colour(0xff4a4a4a));
    }
    else if (button == &jumpBack10sButton)
    {
        playerAudio.jumpBackward(10.0);
    }
    else if (button == &jumpForward10sButton)
    {
        playerAudio.jumpForward(10.0);
    }

    updateUI();
}
void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
    {
        playerAudio.setGain((float)slider->getValue());
    }
    else if (slider == &positionSlider)
    {
        double newPosition = slider->getValue() * playerAudio.getLength();
        playerAudio.setPosition(newPosition);
    }
    else if (slider == &speedSlider)
    {
        playerAudio.setSpeed(slider->getValue());
    }
}

void PlayerGUI::timerCallback()
{
    updateUI();
}

void PlayerGUI::updateUI()
{

    double current = playerAudio.getPosition();
    double total = playerAudio.getLength();

    timeLabel.setText(formatTime(current) + " / " + formatTime(total), juce::dontSendNotification);

    if (total > 0)
    {
        positionSlider.setValue(current / total, juce::dontSendNotification);


        if (playerAudio.isLooping() && current >= total - 0.1 && total > 1.0)
        {

            playerAudio.setPosition(0.0);
            if (!playerAudio.isPlaying())
            {
                playerAudio.play();
            }
        }
    }


    bool isPlaying = playerAudio.isPlaying();
    playPauseButton.setButtonText(isPlaying ? "Pause" : "Play");


    bool isLooping = playerAudio.isLooping();
    loopButton.setButtonText(isLooping ? "Loop:On" : "Loop:Off");
    loopButton.setColour(juce::TextButton::buttonColourId,
        isLooping ? juce::Colours::lightgreen : juce::Colour(0xff4a4a4a));


    bool hasAudio = total > 0;
    playPauseButton.setEnabled(hasAudio);
    stopButton.setEnabled(hasAudio);
    loopButton.setEnabled(hasAudio);
    jumpBack10sButton.setEnabled(hasAudio && current > 0);
    jumpForward10sButton.setEnabled(hasAudio && current < total);
    speedSlider.setEnabled(hasAudio);


    if (isLooping && hasAudio)
    {
        positionSlider.setColour(juce::Slider::trackColourId, juce::Colours::lightgreen.withAlpha(0.3f));
    }
    else
    {
        positionSlider.setColour(juce::Slider::trackColourId, juce::Colour(0xff6a6a6a));
    }
}

juce::String PlayerGUI::formatTime(double seconds)
{
    int totalSeconds = static_cast<int>(seconds);
    int mins = totalSeconds / 60;
    int secs = totalSeconds % 60;
    return juce::String::formatted("%d:%02d", mins, secs);
}