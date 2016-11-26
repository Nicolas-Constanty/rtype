#pragma once

#ifndef IRENDERER_HPP_
#define IRENDERER_HPP_

#include <memory>

namespace SaltyEngine
{
	class Scene;
	class IRenderer
	{
	public:
		virtual ~IRenderer() {};
		virtual void Display(const std::unique_ptr<Scene> &scene) const = 0;
	};
}

#endif // !IRENDERER_HPP_
