#pragma once

#ifndef IRENDERER_HPP_
#define IRENDERER_HPP_

namespace SaltyEngine
{
	class Scene;
	class IRenderer
	{
	public:
		virtual ~IRenderer() {};
		virtual void Display() const = 0;
	};
}

#endif // !IRENDERER_HPP_