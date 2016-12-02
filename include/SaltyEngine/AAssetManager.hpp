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
    template <class Texture, class Sound = ::SaltyEngine::Sound::ISound>
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
        }

        virtual ~AAssetManager() {}

    protected:
        std::string                     cwd;
        std::map<std::string, Sound*>   m_sounds;
        std::map<std::string, Texture*> m_textures;

    public:
        virtual bool LoadISound(const std::string &name, bool isMusic) = 0;
        bool LoadSound(const std::string &name) {
            return LoadISound(name, false);
        }
        bool LoadMusic(const std::string &name) {
            return LoadISound(name, true);
        }

        virtual bool LoadTexture(const std::string &name) = 0;

    public:
        Sound   *GetSound(const std::string &name) const {
            typename std::map<std::string, Sound*>::const_iterator it = m_sounds.find(name);
            if (it == m_sounds.end()) {
                Debug::PrintError("Cannot find sound " + name);
                return nullptr;
            }
            return it->second;
        }

        Texture *GetTexture(const std::string &name) const {
            typename std::map<std::string, Texture*>::const_iterator it = m_textures.find(name);
            if (it == m_textures.end()) {
                Debug::PrintError("Cannot find texture " + name);
                return nullptr;
            }
            return it->second;
        }

        void    LoadAssets() {
            LoadSounds();
            LoadTextures();
            LoadMonsters();
        }

        void    LoadSounds() {
            for (std::string filename: getFilesInDir(getFullPath(Asset::SOUNDS_PATH))) {
                unsigned long dotPos = filename.find_last_of(".");
                if (filename.substr(dotPos) == Asset::SOUND_EXTENSION) {
                    Debug::PrintSuccess("Loading sound [ " + filename + " ]");
                    LoadTexture(filename.substr(0, dotPos));
                }
            }
        }

        void    LoadTextures() {
            for (std::string filename: getFilesInDir(getFullPath(Asset::TEXTURES_PATH))) {
                unsigned long dotPos = filename.find_last_of(".");
                if (filename.substr(dotPos) == Asset::TEXTURE_EXTENSION) {
                    Debug::PrintSuccess("Loading texture [ " + filename + " ]");
                    LoadTexture(filename.substr(0, dotPos));
                }
            }
        }

        void    LoadMonsters() {
            for (std::string filename: getFilesInDir(getFullPath(Asset::MONSTERS_PATH))) {
                unsigned long dotPos = filename.find_last_of(".");
                if (filename.substr(dotPos) == Asset::MONSTER_EXTENSION) {
                    Debug::PrintSuccess("Loading monster [ " + filename + " ]");
                    Factory::LoadAsset(getFullPath(Asset::MONSTERS_PATH) + filename);
                }
            }
        }

    protected:
        inline std::string getFullPath(std::string const &path) {
            return cwd + path;
        }

        std::list<std::string>  getFilesInDir(const std::string &folder) {
            std::list<std::string>  files;

#if _WIN32
            WIN32_FIND_DATA findFileData;
		    HANDLE hFind;

			std::wstring s = std::wstring(folder.begin(), folder.end());
		    hFind = FindFirstFile(s.c_str(), &findFileData);

		    while (hFind != INVALID_HANDLE_VALUE)
		    {
				std::wstring fn = findFileData.cFileName;
                std::string filename = std::string(fn.begin(), fn.end());
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
