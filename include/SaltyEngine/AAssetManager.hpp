//
// Created by wery_a on 30/11/16.
//

#ifndef RTYPE_AASSETMANAGER_HPP
#define RTYPE_AASSETMANAGER_HPP

#include <memory>
#include <cstring>
#include "SaltyEngine/ISound.hpp"
#include "SaltyEngine/Constants.hpp"
#include "Common/Debug.hpp"

#include "Parser/ParserJson.hpp"
#include "Parser/Parser.hpp"

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

    ///
    /// \brief Struct of a Sprite
    ///
    struct SpriteDefault {
        std::string texture;
        Vector2i    position;
        Vector2i    size;
    };

    ///
    /// \brief Struct of an Animation
    ///
    struct AnimationDefault {
        std::string             mode;
        int                     framerate;
        std::list<std::string>  sprites;
    };

    ///
    /// \brief AssetManager load and get all assets
    /// \tparam Texture
    /// \tparam Sprite
    /// \tparam Sound
    template <class Texture, class Sprite, class Animation, class Sound = ::SaltyEngine::Sound::ISound>
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
            path_scenes = getFullPath(Asset::SCENES_PATH);
            path_prefabs = getFullPath(Asset::PREFABS_PATH);
            path_metas = getFullPath(Asset::METAS_PATH);
            path_textures = getFullPath(Asset::TEXTURES_PATH);
            path_sounds = getFullPath(Asset::SOUNDS_PATH);
            path_sprites = getFullPath(Asset::SPRITES_PATH);
            path_animations = getFullPath(Asset::ANIMS_PATH);
        }

        virtual ~AAssetManager() {

        }

    protected:
        std::string                             cwd;

        std::string                             path_scenes;
        std::string                             path_prefabs;
        std::string                             path_metas;
        std::string                             path_textures;
        std::string                             path_sounds;
        std::string                             path_sprites;
        std::string                             path_animations;

        std::map<std::string, std::unique_ptr<Sound>>   m_sounds;
        std::map<std::string, std::unique_ptr<Texture>> m_textures;
        std::map<std::string, SpriteDefault>            m_sprites;
        std::map<std::string, AnimationDefault>         m_animations;
        std::list<std::string>                          m_prefabs;

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
        virtual Sound *GetSound(std::string const &name) {
            typename std::map<std::string, std::unique_ptr<Sound>>::const_iterator it = m_sounds.find(name);
            if (it == m_sounds.end()) {
                if (!LoadSound(name)) {
                    Debug::PrintError("Cannot find sound " + name);
                    return nullptr;
                }
                it = m_sounds.find(name);
                if (it == m_sounds.end()) {
                    Debug::PrintWarning("Failed to get sound " + name);
                    return nullptr;
                }
            }
            return it->second.get();
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
                it = m_textures.find(name);
                if (it == m_textures.end()) {
                    Debug::PrintWarning("Failed to get texture " + name);
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
            try {
                Parser parser = Parser(JSON, (path_sprites + filename + Asset::SPRITE_EXTENSION).c_str());
                JsonVariant::json_pair map;
                if (parser.parse(&map)) {
                    std::string texture = map["texture"]();

                    if (texture.empty() || map["rect"]["x"]().empty() || map["rect"]["y"]().empty() || map["rect"]["width"]().empty() || map["rect"]["heigth"]().empty()) {
                        Debug::PrintError("Bad format prefab " + filename);
                        return false;
                    }

                    LoadTexture(texture);
                    m_sprites[filename] = SpriteDefault {
                            texture,
                            Vector2i(std::stoi(map["rect"]["x"]()), std::stoi(map["rect"]["y"]())),
                            Vector2i(std::stoi(map["rect"]["width"]()), std::stoi(map["rect"]["heigth"]()))
                    };
                    Debug::PrintSuccess("Sprite " + filename + " was successfuly loaded");
                } else {
                    Debug::PrintError("Cannot parse sprite " + filename);
                    return false;
                }
            } catch (std::exception const &e) {
                Debug::PrintError(std::string(e.what()) + " " + filename);
                return false;
            }
            return true;
        }

        ///
        /// \brief Return Sprite pointer
        /// \param name
        /// \return
        virtual Sprite  *GetSprite(std::string const &name) = 0;

    public:
        ///
        /// \brief LoadAnimation by filename
        /// \param filename
        /// \return bool
        bool            LoadAnimation(std::string const &filename) {
            if (m_animations.find(filename) != m_animations.end()) {
                Debug::PrintWarning("Animation " + filename + " already loaded");
                return false;
            }
            try {
                Parser parser = Parser(JSON, (path_animations + filename + Asset::ANIM_EXTENSION).c_str());
                JsonVariant::json_pair map;
                if (parser.parse(&map)) {
                    std::string const &mode = map["mode"]();
                    int      framrate = std::stoi(map["framerate"]());
                    JsonVariant const &spritesJSON = map["sprites"];
                    std::list<std::string>  sprites;

                    for (unsigned int i = 0; i < spritesJSON.size(); ++i) {
                        const std::string sprite = spritesJSON[i]();
                        LoadSprite(sprite);
                        sprites.push_back(sprite);
                    }
                    m_animations[filename] = AnimationDefault {
                            mode,
                            framrate,
                            sprites
                    };
                    Debug::PrintSuccess("Animation " + filename + " was successfuly loaded");
                } else {
                    Debug::PrintError("Cannot parse animation " + filename);
                    return false;
                }
            } catch (std::exception const &e) {
                Debug::PrintError(std::string(e.what()) + " " + filename);
                return false;
            }
            return true;
        }

        ///
        /// \brief Return Animation pointer
        /// \param name
        /// \return
        virtual Animation   *GetAnimation(std::string const &name) = 0;
    public:
        ///
        /// \brief Load Prefab from filename
        /// \brief Load sprites dependencies
        /// \param filename
        /// \return bool
        bool    LoadPrefab(std::string const &filename) {
            if (std::find(m_prefabs.begin(), m_prefabs.end(), filename) != m_prefabs.end()) {
                Debug::PrintWarning("Prefab " + filename + " already loaded");
                return false;
            }
            try {
                Parser parser = Parser(JSON, (path_prefabs + filename + Asset::PREFAB_EXTENSION).c_str());
                JsonVariant::json_pair map;
                if (parser.parse(&map)) {
                    Debug::PrintInfo("Parsing Prefab " + filename);
                    std::string const &lib = map["lib"]();
                    JsonVariant const &sprites = map["sprites"];
                    JsonVariant const &sounds = map["sounds"];
                    JsonVariant const &dependencies = map["dependencies"];
                    JsonVariant const &animations = map["animations"];

                    for (unsigned int i = 0; i < sprites.size(); ++i) {
                        LoadSprite(sprites[i]());
                    }

                    for (unsigned int i = 0; i < sounds.size(); ++i) {
                        LoadSound(sounds[i]());
                    }

                    for (unsigned int i = 0; i < dependencies.size(); ++i) {
                        LoadPrefab(dependencies[i]());
                    }

                    for (unsigned int i = 0; i < animations.size(); ++i) {
                        LoadAnimation(animations[i]());
                    }

                    if (!lib.empty()) {
                        Factory::Instance().LoadAsset(path_metas + lib + Asset::META_EXTENSION);
                    }

                    m_prefabs.push_back(filename);
                    Debug::PrintSuccess("Prefab " + filename + " was successfuly loaded");
                } else {
                    Debug::PrintError("Cannot parse prefab " + filename);
                    return false;
                }
            } catch (std::exception const &e) {
                Debug::PrintError(std::string(e.what()) + " " + filename);
                return false;
            }
            return true;
        }

        ///
        /// \brief Load Scene from filename
        /// \brief Load Prefabs
        /// \brief Return list of pair of prefabName and position
        /// \param filename
        /// \return std::list<std::pair<std::string, Vector2f>>
        std::list<std::pair<std::string, Vector2f>> LoadScene(std::string const &filename) {
            std::list<std::pair<std::string, Vector2f>> objects;

            try {
                Parser parser = Parser(JSON, (path_scenes + filename + Asset::SCENE_EXTENSION).c_str());
                JsonVariant::json_pair map;
                if (parser.parse(&map)) {
                    Debug::PrintInfo("Parsing Scene " + filename);
                    std::string const &title = map["title"]();
                    std::string const &preview = map["preview"]();

                    JsonVariant::json_pair *prefabs = boost::get<JsonVariant::json_pair *>(map["prefabs"].get());
                    for (JsonVariant::json_pair::const_iterator prefab = prefabs->begin(); prefab != prefabs->end(); ++prefab) {
                        std::string prefabName = prefab->first;
                        Vector2f    position = Vector2f(std::stoi(prefab->second["position"]["x"]()), std::stoi(prefab->second["position"]["y"]()));
                        if (LoadPrefab(prefabName)) {
                            objects.push_back(std::make_pair(prefabName, position));
                        }
                    }
                    Debug::PrintSuccess("Scene " + filename + " was successfuly loaded");
                } else {
                    Debug::PrintError("Cannot parse scene " + filename);
                }
            } catch (std::exception const &e) {
                Debug::PrintError(std::string(e.what()) + " " + filename);
            }
            return objects;
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
                unsigned long dotPos = static_cast<unsigned long>(filename.find_last_of("."));
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
                unsigned long dotPos = static_cast<unsigned long>(filename.find_last_of("."));
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
            for (std::string filename : getFilesInDir(path_metas)) {
                unsigned long dotPos = static_cast<unsigned long>(filename.find_last_of("."));
                if (dotPos == filename.npos) {
                    continue;
                }
                if (filename.substr(dotPos) == Asset::META_EXTENSION) {
                    Debug::PrintSuccess("Loading prefab [ " + filename + " ]");
                    Factory::Instance().LoadAsset(path_metas + filename);
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
