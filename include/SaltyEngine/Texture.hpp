#pragma once

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_
#include "SaltyEngine/Object.hpp"

namespace SaltyEngine
{
	template <class T>
	class Texture : public Object
	{
	public:
		explicit Texture(const std::string& name) : Object(name)
		{
		}

		virtual ~Texture() {};
		virtual T GetSize() const = 0;

	protected:
		T	m_size;
	};
}

#endif // !TEXTURE_HPP_
