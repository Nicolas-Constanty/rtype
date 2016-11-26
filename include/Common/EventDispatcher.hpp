//
// Created by veyrie_f on 25/10/2016.
//

#ifndef SPIDERCLIENT_EVENTDISPATCHER_HPP
#define SPIDERCLIENT_EVENTDISPATCHER_HPP


#include <map>
#include <boost/any.hpp>
#include <queue>
#include "Singleton.hpp"
#include "Delegate.hpp"
#include <boost/thread/win32/shared_mutex.hpp>
#include "thread/BoostMutex.hpp"

/**
 * \brief EventDispatcher allow you to create events that will be dispatched on call.
 */
class EventDispatcher : public Singleton<EventDispatcher>
{
    friend class Singleton<EventDispatcher>;
private:
	EventDispatcher();
	virtual ~EventDispatcher();

public:
    /**
     * \brief Adds a listener referenced with an id, as a string.
     */
	bool AddListener(std::string const& id, boost::any delegate);
	/**
	 * \brief Pushes a delegate in the queue
	 */
	bool PushListener(boost::any delegate);

    /**
     * \brief Dispatch events matching a certain id.
     * By default, the expected return type is 'void'. However, you can specify
     * the type your desire in the template arguments.
     */
    template <class RetType = void, class ... Args>
	RetType Dispatch(std::string const& id, Args &&... args)
    {
        if (_events.find(id) != _events.end())
        {
            //std::cerr << "EventDispatcher (Warning): " + id + " not found in events." << std::endl;
            //throw std::runtime_error("Id " + id + " not found in events");

			Delegate< RetType(Args...) > delegate = *boost::any_cast< Delegate<RetType(Args...)> >(&_events[id]);
			return (delegate)(args...);
        }
        //Delegate< RetType(Args...) > delegate = *boost::any_cast< Delegate<RetType(Args...)> >(&_events[id]);
        //return (delegate)(args...);
		return (RetType)0;
    }

	/**
	 * \brief Dispatchs from queue.
	 */
	template <class RetType = void, class ... Args>
	RetType DispatchQ(Args &&... args)
	{
		_mutex.lock();
		if (_eventsQ.size() > 0)
		{
			Delegate< RetType(Args...) > delegate = *boost::any_cast< Delegate<RetType(Args...)> >(&_eventsQ.front());
			_eventsQ.pop();
			_mutex.unlock();
			return (delegate)(args...);
		}
		_mutex.unlock();
		return (RetType)0;
	}

	/**
	 * Erase an event from the event list matching the ID
	 */
	void Erase(std::string const& id)
	{
		if (_events.find(id) != _events.end())
		{
			_events.erase(id);
		}
	}

	bool IsQueueEmpty() const
    {
		return _eventsQ.empty();
    }

private:
    std::map<std::string, boost::any > _events;
	std::queue<boost::any> _eventsQ;
	BoostMutex	_mutex;
};


#endif //SPIDERCLIENT_EVENTDISPATCHER_HPP
