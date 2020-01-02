// License: BSD 3 Clause
// Copyright (C) 2020, The LabSound Authors. All rights reserved.

#ifndef AudioDestinationMiniaudio_h
#define AudioDestinationMiniaudio_h

#include "LabSound/core/AudioNode.h"
#include "LabSound/core/AudioBus.h"

#include "internal/AudioDestination.h"

#include "miniaudio.h"
#include <iostream>
#include <memory>
#include <cstdlib>

namespace lab {

class AudioDestinationMiniaudio : public AudioDestination
{

public:

    AudioDestinationMiniaudio(AudioIOCallback &, unsigned int numChannels, float sampleRate);
    virtual ~AudioDestinationMiniaudio();

    virtual void start() override;
    virtual void stop() override;

    float sampleRate() const override { return m_sampleRate; }

    void render(int numberOfFrames, void * outputBuffer, void * inputBuffer);
    
    unsigned int channelCount() const { return m_numChannels; }

private:

    void configure();

    AudioIOCallback & m_callback;
    AudioBus m_renderBus = {2, AudioNode::ProcessingSizeInFrames, false};
    std::unique_ptr<AudioBus> m_inputBus;
    unsigned int m_numChannels;
    float m_sampleRate;
    ma_device device;
};

} // namespace lab

#endif // AudioDestinationMiniaudio_h
