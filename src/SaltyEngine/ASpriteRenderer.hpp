#pragma once

#ifndef ASPRITERENDERER_HPP_
#define ASPRITERENDERER_HPP_

#include "SaltyEngine/Component.hpp"
#include "SaltyEngine/Sprite.hpp"

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
		ASpriteRenderer(const std::string &name, GameObject * const gameObj, int layer) : Component(name, gameObj), m_layer(layer) {};
		ASpriteRenderer(GameObject* const gameObj, int layer) : Component("ASpriteRenderer", gameObj), m_layer(layer) {};
		virtual ~ASpriteRenderer() {};
		virtual void Draw() const = 0;
		virtual int GetLayer() const { return (m_layer); }

	protected:
		Sprite<T>		*m_sprite;
		const int		m_layer;
	};
}

#endif // !ISPRITERENDERER_HPP_
