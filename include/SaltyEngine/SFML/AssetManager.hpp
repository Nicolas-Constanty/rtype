//
// Created by wery_a on 30/11/16.
//

#ifndef RTYPE_ASSETMANAGER_HPP
#define RTYPE_ASSETMANAGER_HPP

#include <SFML/System.hpp>
#include "SaltyEngine/AAssetManager.hpp"

namespace SaltyEngine {
    namespace SFML {
        class AssetManager: public AAssetManager<::SaltyEngine::SFML::Texture>, public Singleton<AssetManager> {
        public:
            friend class Singleton<AssetManager>;

        private:
            AssetManager();
            virtual ~AssetManager();

        public:
            bool LoadISound(const std::string &name, bool isMusic);
            bool LoadTexture(const std::string &name);
        };
    }
}

#endif //RTYPE_ASSETMANAGER_HPP
