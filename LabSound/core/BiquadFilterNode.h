/*
 * Copyright (C) 2011, Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef BiquadFilterNode_h
#define BiquadFilterNode_h

#include "LabSound/core/AudioBasicProcessorNode.h"
#include "LabSound/core/BiquadProcessor.h"

namespace WebCore {

class AudioParam;
    
class BiquadFilterNode : public AudioBasicProcessorNode {
public:
    // These must be defined as in the .idl file and must match those in the BiquadProcessor class.
    enum {
        LOWPASS = 0,
        HIGHPASS = 1,
        BANDPASS = 2,
        LOWSHELF = 3,
        HIGHSHELF = 4,
        PEAKING = 5,
        NOTCH = 6,
        ALLPASS = 7
    };
    
    BiquadFilterNode(float sampleRate);
    
    unsigned short type() { return biquadProcessor()->type(); }
    void setType(unsigned short type, ExceptionCode&);

    std::shared_ptr<AudioParam> frequency() { return biquadProcessor()->parameter1(); }
    std::shared_ptr<AudioParam> q() { return biquadProcessor()->parameter2(); }
    std::shared_ptr<AudioParam> gain() { return biquadProcessor()->parameter3(); }
    std::shared_ptr<AudioParam> detune() { return biquadProcessor()->parameter4(); }

    // Get the magnitude and phase response of the filter at the given
    // set of frequencies (in Hz). The phase response is in radians.
    void getFrequencyResponse(ContextRenderLock&,
                              const std::vector<float>& frequencyHz,
                              std::vector<float>& magResponse,
                              std::vector<float>& phaseResponse);

private:

    BiquadProcessor* biquadProcessor() { return static_cast<BiquadProcessor*>(processor()); }
};

} // namespace WebCore

#endif // BiquadFilterNode_h
