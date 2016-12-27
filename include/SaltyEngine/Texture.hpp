#pragma once

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include "SaltyEngine/Object.hpp"

namespace SaltyEngine
{
	template <class T>
	class LIB_EXPORT Texture : public Object
	{
	public:
		explicit Texture(const std::string& name) : Object(name)
		{
		}

		virtual ~Texture() {};
		virtual T GetSize(void) const = 0;
		virtual bool Create(unsigned int width, unsigned int height) = 0;

	protected:
		T	m_size;
	};
}

#endif // !TEXTURE_HPP_
