//
// Created by veyrie_f on 23/10/2016.
//

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <type_traits>

/**
 * \brief Singleton class that creates a templated singleton
 * You MUST call an Instantiate first to create your object
 */
template<class T>
class Singleton
{
	// delete copy and move constructors and assign operators
	Singleton(Singleton const&) = delete;             // Copy construct
	Singleton(Singleton&&) = delete;                  // Move construct
	Singleton& operator=(Singleton const&) = delete;  // Copy assign
	Singleton& operator=(Singleton &&) = delete;      // Move assign

public:
	static T &Instance();

protected:
    //static T m_instance;
	Singleton ()
	{}

	virtual ~Singleton()
	{
		//delete m_instance;
	}
};

//template <class T>
//T Singleton<T>::m_instance = T();

#endif //!SINGLETON_HPP
