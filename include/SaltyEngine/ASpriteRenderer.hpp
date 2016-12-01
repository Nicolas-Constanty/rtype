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
		explicit ASpriteRenderer(const std::string &name, GameObject * const gameObj, Sprite<T> * const sprite, Layout layer) : Component(name, gameObj), m_sprite(sprite), m_layer(layer), m_window(nullptr)
		{
		};
		explicit ASpriteRenderer(GameObject* const gameObj, Sprite<T> * const sprite, Layout layer) : Component("ASpriteRenderer", gameObj), m_sprite(sprite), m_layer(layer), m_window(nullptr)
		{
		};
		virtual ~ASpriteRenderer() {};
		virtual Sprite<T>  *GetSprite() const = 0;
		virtual IWindow *GetWindow() const = 0;
		virtual int GetLayer() const { return (m_layer); }
		virtual void SetSprite(Sprite<T> * const sprite) { m_sprite = sprite; }

	protected:
		Sprite<T>		*m_sprite;
		const Layout	m_layer;
		IWindow			*m_window;
	};
}

#endif // !ISPRITERENDERER_HPP_
