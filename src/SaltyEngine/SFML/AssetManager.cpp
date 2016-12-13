//
// Created by wery_a on 30/11/16.
//

#include <SaltyEngine/SFML/Music.hpp>
#include <SaltyEngine/SFML/Sound.hpp>
#include <SaltyEngine/SFML/Texture.hpp>
#include "SaltyEngine/SFML/AssetManager.hpp"
#include <SaltyEngine/Debug.hpp>

namespace SaltyEngine {
    namespace SFML {
        AssetManager::AssetManager(): AAssetManager<::SaltyEngine::SFML::Texture, ::SaltyEngine::SFML::Sprite>() {

        }

        AssetManager::~AssetManager() {

        }

        bool AssetManager::LoadISound(std::string const &name, bool isMusic) {
            if (m_sounds.find(name) != m_sounds.end()) {
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
                Debug::PrintWarning("Failed to load sound " + name);
                return false;
            }
            Debug::PrintSuccess("Sound " + name + " was successfuly loaded");
            m_sounds[name] = std::unique_ptr<::SaltyEngine::Sound::ISound>(sound);
            return true;
        }

        bool AssetManager::LoadTexture(std::string const &name) {
            if (m_textures.find(name) != m_textures.end()) {
                Debug::PrintWarning("Texture " + name + " already loaded");
                return false;
            }
            ::SaltyEngine::SFML::Texture *texture = new ::SaltyEngine::SFML::Texture();
            if (!texture->loadFromFile(path_textures + name + Asset::TEXTURE_EXTENSION)) {
                Debug::PrintWarning("Failed to load texture " + name);
                return false;
            }
            Debug::PrintSuccess("Texture " + name + " was successfuly loaded");
            m_textures[name] = std::unique_ptr<::SaltyEngine::SFML::Texture>(texture);
            return true;
        }

        ::SaltyEngine::SFML::Sprite * AssetManager::GetSprite(std::string const &name) {
            typename std::map<std::string, SpriteDefault>::const_iterator it = m_sprites.find(name);
            if (it == m_sprites.end()) {
                if (!LoadSprite(name)) {
                    Debug::PrintWarning("Cannot find sprite " + name);
                    return nullptr;
                }
                it = m_sprites.find(name);
                if (it == m_sprites.end()) {
                    return nullptr;
                }
            }
            ::SaltyEngine::SFML::Texture *texture = GetTexture(it->second.texture);
            if (texture == nullptr) {
                return nullptr;
            }
            ::SaltyEngine::Vector2i position = it->second.position;
            ::SaltyEngine::Vector2i size = it->second.size;
            ::SaltyEngine::SFML::Sprite *sprite = new ::SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(position.x, position.y, size.x, size.y));
            sprite->SetName(name);
            return sprite;
        }

        ::SaltyEngine::Sound::ISound *AssetManager::GetSound(std::string const &name) {
            ::SaltyEngine::Sound::ISound *sound = AAssetManager<::SaltyEngine::SFML::Texture, ::SaltyEngine::SFML::Sprite>::GetSound(name);
            if (sound) {
                return sound->Get();
            }
            return nullptr;
        }
    }
}