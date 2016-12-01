//
// Created by veyrie_f on 23/10/2016.
//

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <type_traits>
#include <ServerRoom/RtypeGameServerTCPConnection.hpp>
#include <ServerRoom/RoomService.hpp>

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
	static T &Instance()
    {
		// C++11 Static Initializer -> avoids any concurrency at creation
		// See : http://preshing.com/20130930/double-checked-locking-is-fixed-in-cpp11/
		static T instance;
        return instance;
    }

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
