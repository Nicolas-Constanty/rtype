#pragma once

#ifndef DEFAULTRENDERER_HPP_
#define DEFAULTRENDERER_HPP_

#include "SaltyEngine/ARenderer.hpp"

namespace SaltyEngine
{
	class LIB_EXPORT DefaultRenderer : public ARenderer<Vector2ui>
	{
	public:
		DefaultRenderer() : ARenderer(0, 0) {}

		virtual ~DefaultRenderer() {};
		void Display() override {};
		virtual void RemoveSpriteRenderer(GameObject * const gm) { (void)gm; };
		Vector2i GetRealSize() const { return Vector2i(0,0); };
	};
}

#endif // !DEFAULTRENDERER_HPP_
