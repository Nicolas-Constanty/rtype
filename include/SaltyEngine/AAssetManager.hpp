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
#include "SaltyEngine/Constants.hpp"
#include "SaltyEngine/Texture.hpp"
#include "SaltyEngine/Debug.hpp"

#if _WIN32
#include <direct.h>
#include "Common/DllLoader.hpp"
#else
#include <dirent.h>
#include <unistd.h>
#include "Common/LibLoader.hpp"
#include "GameObject.hpp"

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
            path_prefabs = getFullPath(Asset::PREFABS_PATH);
            path_textures = getFullPath(Asset::TEXTURES_PATH);
            path_sounds = getFullPath(Asset::SOUNDS_PATH);
            path_sprites = getFullPath(Asset::SPRITES_PATH);
        }

        virtual ~AAssetManager() {

        }

    protected:
        std::string                             cwd;

        std::string                             path_prefabs;
        std::string                             path_textures;
        std::string                             path_sounds;
        std::string                             path_sprites;

        std::map<std::string, Sound*>           m_sounds;
        std::map<std::string, std::unique_ptr<Texture>> m_textures;
        std::map<std::string, SpriteDefault>    m_sprites;


    public:
        ///
        /// \brief Load sound and music from child
        /// \param name
        /// \param isMusic
        /// \return bool
        virtual bool LoadISound(std::string const &name, bool isMusic) = 0;

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
        bool LoadMusic(std::string const &name) {
            return LoadISound(name, true);
        }

        ///
        /// \brief Return Sound template parameter pointer
        /// \param name
        /// \return Sound*
        Sound   *GetSound(std::string const &name) {
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
        virtual bool LoadTexture(std::string const &name) = 0;

        ///
        /// \brief Return Texture template parameter pointer
        /// \param name
        /// \return Texture*
        Texture *GetTexture(std::string const &name) {
            typename std::map<std::string, std::unique_ptr<Texture>>::const_iterator it = m_textures.find(name);
            if (it == m_textures.end()) {
                if (!LoadTexture(name)) {
                    Debug::PrintError("Cannot find texture " + name);
                    return nullptr;
                }
            }
            return it->second.get();
        }

    public:
        ///
        /// \brief LoadSprite by filename
        /// \param filename
        /// \return bool
        bool            LoadSprite(std::string const &filename) {
            if (m_sprites.find(filename) != m_sprites.end()) {
                Debug::PrintWarning("Sprite " + filename + " already loaded");
                return false;
            }
            std::string texture;

            LoadTexture(texture);
            m_sprites[filename] = SpriteDefault{};
            return true;
        }

        ///
        /// \brief Return Sprite pointer
        /// \param name
        /// \return
        virtual Sprite  *GetSprite(std::string const &name) = 0;

    public:
        bool    LoadPrefab(std::string const &filename) {
            std::list<std::string>  sprites;
            std::string             lib;

            for (std::string sprite: sprites) {
                LoadSprite(sprite);
            }
            if (!lib.empty()) {
                Factory::LoadAsset(path_prefabs + filename);
            }
            return true;
        }

        std::list<std::pair<std::string, Vector2i>> LoadScene(std::string const &filename) {
            std::list<std::pair<std::string, Vector2i>> objects;
//            for () {
                std::string prefabName;
                Vector2i    position;
                LoadPrefab(prefabName);
            objects.push_back(std::make_pair(prefabName, position));
//            }
//            objects.sort(compare_position_objects);
            return objects;
        }

    private:
        bool    compare_position_objects(std::pair<std::string, Vector2i> obj1, std::pair<std::string, Vector2i> obj2) {
            return obj1.second.x < obj2.second.x;
        }

    public:
        ///
        /// \brief Load all Assets
        /// \param
        /// \return
        void    LoadAssets() {
            LoadSounds();
            LoadTextures();
            LoadPrefabs();
        }

        ///
        /// \brief Load all Sounds
        /// \param
        /// \return
        void    LoadSounds() {
            for (std::string filename: getFilesInDir(path_sounds)) {
                unsigned long dotPos = filename.find_last_of(".");
                if (dotPos == filename.npos) {
                    continue;
                }
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
            for (std::string filename: getFilesInDir(path_textures)) {
                unsigned long dotPos = filename.find_last_of(".");
                if (dotPos == filename.npos) {
                    continue;
                }
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
        void    LoadPrefabs() {
            for (std::string filename: getFilesInDir(path_prefabs)) {
                unsigned long dotPos = filename.find_last_of(".");
                if (dotPos == filename.npos) {
                    continue;
                }
                if (filename.substr(dotPos) == Asset::PREFAB_EXTENSION) {
                    Debug::PrintSuccess("Loading prefab [ " + filename + " ]");
                    Factory::LoadAsset(path_prefabs + filename);
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
        std::list<std::string>  getFilesInDir(std::string const &folder) {
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
