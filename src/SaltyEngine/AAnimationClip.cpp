//
// Created by nicolas-constanty on 18/12/16.
//


#include "SaltyEngine/AAnimationClip.hpp"

namespace SaltyEngine
{
    AAnimationClip::AAnimationClip(const std::string &name, int frameRate, AnimationConstants::WrapMode mode) :
            Object(name),
            m_frameRate(frameRate),
            m_wrapMode(mode) {}

    AnimationConstants::WrapMode AAnimationClip::GetWrapMode() const {
        return (m_wrapMode);
    }

    void AAnimationClip::SetWrapMode(AnimationConstants::WrapMode wrapMode) {
        m_wrapMode = wrapMode;
    }

    double AAnimationClip::GetFrameRate() const {
        return m_frameRate;
    }

    void AAnimationClip::SetFrameRate(int frameRate) {
        m_frameRate = frameRate;
    }

    void AAnimationClip::OnAnimEnd() {
        if (m_event_end != nullptr)
            m_event_end();
    }
}