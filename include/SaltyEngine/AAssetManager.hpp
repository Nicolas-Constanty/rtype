//
// Created by wery_a on 30/11/16.
//

#ifndef RTYPE_AASSETMANAGER_HPP
#define RTYPE_AASSETMANAGER_HPP

#include <memory>
#include <Common/Singleton.hpp>
#include "SaltyEngine/ISound.hpp"
#include "SaltyEngine/Texture.hpp"
#include "SaltyEngine/Debug.hpp"

namespace SaltyEngine {
    namespace Asset {
        const std::string    ASSET_PATH = "Assets/";
        const std::string    SOUNDS_PATH = ASSET_PATH + "Sounds/";
        const std::string    TEXTURES_PATH = ASSET_PATH + "Textures/";
        const std::string    FONTS_PATH = ASSET_PATH + "Fonts/";

        const std::string    SOUND_EXTENSION = ".ogg";
        const std::string    TEXTURE_EXTENSION = ".png";
        const std::string    FONT_EXTENSION = ".ttf";
    }

    template <class Texture, class Sound = ::SaltyEngine::Sound::ISound>
    class AAssetManager {
    protected:
        AAssetManager() {}
        virtual ~AAssetManager() {}

    protected:
        std::map<std::string, Sound*> m_sounds;
        std::map<std::string, Texture*> m_textures;

    public:
        virtual bool LoadISound(const std::string &name, bool isMusic) = 0;
        bool LoadSound(const std::string &name) {
            return LoadISound(name, false);
        }
        bool LoadMusic(const std::string &name) {
            return LoadISound(name, true);
        }

        virtual bool LoadTexture(const std::string &name) = 0;

    public:
        Sound   *GetSound(const std::string &name) {
            typename std::map<std::string, Sound*>::const_iterator it = m_sounds.find(name);
            if (it == m_sounds.end()) {
                Debug::PrintError("Cannot find sound " + name);
                return nullptr;
            }
            return it->second;
        }

        Texture *GetTexture(const std::string &name) {
            typename std::map<std::string, Texture*>::const_iterator it = m_textures.find(name);
            if (it == m_textures.end()) {
                Debug::PrintError("Cannot find texture " + name);
                return nullptr;
            }
            return it->second;
        }
    };
}

#endif //RTYPE_AASSETMANAGER_HPP
