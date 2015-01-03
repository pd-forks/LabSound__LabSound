//
//  SupersawNode.h
//
// Copyright (c) 2003-2013 Nick Porcino, All rights reserved.
// License is MIT: http://opensource.org/licenses/MIT

#ifndef __LabSound__SupersawNode__
#define __LabSound__SupersawNode__

#include "AudioContext.h"
#include "AudioNode.h"
#include "AudioParam.h"

namespace LabSound {
    using namespace WebCore;

    class SupersawNode : public AudioNode {
    public:
		static PassRefPtr<SupersawNode> create(std::shared_ptr<AudioContext> context, float sampleRate)
		{
			return adoptRef(new SupersawNode(context, sampleRate));
		}

		std::shared_ptr<AudioParam> attack()  const;
		std::shared_ptr<AudioParam> decay()   const;
		std::shared_ptr<AudioParam> sustain() const;
		std::shared_ptr<AudioParam> release() const;

        std::shared_ptr<AudioParam> sawCount()  const;
        std::shared_ptr<AudioParam> frequency() const;
        std::shared_ptr<AudioParam> detune()    const;

		void noteOn();
		void noteOff();

        void update(); // call if sawCount is changed. CBB: update automatically

    private:
		SupersawNode(std::shared_ptr<AudioContext>, float sampleRate);

        // Satisfy the AudioNode interface
        virtual void process(size_t);
        virtual void reset() { /*m_currentSampleFrame = 0;*/ }
        virtual double tailTime() const OVERRIDE { return 0; }
        virtual double latencyTime() const OVERRIDE { return 0; }
        virtual bool propagatesSilence() const OVERRIDE;
        // ^

        class Data;
        Data* _data;
    };
}

#endif
