#include <JuceHeader.h>
#include "MainComponent.h"

class AudioPlayerApp : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return "Professional Audio Player"; }
    const juce::String getApplicationVersion() override { return "2.0"; }

    void initialise(const juce::String&) override
    {
        mainWindow = std::make_unique<MainWindow>(getApplicationName());
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

private:
    class MainWindow : public juce::DocumentWindow
    {
    public:
        MainWindow(juce::String name)
            : DocumentWindow(name,
                juce::Colour(0xff2d2d2d),
                DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(new MainComponent(), true);
            setResizable(true, true);

            
            setResizeLimits(600, 400, 1200, 800);
            centreWithSize(800, 600);
            

            setVisible(true);
        }

        void closeButtonPressed() override
        {
            juce::JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
    };

    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(AudioPlayerApp)