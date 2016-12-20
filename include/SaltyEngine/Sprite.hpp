#pragma once

#ifndef SPRITE_HPP_
#define SPRITE_HPP_
#include "SaltyEngine/BasicRect.hpp"
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

		explicit Sprite(Texture<T>* const texture, BasicRect<T>* const rect,
			const std::string& name)
			: Object(name)
		{
			m_rect = rect;
			m_texture = texture;
		}

		virtual ~Sprite() {
			delete m_rect;
		};

	private:
		BasicRect<T>		*m_rect;
		Texture<T>		*m_texture;
	public:
		BasicRect<T>* GetRect(void) const
		{
			return m_rect;
		}

		Texture<T>* GetTexture(void) const
		{
			return m_texture;
		}

		virtual void SetRect(BasicRect<T>* const rect)
		{
			m_rect = rect;
		}

		virtual BasicRect<T> *GetBounds() const = 0;
	};
}

#endif // !SPRITE_HPP_
