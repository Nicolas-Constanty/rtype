#pragma once

#ifndef SPRITE_HPP_
#define SPRITE_HPP_
#include "SaltyEngine/IRect.hpp"
#include "SaltyEngine/Object.hpp"
#include "SaltyEngine/Texture.hpp"

namespace SaltyEngine
{
	template <class T>
	class Sprite : public Object 
	{
	public:
		explicit Sprite(IRect *const rect,
			const std::string& name)
			: Object(name)
		{
			m_rect = rect;
		}

		virtual ~Sprite() {};

	private:
		IRect		*m_rect;
		Texture<T>  *m_texture;
	public:
		IRect* GetRect() const
		{
			return m_rect;
		}

		virtual void SetRect(IRect* const rect)
		{
			m_rect = rect;
		}
	};
}

#endif // !SPRITE_HPP_
