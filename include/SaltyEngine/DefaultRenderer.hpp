#pragma once

#ifndef DEFAULTRENDERER_HPP_
#define DEFAULTRENDERER_HPP_

#include "SaltyEngine/IRenderer.hpp"

namespace SaltyEngine
{
	class DefaultRenderer : public IRenderer
	{
	public:
		virtual ~DefaultRenderer() {};
		void Display() const override {};
		virtual void RemoveSpriteRenderer(GameObject * const gm) { (void)gm; };
	};
}

#endif // !DEFAULTRENDERER_HPP_
