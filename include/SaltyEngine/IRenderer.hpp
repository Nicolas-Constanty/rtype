#pragma once

#ifndef IRENDERER_HPP_
#define IRENDERER_HPP_

#include "Common/DLLexport.hpp"
#include "Vector2.hpp"

namespace SaltyEngine
{
	class Scene;
	class GameObject;
	class LIB_EXPORT IRenderer
	{
	public:
		IRenderer(unsigned int x, unsigned int y) : m_size(x, y) {};
		virtual ~IRenderer() {};
		virtual void Display() = 0;
		virtual void RemoveSpriteRenderer(GameObject * const gm) = 0;
		const Vector2ui &GetSize() const {
			return m_size;
		}

	protected:
		Vector2ui m_size;
	};
}

#endif // !IRENDERER_HPP_
