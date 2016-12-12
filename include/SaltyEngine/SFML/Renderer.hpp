#pragma once

#ifndef SFMLRENDERER_HPP_
#define SFMLRENDERER_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include "SaltyEngine/ARenderer.hpp"
#include "SaltyEngine/GUI/Selectable.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SFML/Rect.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class SpriteRenderer;
		class BoxCollider2D;
		class Renderer : public ARenderer<sf::Vector2i>
		{
		public:
			struct Drawable
			{
				Drawable(Sprite *s, Rect *r, sf::RenderWindow *w, GameObject *g) : spr(s), rect(r), wind(w), gm(g) {}
				Sprite *spr;
				Rect   *rect;
				sf::RenderWindow *wind;
				GameObject *gm;
			};
		public:
			typedef std::list<Drawable> SpriteList;
			typedef  std::map<int, SpriteList> SpriteMap;
		public:
			Renderer(sf::VideoMode const &vm, const std::string &name);
			virtual ~Renderer() {};
			void Display() const override;
			sf::RenderWindow *GetRenderWindow(void) const;

			void DrawDebug() const;

		protected:
			std::unique_ptr<sf::RenderWindow> m_window;

		private:
			void DrawGame() const;
			void DrawGUI() const;
			void DrawSprites(const SpriteList &sprite_list) const;

		public:
			SpriteMap m_spriteRenderers;
			std::list<BoxCollider2D *> m_debug;
			std::list<GUI::Selectable *> m_selectables;
			std::list <Drawable> m_rects;
		public:
			void AddSpriteRenderer(SpriteRenderer* const sprr);
			void AddDebug(BoxCollider2D *);

			const SpriteMap &GetSprites(void) const
			{
				return (m_spriteRenderers);
			}

		public:
			void AddSelectable(GUI::Selectable* const select);
		};
	}
}

#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SFML/BoxCollider2D.hpp"

#endif // !SFMLRENDERER_HPP_
