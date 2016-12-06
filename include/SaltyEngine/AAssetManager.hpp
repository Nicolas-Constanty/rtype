//
// Created by wery_a on 30/11/16.
//

#ifndef RTYPE_AASSETMANAGER_HPP
#define RTYPE_AASSETMANAGER_HPP

#include <memory>
#include <Common/Singleton.hpp>
#include <cstring>
#include "SaltyEngine/ISound.hpp"
#include "SaltyEngine/Texture.hpp"
#include "SaltyEngine/Debug.hpp"
#include "SaltyEngine/Constants.hpp"
#include "SaltyEngine/Texture.hpp"

#if _WIN32
#include <direct.h>
#include "Common/DllLoader.hpp"
#else
#include <dirent.h>
#include <unistd.h>
#include "Common/LibLoader.hpp"
#endif

namespace SaltyEngine {

    struct SpriteDefault {
        std::string texture;
        Vector2i    position;
        Vector2i    size;
    };

    ///
    /// \brief AssetManager load and get all assets
    /// \tparam Texture
    /// \tparam Sprite
    /// \tparam Sound
    template <class Texture, class Sprite, class Sound = ::SaltyEngine::Sound::ISound>
    class AAssetManager {
    protected:
        AAssetManager() {
            #if _WIN32
                CHAR *cwd = new char[256];
                _getcwd(cwd, 256);
                this->cwd = std::string(cwd) + "\\";
            #else
                char *cwd = new char[256];
                getcwd(cwd, 256);
                this->cwd = std::string(cwd) + "/";
            #endif
            path_monsters = getFullPath(Asset::MONSTERS_PATH);
            path_textures = getFullPath(Asset::TEXTURES_PATH);
            path_sounds = getFullPath(Asset::SOUNDS_PATH);
            path_sprites = getFullPath(Asset::SPRITES_PATH);
        }

        virtual ~AAssetManager() {}

    protected:
        std::string                             cwd;

        std::string                             path_monsters;
        std::string                             path_textures;
        std::string                             path_sounds;
        std::string                             path_sprites;

        std::map<std::string, Sound*>           m_sounds;
        std::map<std::string, Texture*>         m_textures;
        std::map<std::string, SpriteDefault>    m_sprites;


    public:
        ///
        /// \brief Load sound and music from child
        /// \param name
        /// \param isMusic
        /// \return bool
        virtual bool LoadISound(const std::string &name, bool isMusic) = 0;

        ///
        /// \brief Call LoadISound for Sound
        /// \param name
        /// \return bool
        bool LoadSound(const std::string &name) {
            return LoadISound(name, false);
        }

        ///
        /// \brief Call LoadISound for Music
        /// \param name
        /// \return bool
        bool LoadMusic(const std::string &name) {
            return LoadISound(name, true);
        }

        ///
        /// \brief Return Sound template parameter pointer
        /// \param name
        /// \return Sound*
        Sound   *GetSound(const std::string &name) {
            typename std::map<std::string, Sound*>::const_iterator it = m_sounds.find(name);
            if (it == m_sounds.end()) {
                if (!LoadSound(name)) {
                    Debug::PrintError("Cannot find sound " + name);
                    return nullptr;
                }
            }
            return it->second;
        }

    public:
        ///
        /// \brief Load texture from child
        /// \param name
        /// \return
        virtual bool LoadTexture(const std::string &name) = 0;

        ///
        /// \brief Return Texture template parameter pointer
        /// \param name
        /// \return Texture*
        Texture *GetTexture(const std::string &name) {
            typename std::map<std::string, Texture*>::const_iterator it = m_textures.find(name);
            if (it == m_textures.end()) {
                if (!LoadTexture(name)) {
                    Debug::PrintError("Cannot find texture " + name);
                    return nullptr;
                }
            }
            return it->second;
        }

