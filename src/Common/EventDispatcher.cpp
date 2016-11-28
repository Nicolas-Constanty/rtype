//
// Created by veyrie_f on 25/10/2016.
//

#include "common/EventDispatcher.hpp"

EventDispatcher::EventDispatcher() {

}

EventDispatcher::~EventDispatcher() {

}

bool EventDispatcher::AddListener(std::string const &id, boost::any delegate) {
    _events[id] = delegate;
    return false;
}

bool EventDispatcher::PushListener(boost::any delegate)
{
	_mutex.lock();
	_eventsQ.push(delegate);
	_mutex.unlock();
	return true;
}
