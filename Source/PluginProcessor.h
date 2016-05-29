/*
  ==============================================================================

    A simple delay example with time and feedback knobs

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class FftapeDelayAudioProcessor  : public AudioProcessor,
                                   public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    FftapeDelayAudioProcessor();
    ~FftapeDelayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    void fillDelayBuffer (AudioSampleBuffer& buffer, const int channelIn, const int channelOut, const int64 writePos);

    void fetchFromDelayBuffer (AudioSampleBuffer& buffer, const int channelIn, const int channelOut, const int64 readPos);

    void feedbackDelayBuffer (AudioSampleBuffer& buffer, const int channelIn, const int channelOut, const int64 writePos);

    void parameterChanged (const String &parameterID, float newValue) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    AudioProcessorValueTreeState& getValueTreeState();

    static String paramGain;
    static String paramTime;
    static String paramFeedback;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FftapeDelayAudioProcessor)

    ScopedPointer<AudioProcessorValueTreeState> mState;
    ScopedPointer<UndoManager>                  mUndoManager;

    AudioSampleBuffer                           mDelayBuffer;

    float mInputGain;
    float mLastInputGain;
    float mTime;
    float mFeedbackGain;
    float mLastFeedbackGain;

    int64 mWritePos;
    double mSampleRate;
};


#endif  // PLUGINPROCESSOR_H_INCLUDED