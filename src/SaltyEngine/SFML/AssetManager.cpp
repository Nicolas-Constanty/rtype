//
// Created by wery_a on 30/11/16.
//

#include <SaltyEngine/Debug.hpp>
#include <SaltyEngine/SFML/Music.hpp>
#include <SaltyEngine/SFML/Sound.hpp>
#include <SaltyEngine/SFML/Texture.hpp>
#include "SaltyEngine/SFML/AssetManager.hpp"

namespace SaltyEngine {
    namespace SFML {
        AssetManager::AssetManager(): AAssetManager<::SaltyEngine::SFML::Texture>() {

        }

        AssetManager::~AssetManager() {

        }

        bool AssetManager::LoadISound(const std::string &name, bool isMusic) {
            std::map<std::string, ::SaltyEngine::Sound::ISound*>::const_iterator it = m_sounds.find(name);
            if (it == m_sounds.end()) {
                Debug::PrintWarning("Sound " + name + " already loaded");
                return false;
            }
            ::SaltyEngine::Sound::ISound *sound;
            if (isMusic) {
                sound = new ::SaltyEngine::SFML::Music();
            } else {
                sound = new ::SaltyEngine::SFML::Sound();
            }
            if (!sound->LoadFromFile(path_sounds + name + Asset::SOUND_EXTENSION)) {
                return false;
            }
            m_sounds[name] = sound;
            return true;
        }

        bool AssetManager::LoadTexture(const std::string &name) {
            ::SaltyEngine::SFML::Texture *texture = new SaltyEngine::SFML::Texture();
            if (!texture->loadFromFile(path_textures + name + Asset::TEXTURE_EXTENSION)) {
                Debug::PrintError("Failed to load texture " + name);
                return false;
            }
            m_textures[name] = texture;
            return true;
        }

        ::SaltyEngine::SFML::Sprite * AssetManager::GetSprite(std::string const &name) const {
            typename std::map<std::string, SpriteDefault>::const_iterator it = m_sprites.find(name);
            if (it == m_sprites.end()) {
                if (!LoadSprite(name)) {
                    Debug::PrintError("Cannot find sprite " + name);
                    return nullptr;
                }
            }
            ::SaltyEngine::SFML::Texture *texture = GetTexture(it->second.texture);
            if (texture == nullptr) {
                return nullptr;
            }
            return new ::SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(it->second.position,it->second.size));
        }
    }
}