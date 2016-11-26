#pragma once

#ifndef SFMLRENDERER_HPP_
#define SFMLRENDERER_HPP_

#include "SaltyEngine/IRenderer.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class Renderer : public IRenderer
		{
		public:
			virtual ~Renderer() {};
			virtual void Display(const std::unique_ptr<Scene> &scene) const;
		};
	}
}

#endif // !SFMLRENDERER_HPP_