    public:
        ///
        /// \brief LoadSprite by filename
        /// \param filename
        /// \return bool
        bool            LoadSprite(std::string const &filename) {
            std::string texture;

            LoadTexture(texture);
            m_sprites[filename] = SpriteDefault{};
        }

        ///
        /// \brief Return Sprite pointer
        /// \param name
        /// \return
        virtual Sprite  *GetSprite(std::string const &name) const = 0;

    public:
        bool    LoadPrefab(std::string const &filename) {
            std::list<std::string>  sprites;
            std::string             lib;

            for (std::string sprite: sprites) {
                LoadSprite(sprite);
            }
            if (!lib.empty()) {
                Factory::LoadAsset(path_monsters + filename);
            }
        }

        ///
        /// \brief Load all Assets
        /// \param
        /// \return
        void    LoadAssets() {
            LoadSounds();
            LoadTextures();
            LoadMonsters();
        }

        ///
        /// \brief Load all Sounds
        /// \param
        /// \return
        void    LoadSounds() {
            for (std::string filename: getFilesInDir(getFullPath(Asset::SOUNDS_PATH))) {
                unsigned long dotPos = filename.find_last_of(".");
                if (filename.substr(dotPos) == Asset::SOUND_EXTENSION) {
                    Debug::PrintSuccess("Loading sound [ " + filename + " ]");
                    LoadTexture(filename.substr(0, dotPos));
                }
            }
        }

        ///
        /// \brief Load all Textures
        /// \param
        /// \return
        void    LoadTextures() {
            for (std::string filename: getFilesInDir(getFullPath(Asset::TEXTURES_PATH))) {
                unsigned long dotPos = filename.find_last_of(".");
                if (filename.substr(dotPos) == Asset::TEXTURE_EXTENSION) {
                    Debug::PrintSuccess("Loading texture [ " + filename + " ]");
                    LoadTexture(filename.substr(0, dotPos));
                }
            }
        }

        ///
        /// \brief Load all Monsters
        /// \param
        /// \return
        void    LoadMonsters() {
            for (std::string filename: getFilesInDir(getFullPath(Asset::MONSTERS_PATH))) {
                unsigned long dotPos = filename.find_last_of(".");
                if (filename.substr(dotPos) == Asset::MONSTER_EXTENSION) {
                    Debug::PrintSuccess("Loading monster [ " + filename + " ]");
                    Factory::LoadAsset(path_monsters + filename);
                }
            }
        }

    protected:
        ///
        /// \brief get absolute current directory
        /// \param path
        /// \return std::string
		inline std::string getFullPath(std::string const &path) {
			return cwd + path;
		}

        ///
        /// \brief list files in directory
        /// \param folder
        /// \return std::list<std::string>
        std::list<std::string>  getFilesInDir(const std::string &folder) {
            std::list<std::string>  files;

#if _WIN32
            WIN32_FIND_DATA findFileData;
		    HANDLE hFind;
		    hFind = FindFirstFile(std::string(folder + "\\*").c_str(), &findFileData);
		    while (hFind != INVALID_HANDLE_VALUE)
		    {
                std::string filename = std::string(findFileData.cFileName);
                if (filename != "."  && filename != "..") {
                    files.push_back(filename);
                }
				if (FindNextFile(hFind, &findFileData) == FALSE)
				{
					Debug::PrintError("Cannnot open folder " + folder);
					break;
				}
    		}
    		FindClose(hFind);
#else
            DIR             *dir;
            struct dirent   *ent;

            if ((dir = opendir(folder.c_str())) != NULL) {
                /* get all the files and directories within directory */
                while ((ent = readdir(dir)) != NULL)
                {
                    std::string filename = std::string(ent->d_name);
                    if (filename != "."  && filename != "..") {
                        files.push_back(filename);
                    }
                }
                closedir(dir);
            } else {
                Debug::PrintError("Cannnot open folder " + folder);
            }
#endif
        return files;
        }
    };
}

#endif //RTYPE_AASSETMANAGER_HPP
