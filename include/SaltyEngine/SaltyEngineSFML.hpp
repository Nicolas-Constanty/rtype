#pragma once

#ifndef SALTENGINESFML_HPP_
#define SALTENGINESFML_HPP_

#include "SaltyEngine.hpp"

namespace SaltyEngine
{
	class LIB_EXPORT SaltyEngineSFML : public Engine
	{
	public:
		SaltyEngineSFML();
		~SaltyEngineSFML();

	public:
		void Run();
	};

}

#endif // !SALTENGINESFML_HPP_