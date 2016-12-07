//
// Created by veyrie_f on 27/11/16.
//

#ifndef RTYPE_CONSTANTS_HPP
#define RTYPE_CONSTANTS_HPP

#include <string>
#ifdef _WIN32
#include "Common/DllLoader.hpp"
#else
#include "Common/LibLoader.hpp"
#endif

/**
 * \brief Contains global data for the engine
 */
namespace SaltyEngine
{
    namespace Asset {
#ifdef _WIN32
		const std::string LIB_EXTENSION = ".dll";
        typedef DllLoader ASSET_LOADER;
		const std::string	SEP = "\\";
#else
		const std::string LIB_EXTENSION = ".so";
		typedef LibLoader ASSET_LOADER;
		const std::string	SEP = "/";
#endif

		const std::string    ASSET_PATH = "Assets" + SEP;
		const std::string    SOUNDS_PATH = ASSET_PATH + "Sounds" + SEP;
		const std::string    SPRITES_PATH = ASSET_PATH + "Sprites" + SEP;
		const std::string    TEXTURES_PATH = ASSET_PATH + "Textures" + SEP;
		const std::string    FONTS_PATH = ASSET_PATH + "Fonts" + SEP;
		const std::string    PREFABS_PATH = ASSET_PATH + "Prefabs" + SEP;

		const std::string    SOUND_EXTENSION = ".ogg";
		const std::string    SPRITE_EXTENSION = ".sprite";
		const std::string    TEXTURE_EXTENSION = ".png";
		const std::string    FONT_EXTENSION = ".ttf";
		const std::string    PREFAB_EXTENSION = LIB_EXTENSION;
    }

	namespace AnimationConstants
    {
	    enum WrapMode
	    {
		    PING_PONG,
			LOOP,
			ONCE
	    };
    }
}

#endif //RTYPE_CONSTANTS_HPP
