#pragma once

#ifndef IRENDERER_HPP_
#define IRENDERER_HPP_

#include "GameObject.hpp"

namespace SaltyEngine
{
	class Scene;
	class IRenderer
	{
	public:
		virtual ~IRenderer() {};
		virtual void Display() const = 0;
		virtual void RemoveSpriteRenderer(GameObject * const gm) = 0;
	};
}

#endif // !IRENDERER_HPP_
