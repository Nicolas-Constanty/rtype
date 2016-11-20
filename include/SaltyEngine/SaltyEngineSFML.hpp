#pragma once

#ifndef SALTENGINESFML_HPP_
#define SALTENGINESFML_HPP_

#include "SaltyGame.hpp"

namespace SaltyEngine
{
	class SaltyEngineSFML : public SaltyGame
	{
	public:
		SaltyEngineSFML();
		~SaltyEngineSFML();

	public:
		void Run();
	};

}

#endif // !SALTENGINESFML_HPP_