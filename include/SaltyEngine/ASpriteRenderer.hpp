#pragma once

#ifndef ASPRITERENDERER_HPP_
#define ASPRITERENDERER_HPP_

#include "SaltyEngine/Component.hpp"
#include "SaltyEngine/Sprite.hpp"
#include "SaltyEngine/Config.hpp"
#include "SaltyEngine/IWindow.hpp"

namespace SaltyEngine
{
	template <class T>
	class ASpriteRenderer : public Component
	{
	public:
		// delete copy and move constructors and assign operators
		ASpriteRenderer(ASpriteRenderer const&) = delete;             // Copy construct
		ASpriteRenderer(ASpriteRenderer&&) = delete;                  // Move construct
		ASpriteRenderer& operator=(ASpriteRenderer const&) = delete;  // Copy assign
		ASpriteRenderer& operator=(ASpriteRenderer &&) = delete;      // Move assign

	public:
		explicit ASpriteRenderer(const std::string &name, GameObject * const gameObj, Sprite<T> * const sprite, Layout layer) :
				Component(name, gameObj),
				m_layer(layer),
				m_window(nullptr),
				m_sprite(sprite)
		{
			m_default_sprite = m_sprite;
		};
		explicit ASpriteRenderer(GameObject* const gameObj, Sprite<T> * const sprite, Layout layer) :
				Component("ASpriteRenderer", gameObj),
                m_layer(layer),
                m_window(nullptr),
                m_sprite(sprite)
		{
			m_default_sprite = m_sprite;
		};
		virtual ~ASpriteRenderer() {
			if (m_default_sprite) {
				delete m_default_sprite;
			}
        };
		virtual Sprite<T>  *GetSprite() const = 0;
		virtual IWindow *GetWindow() const = 0;
		virtual int GetLayer() const { return (m_layer); }
		virtual void SetSprite(Sprite<T> * const sprite) { m_sprite = sprite; }
		virtual void SetLayout(Layout layout) { m_layer = layout; }

	protected:

		Layout			m_layer;
		IWindow			*m_window;

	public:
		Sprite<T>		*m_sprite;
		Sprite<T>		*m_default_sprite;
	};
}

#endif // !ISPRITERENDERER_HPP_
