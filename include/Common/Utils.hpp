//
// Created by wery_a on 28/11/16.
//

#ifndef RTYPE_MAKEUNIQUE_HPP
#define RTYPE_MAKEUNIQUE_HPP

#include <memory>

template<typename T, typename... Args>
std::unique_ptr<T> Make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template< typename ContainerT, typename PredicateT >
void erase_if( ContainerT& items, const PredicateT& predicate ) {
    for( auto it = items.begin(); it != items.end(); ) {
        if( predicate(*it) ) it = items.erase(it);
        else ++it;
    }
};

#endif //RTYPE_MAKEUNIQUE_HPP
