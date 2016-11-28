//
// Created by wery_a on 28/11/16.
//

#ifndef RTYPE_MAKEUNIQUE_HPP
#define RTYPE_MAKEUNIQUE_HPP

#include <memory>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif //RTYPE_MAKEUNIQUE_HPP
