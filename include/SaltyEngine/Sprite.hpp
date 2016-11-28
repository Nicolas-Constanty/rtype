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
		explicit Sprite(Texture<T>* const texture,
			const std::string& name)
			: Object(name)
		{
			m_rect = nullptr;
			m_texture = texture;
		}

		explicit Sprite(Texture<T>* const texture, IRect<T>* const rect,
			const std::string& name)
			: Object(name)
		{
			m_rect = rect;
			m_texture = texture;
		}

		virtual ~Sprite() {};

	private:
		IRect<T>		*m_rect;
		Texture<T>		*m_texture;
	public:
		IRect<T>* GetRect() const
		{
			return m_rect;
		}

		virtual void SetRect(IRect<T>* const rect)
		{
			m_rect = rect;
		}
	};
}

#endif // !SPRITE_HPP_