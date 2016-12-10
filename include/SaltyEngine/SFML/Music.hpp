//
// Created by wery_a on 30/11/16.
//

#ifndef RTYPE_MUSIC_HPP
#define RTYPE_MUSIC_HPP

#include <SFML/Audio.hpp>
#include "SaltyEngine/ISound.hpp"

namespace SaltyEngine {
    namespace SFML {
        class Music: public ::SaltyEngine::Sound::ISound, private sf::Music {
        public:
            Music();
            virtual ~Music();

            bool    LoadFromFile(const std::string &filename);

            void    Play(void);
            void    Pause(void);
            void    Stop(void);
            ::SaltyEngine::Sound::Status  GetStatus(void) const;

            void    SetLoop(bool);
            bool    GetLoop(void) const;

            void    SetVolume(float);
            float   GetVolume(void) const;

            ::SaltyEngine::Sound::ISound const *Get() const;
        };
    }
}

#endif //RTYPE_MUSIC_HPP
