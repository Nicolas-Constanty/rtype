//
// Created by wery_a on 30/11/16.
//

#ifndef RTYPE_ASSETMANAGER_HPP
#define RTYPE_ASSETMANAGER_HPP

#include "SaltyEngine/SFML/Texture.hpp"
#include "SaltyEngine/SFML/Sprite.hpp"
#include "SaltyEngine/SFML/AnimationClip.hpp"
#include "Common/Singleton.hpp"
#include "SaltyEngine/AAssetManager.hpp"

namespace SaltyEngine {
    namespace SFML {
        class LIB_EXPORT AssetManager: public AAssetManager<Texture, Sprite, AnimationClip, sf::Font>, public Singleton<AssetManager> {
        public:
            friend class Singleton<AssetManager>;

        private:
            AssetManager();
            virtual ~AssetManager();

        public:
            bool LoadISound(std::string const &name, bool isMusic);
            bool LoadTexture(std::string const &name);
            Sprite *GetSprite(std::string const &name);
            Sprite *GetSpriteScale(std::string const &name, bool noScale);
            AnimationClip *GetAnimation(std::string const &name);
            ::SaltyEngine::Sound::ISound *GetSound(std::string const &name);
            bool LoadFont(std::string const &name);
        };
    }
}

template<>
SaltyEngine::SFML::AssetManager &Singleton<SaltyEngine::SFML::AssetManager>::Instance();

#endif //RTYPE_ASSETMANAGER_HPP
