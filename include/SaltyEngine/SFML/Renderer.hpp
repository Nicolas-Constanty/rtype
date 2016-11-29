#pragma once

#ifndef SFMLRENDERER_HPP_
#define SFMLRENDERER_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include "SaltyEngine/ARenderer.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class SpriteRenderer;
		class Renderer : public ARenderer<sf::Vector2i>
		{
		public:
			typedef std::list<std::unique_ptr<SpriteRenderer>> SpriteList;
			typedef  std::map<int, SpriteList> SpriteMap;
		public:
			Renderer(sf::VideoMode const &vm, const std::string &name);
			virtual ~Renderer() {};
			void Display() const override;
			sf::RenderWindow *GetRenderWindow(void) const;

		protected:
			std::unique_ptr<sf::RenderWindow> m_window;

		private:
			void DrawGame(const SpriteMap &sprite_map) const;
			void DrawGUI(const SpriteMap &sprite_map) const;
			void DrawSprites(const SpriteList &sprite_list) const;

		public:
			static SpriteMap m_spriteRenderers;
		public:
			static void AddSpriteRenderer(SpriteRenderer* const sprr);

			static const SpriteMap &GetSprites(void)
			{
				return (m_spriteRenderers);
			}
		};
	}
}

#include "SaltyEngine/SFML/SpriteRenderer.hpp"

#endif // !SFMLRENDERER_HPP_
