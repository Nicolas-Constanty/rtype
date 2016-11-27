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
    namespace Asset
    {
        /**
         * \var Library extension
         */
#ifdef _WIN32
        const std::string LIB_EXTENSION = ".dll";
        typedef DllLoader ASSET_LOADER;
#else
        const std::string LIB_EXTENSION = ".so";
        typedef LibLoader ASSET_LOADER;
#endif

        const std::string ASSET_PATH = "./";
    }
}

#endif //RTYPE_CONSTANTS_HPP
