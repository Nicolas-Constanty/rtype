#pragma once

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <SFML/Graphics.hpp>

namespace SpriteEditor
{
	class Texture : public sf::Texture
	{
	public:
		~Texture() {};
		virtual bool loadFromFile(const std::string &filename);
		const std::string &GetFilename();
	private:
		std::string m_filename;
	};
}

#endif // !TEXTURE_HPP_
