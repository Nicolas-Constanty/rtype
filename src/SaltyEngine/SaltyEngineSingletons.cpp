#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/Factory.hpp"
#include "SaltyEngine/Coroutine.hpp"
#include "Common/Singleton.hpp"

template<>
SaltyEngine::Engine &Singleton<SaltyEngine::Engine>::Instance()
{
	static SaltyEngine::Engine _inst;

	return _inst;
}

template<>
SaltyEngine::Factory &Singleton<SaltyEngine::Factory>::Instance()
{
	static SaltyEngine::Factory _inst;

	return _inst;
}

template<>
coroutine::Ordinator &Singleton<coroutine::Ordinator>::Instance()
{
	static coroutine::Ordinator _inst;

	return _inst;
}