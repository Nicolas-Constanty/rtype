#ifndef RTYPE_HPP_
#define RTYPE_HPP_

#include "SaltyEngine/Object.hpp"

template <typename ... Args>
class RtypeFactory
{
public:
	//typedef std::tuple<SaltyEngine::PlayerController> ObjectsList;
	static const std::vector<std::string> names;

	SaltyEngine::GameObject	*create(std::string const &name)
	{
		return _create<0>(name);
	}

private:
	template <size_t n>
	SaltyEngine::GameObject	*_create(std::string const &name)
	{
		if (n > sizeof...(Args))
			return NULL;

		if (name == names[n])
			return dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Object::Instantiate<std::tuple_element<n, std::tuple<Args...> >::type >(name));
		return _create<n + 1 >= sizeof...(Args) ? 0 : n + 1>(name);
	}
};

#endif // !RTYPE_HPP_
