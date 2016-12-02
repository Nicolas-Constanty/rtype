//
// Created by wery_a on 30/11/16.
//

#ifndef RTYPE_ISOUND_HPP
#define RTYPE_ISOUND_HPP

namespace SaltyEngine {
    namespace Sound {
        enum  	Status {
            Stopped,
            Paused,
            Playing
        };

        class ISound {
        public:
            virtual ~ISound() {};

            virtual bool    LoadFromFile(const std::string &) = 0;

            virtual void    Play(void) = 0;
            virtual void    Pause(void) = 0;
            virtual void    Stop(void) = 0;
            virtual Status  GetStatus(void) const = 0;

            virtual void    SetLoop(bool) = 0;
            virtual bool    GetLoop(void) const = 0;

            virtual void    SetVolume(float) = 0;
            virtual float   GetVolume(void) const = 0;
        };
    }
}

#endif //RTYPE_ISOUND_HPP
