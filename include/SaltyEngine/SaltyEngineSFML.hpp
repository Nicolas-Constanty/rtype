#pragma once

#ifndef SALTENGINESFML_HPP_
#define SALTENGINESFML_HPP_

#include "SaltyEngine.hpp"

namespace SaltyEngine
{
	class SaltyEngineSFML : public SaltyEngine
	{
	public:
		SaltyEngineSFML();
		~SaltyEngineSFML();

	public:
		void Run();
	};

}

#endif // !SALTENGINESFML_HPP_