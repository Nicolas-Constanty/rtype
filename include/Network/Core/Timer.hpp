//
// Created by gaspar_q on 12/14/16.
//

#ifndef RTYPE_PINGI_HPP
#define RTYPE_PINGI_HPP


#include <chrono>
#include "Common/DLLexport.hpp"

namespace Network
{
    namespace Core
    {
        class PREF_EXPORT Timer
        {
        public:
            Timer();
            Timer(Timer const &ref);
            ~Timer();

        public:
            void refresh();
            bool timeout(std::chrono::milliseconds const &limit) const;

        private:
            std::chrono::time_point<std::chrono::steady_clock>   lastPing;
        };
    }
}


#endif //RTYPE_PINGI_HPP
