//
// Created by wery_a on 30/11/16.
//

#include "SaltyEngine/SFML/Music.hpp"
#include "SaltyEngine/SFML/Sound.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"

namespace SaltyEngine {
    namespace SFML {
        AssetManager::AssetManager(): AAssetManager<Texture, Sprite, AnimationClip>() {

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
                sound = new Music();
            } else {
                sound = new Sound();
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
            Texture *texture = new Texture();
            if (!texture->loadFromFile(path_textures + name + Asset::TEXTURE_EXTENSION)) {
                Debug::PrintWarning("Failed to load texture " + name);
                return false;
            }
            Debug::PrintSuccess("Texture " + name + " was successfuly loaded");
            m_textures[name] = std::unique_ptr<Texture>(texture);
            return true;
        }

        Sprite *AssetManager::GetSprite(std::string const &name) {
            typename std::map<std::string, SpriteDefault>::const_iterator it = m_sprites.find(name);
            if (it == m_sprites.end()) {
                if (!LoadSprite(name)) {
                    Debug::PrintWarning("Cannot find sprite " + name);
                    return nullptr;
                }
                it = m_sprites.find(name);
                if (it == m_sprites.end()) {
                    Debug::PrintWarning("Failed to get sprite " + name);
                    return nullptr;
                }
            }
            Texture *texture = GetTexture(it->second.texture);
            if (texture == nullptr) {
                return nullptr;
            }
            ::SaltyEngine::Vector2i position = it->second.position;
            ::SaltyEngine::Vector2i size = it->second.size;
            m_createdsprites.emplace(new Sprite(texture, new Rect(position.x, position.y, size.x, size.y)));
//            Sprite *sprite();
            m_createdsprites.top()->SetName(name);
            m_createdsprites.top()->scale(it->second.scale.x, it->second.scale.y);
            return m_createdsprites.top().get();
        }

        AnimationClip* AssetManager::GetAnimation(std::string const &name) {
            typename std::map<std::string, AnimationDefault>::const_iterator it = m_animations.find(name);
            if (it == m_animations.end()) {
                if (!LoadAnimation(name)) {
                    Debug::PrintWarning("Cannot find animation " + name);
                    return nullptr;
                }
                it = m_animations.find(name);
                if (it == m_animations.end()) {
                    Debug::PrintWarning("Failed to get animation " + name);
                    return nullptr;
                }
            }

            AnimationConstants::WrapMode mode = AnimationConstants::WrapMode::ONCE;

            if (it->second.mode == "PING_PONG") {
                mode = AnimationConstants::WrapMode::PING_PONG;
            } else if (it->second.mode == "LOOP") {
                mode = AnimationConstants::WrapMode::LOOP;
            }

            AnimationClip *clip = new SaltyEngine::SFML::AnimationClip(name, it->second.framerate, mode);
            for (std::string const &spriteName: it->second.sprites) {
                Sprite  *sprite = GetSprite(spriteName);
                sprite->scale(it->second.scale.x, it->second.scale.y);
                clip->AddSprite(sprite);
            }
            return clip;
        }

        ::SaltyEngine::Sound::ISound *AssetManager::GetSound(std::string const &name) {
            ::SaltyEngine::Sound::ISound *sound = AAssetManager<Texture, Sprite, AnimationClip>::GetSound(name);
            if (sound) {
                return sound->Get();
            }
            return nullptr;
        }
    }
}