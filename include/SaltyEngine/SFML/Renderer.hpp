#pragma once

#ifndef SFMLRENDERER_HPP_
#define SFMLRENDERER_HPP_

#include <memory>
#include "SaltyEngine/SFML/Rect.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SFML/Label.hpp"
#include "SaltyEngine/ARenderer.hpp"
#include "SaltyEngine/GUI/Selectable.hpp"
#include "SaltyEngine/GameObject.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class SpriteRenderer;
		class BoxCollider2D;
		class LIB_EXPORT Renderer : public ARenderer<sf::Vector2i>, public sf::RenderWindow
		{
		public:
			struct Drawable
			{
				Drawable(Sprite **s, sf::RenderWindow *w, GameObject *g, SpriteRenderer *sr) :
						spr(s), wind(w), gm(g), sprr(sr) {}
				Sprite **spr;
				sf::RenderWindow *wind;
				GameObject *gm;
				SpriteRenderer *sprr;
			};
		public:
			typedef std::list<Drawable> SpriteList;
			typedef  std::map<int, SpriteList> SpriteMap;
			typedef std::list<::SaltyEngine::GUI::SFML::Label *> LabelList;
		public:
			Renderer(sf::VideoMode const &vm, const std::string &name);
			virtual ~Renderer();
			void Display() override;
            virtual void RemoveSpriteRenderer(GameObject * const gm) override;
			//sf::RenderWindow *GetRenderWindow(void) const;
			void DrawDebug();

		protected:
			//std::unique_ptr<sf::RenderWindow> m_window;

		private:
			void DrawGame() const;
			void DrawGUI() const;
			void DrawLabel();
			void DrawSprites(const SpriteList &sprite_list) const;

		private:
			SpriteMap m_spriteRenderers;
			std::list<BoxCollider2D *> m_debug;
			std::list<::SaltyEngine::GUI::Selectable *> m_selectables;
			LabelList m_labels;
		public:
			void AddSpriteRenderer(SpriteRenderer* const sprr);
			void AddDebug(BoxCollider2D *);

			const SpriteMap &GetSprites(void) const
			{
				return (m_spriteRenderers);
			}

		public:
			void AddSelectable(::SaltyEngine::GUI::Selectable* const select);

			::SaltyEngine::Vector2i GetRealSize() const;

			void AddLabel(::SaltyEngine::GUI::SFML::Label *label);
		};
	}
}

#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SFML/BoxCollider2D.hpp"

#endif // !SFMLRENDERER_HPP_
