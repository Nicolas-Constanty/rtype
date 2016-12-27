#pragma once

#ifndef DEFAULTSCENE_HPP_
#define DEFAULTSCENE_HPP_

#include "AScene.hpp"

namespace SaltyEngine
{
	class LIB_EXPORT DefaultScene : public AScene
	{
	public:
		DefaultScene() : AScene() {};
		explicit DefaultScene(const std::string &name) : AScene(name) {};
		~DefaultScene() {};

	public:
		void UpdatePhysics() override;
	};
}

#endif // !DEFAULTSCENE_HPP_
