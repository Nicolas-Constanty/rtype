#pragma once

#ifndef SFMLTEXTURE_HPP_
#define SFMLTEXTURE_HPP_

#include <SFML/Graphics.hpp>
#include "SaltyEngine/Texture.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class Texture : public sf::Texture, public ::SaltyEngine::Texture<sf::Vector2i>
		{
		public:

			explicit Texture(const std::string& filename)
				: sf::Texture(), ::SaltyEngine::Texture<sf::Vector2i>("SFMLTexture")
			{
				m_filename = filename;
			}

			explicit Texture()
				: sf::Texture(), ::SaltyEngine::Texture<sf::Vector2i>("SFMLTexture")
			{
				m_filename = "None";
			}

			virtual ~Texture() {};

			sf::Vector2i GetSize(void) const override
			{
				return m_size;
			}

			const std::string &GetFileName(void) const
			{
				return (m_filename);
			}

			bool Create(unsigned int width, unsigned int height) override
			{
				return create(width, height);
			}

		protected:
			sf::Vector2i	m_size;
			std::string		m_filename;
		};
	}
}

#endif // !SFMLTEXTURE_HPP_
