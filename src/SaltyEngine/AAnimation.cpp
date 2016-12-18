//
// Created by nicolas-constanty on 18/12/16.
//

#include "SaltyEngine/AAnimation.hpp"

namespace SaltyEngine
{
    AAnimation::AAnimation(GameObject *const obj, bool playAuto, AnimationConstants::WrapMode mode) :
            SaltyBehaviour(obj),
            m_playAuto(playAuto),
            m_wrapMode(mode)
    {
    }

    void AAnimation::PlayQueued(std::string const &animName) {
        m_queuedAnims.push(animName);
    }

    void AAnimation::Stop() {
        m_isPlaying = false;
    }

    AnimationConstants::WrapMode AAnimation::GetWrapMode() const {
        return m_wrapMode;
    }

    void AAnimation::SetWrapMode(AnimationConstants::WrapMode mode) {
        m_wrapMode = mode;
    }

    bool AAnimation::IsPlaying() const {
        return m_isPlaying;
    }
}