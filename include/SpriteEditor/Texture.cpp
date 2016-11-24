#include "SpriteEditor/Texture.hpp"

namespace SpriteEditor
{
	bool Texture::loadFromFile(const std::string & filename)
	{
		m_filename = filename;
		return sf::Texture::loadFromFile(filename);
	}
	const std::string & Texture::GetFilename()
	{
		return (m_filename);
	}
}

