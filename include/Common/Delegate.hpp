//
// Created by veyrie_f on 24/10/2016.
//

#ifndef SPIDERCLIENT_IDELEGATE_HPP
#define SPIDERCLIENT_IDELEGATE_HPP

#include <functional>
#include "common/dllexport.h"

/**
 * \brief The Delegate class allow you to create a delegate.
 * You can create a pointer to function, to method, a lambda expression, std::bind
 * or whatever you want. It also allows you to pass any number of arguments of any kind
 * which will be use at functor invocation
 */
template <class T>
class Delegate
{
public:
    /**
     * \brief CTOR
     * \param The function callback
     */
    template <class Func>
	Delegate(Func func) :
            _func(func)
    {
    }

/**
 * IMPORTANT : _func must be declared first in order to
 * be resolved by decltype !!!
 */
private:
    std::function<T> _func;

public:
    /**
     * \brief Functor
     * \param Optionnal : send arguments to invoke the callback
     * http://www.cprogramming.com/c++11/c++11-auto-decltype-return-value-after-function.html
     */
    template<class ... Args>
	auto operator()(Args &&... args) -> decltype(this->_func(args...))
    {
        return this->_func(args...);

	}

};


#endif //SPIDERCLIENT_IDELEGATE_HPP
