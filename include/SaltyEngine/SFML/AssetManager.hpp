//
// Created by wery_a on 30/11/16.
//

#ifndef RTYPE_ASSETMANAGER_HPP
#define RTYPE_ASSETMANAGER_HPP

#include "SaltyEngine/AAssetManager.hpp"
#include "SaltyEngine/SFML/Texture.hpp"
#include "SaltyEngine/SFML/Sprite.hpp"

namespace SaltyEngine {
    namespace SFML {
        class AssetManager: public AAssetManager<::SaltyEngine::SFML::Texture, ::SaltyEngine::SFML::Sprite>, public Singleton<AssetManager> {
        public:
            friend class Singleton<AssetManager>;

        private:
            AssetManager();
            virtual ~AssetManager();

        public:
            bool LoadISound(std::string const &name, bool isMusic);
            bool LoadTexture(std::string const &name);
            ::SaltyEngine::SFML::Sprite *GetSprite(std::string const &name);
        };
    }
}

#endif //RTYPE_ASSETMANAGER_HPP
