//
// Created by wery_a on 30/11/16.
//

#include "SaltyEngine/SFML/Music.hpp"

namespace SaltyEngine {
    namespace SFML {

        Music::Music() {

        }

        bool Music::LoadFromFile(const std::string &filename) {
            return openFromFile(filename);
        }

        Music::~Music() {

        }

        void Music::Play() {
            play();
        }

        void Music::Pause() {
            pause();
        }

        void Music::Stop() {
            stop();
        }

        ::SaltyEngine::Sound::Status Music::GetStatus() const {
            switch (getStatus()) {
                case sf::SoundSource::Status::Paused:
                    return ::SaltyEngine::Sound::Status::Paused;
                case sf::SoundSource::Status::Stopped:
                    return ::SaltyEngine::Sound::Status::Stopped;
                case sf::SoundSource::Status::Playing:
                    return ::SaltyEngine::Sound::Status::Playing;
            }
            return ::SaltyEngine::Sound::Status::Stopped;
        }

        void Music::SetLoop(bool loop) {
            setLoop(loop);
        }

        bool Music::GetLoop() const {
            return getLoop();
        }

        void Music::SetVolume(float volume) {
            setVolume(volume);
        }

        float Music::GetVolume() const {
            return getVolume();
        }

        ::SaltyEngine::Sound::ISound const * Music::Get() const {
            return this;
        }
    }
}