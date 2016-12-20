//
// Created by wery_a on 30/11/16.
//

#ifndef RTYPE_SOUND_HPP
#define RTYPE_SOUND_HPP

#include <SFML/Audio.hpp>
#include "SaltyEngine/ISound.hpp"

namespace SaltyEngine {
    namespace SFML {
        class Sound: public ::SaltyEngine::Sound::ISound, private sf::Sound {
        public:
            Sound();
            virtual ~Sound();

            bool    LoadFromFile(const std::string &filename);

            void    Play(void);
            void    Pause(void);
            void    Stop(void);
            ::SaltyEngine::Sound::Status  GetStatus(void) const;

            void    SetLoop(bool loop);
            bool    GetLoop(void) const;

            void    SetVolume(float volume);
            float   GetVolume(void) const;

            ::SaltyEngine::Sound::ISound *Get();

        private:
            sf::SoundBuffer *m_buffer;
        };
    }
}

#endif //RTYPE_SOUND_HPP
