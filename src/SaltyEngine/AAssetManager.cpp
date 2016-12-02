//#include "SaltyEngine/AAssetManager.hpp"
//
//namespace SaltyEngine
//{
//	template <class Texture, class Sound = ::SaltyEngine::Sound::ISound>
//	std::string AAssetManager<Texture, Sound>::getFullPath(std::string const &path) {
//		Debug::PrintInfo(cwd + path);
//		return cwd + path;
//	}
//
//	template <class Texture, class Sound = ::SaltyEngine::Sound::ISound>
//	std::list<std::string>  AAssetManager<Texture, Sound>::getFilesInDir(const std::string &folder) {
//		std::list<std::string>  files;
//
//#if _WIN32
//		WIN32_FIND_DATA findFileData;
//		HANDLE hFind;
//
//		hFind = FindFirstFile(std::string(folder + "\\*").c_str(), &findFileData);
//		Debug::PrintInfo(folder);
//		while (hFind != INVALID_HANDLE_VALUE)
//		{
//			std::string filename = std::string(findFileData.cFileName);
//			if (filename != "."  && filename != "..") {
//				files.push_back(filename);
//			}
//			if (FindNextFile(hFind, &findFileData) == FALSE)
//			{
//				Debug::PrintError("Cannnot open folder " + folder);
//				break;
//			}
//		}
//		FindClose(hFind);
//#else
//		DIR             *dir;
//		struct dirent   *ent;
//
//		if ((dir = opendir(folder.c_str())) != NULL) {
//			/* get all the files and directories within directory */
//			while ((ent = readdir(dir)) != NULL)
//			{
//				std::string filename = std::string(ent->d_name);
//				if (filename != "."  && filename != "..") {
//					files.push_back(filename);
//				}
//			}
//			closedir(dir);
//		}
//		else {
//			Debug::PrintError("Cannnot open folder " + folder);
//		}
//#endif
//		return files;
//	}
//}