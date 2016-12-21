//
// Created by wery_a on 30/11/16.
//

#include "SaltyEngine/SFML/Music.hpp"
#include "SaltyEngine/SFML/Sound.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"

namespace SaltyEngine {
    namespace SFML {
        AssetManager::AssetManager(): AAssetManager<Texture, Sprite, AnimationClip, sf::Font>() {

        }

        AssetManager::~AssetManager() {

        }

        bool AssetManager::LoadISound(std::string const &name, bool isMusic) {
            if (m_sounds.find(name) != m_sounds.end()) {
                Debug::PrintWarning("Sound " + name + " already loaded");
                return true;
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
                return true;
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

        bool AssetManager::LoadFont(std::string const &name) {
            if (m_fonts.find(name) != m_fonts.end()) {
                Debug::PrintWarning("Font " + name + " already loaded");
                return true;
            }
            sf::Font *font = new sf::Font();
            std::cout << path_fonts + name + Asset::FONT_EXTENSION << std::endl;
            if (!font->loadFromFile(path_fonts + name + Asset::FONT_EXTENSION)) {
                Debug::PrintWarning("Failed to load font " + name);
                return false;
            }
            Debug::PrintSuccess("Font " + name + " was successfuly loaded");
            m_fonts[name] = std::unique_ptr<sf::Font>(font);
            return true;
        }

        Sprite *AssetManager::GetSprite(std::string const &name) {
            return GetSpriteScale(name, false);
        }

        Sprite *AssetManager::GetSpriteScale(std::string const &name, bool noScale) {
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
            Sprite *sprite = new Sprite(texture, new Rect(position.x, position.y, size.x, size.y));
            sprite->SetName(name);
            if (!noScale) {
                sprite->setScale(it->second.scale.x, it->second.scale.y);
            }
            return sprite;
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
                Sprite  *sprite = GetSpriteScale(spriteName, true);
                sprite->setScale(it->second.scale.x, it->second.scale.y);
                clip->AddSprite(sprite);
            }
            return clip;
        }

        ::SaltyEngine::Sound::ISound *AssetManager::GetSound(std::string const &name) {
            ::SaltyEngine::Sound::ISound *sound = AAssetManager<Texture, Sprite, AnimationClip, sf::Font>::GetSound(name);
            if (sound) {
                return sound->Get();
            }
            return nullptr;
        }
    }
}