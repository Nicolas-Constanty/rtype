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
		virtual void Display(const std::unique_ptr<Scene> &scene) const {};
	};
}

#endif // !DEFAULTRENDERER_HPP_
