#pragma once

#ifndef IRENDERER_HPP_
#define IRENDERER_HPP_

#include "Common/DLLexport.hpp"

namespace SaltyEngine
{
	class Scene;
	class GameObject;
	class LIB_EXPORT IRenderer
	{
	public:
		virtual ~IRenderer() {};
		virtual void Display() = 0;
		virtual void RemoveSpriteRenderer(GameObject * const gm) = 0;
	};
}

#endif // !IRENDERER_HPP_
