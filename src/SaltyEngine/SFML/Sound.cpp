//
// Created by wery_a on 30/11/16.
//

#include "SaltyEngine/SFML/Sound.hpp"

namespace SaltyEngine {
    namespace SFML {

        Sound::Sound() {

        }

        Sound::Sound(sf::SoundBuffer &buffer) {
            m_buffer = buffer;
            setBuffer(m_buffer);
        }

        bool Sound::LoadFromFile(const std::string &filename) {
            if (!m_buffer.loadFromFile(filename)) {
                return false;
            }
            setBuffer(m_buffer);
            return true;
        }

        Sound::~Sound() {

        }

        void Sound::Play() {
            play();
        }

        void Sound::Pause() {
            pause();
        }

        void Sound::Stop() {
            stop();
        }

        ::SaltyEngine::Sound::Status Sound::GetStatus() const {
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

        void Sound::SetLoop(bool loop) {
            setLoop(loop);
        }

        bool Sound::GetLoop() const {
            return getLoop();
        }

        void Sound::SetVolume(float volume) {
            setVolume(volume);
        }

        float Sound::GetVolume() const {
            return getVolume();
        }

        ::SaltyEngine::Sound::ISound* Sound::Get() const {
            return new Sound(m_buffer);
        }
    }
}