#pragma once

#ifndef DEFAULTRENDERER_HPP_
#define DEFAULTRENDERER_HPP_

#include "SaltyEngine/IRenderer.hpp"

namespace SaltyEngine
{
	class LIB_EXPORT DefaultRenderer : public IRenderer
	{
	public:
		virtual ~DefaultRenderer() {};
		void Display() override {};
		virtual void RemoveSpriteRenderer(GameObject * const gm) { (void)gm; };
	};
}

#endif // !DEFAULTRENDERER_HPP_
