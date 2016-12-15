#pragma once

#ifndef RECT_HPP_
#define RECT_HPP_

#include "SaltyEngine/Vector2.hpp"
#include "SaltyEngine/IRect.hpp"
#include "Common/Debug.hpp"

namespace SaltyEngine
{
	template <class T>
	class BasicRect : public IRect<T>
	{
	public:
		BasicRect(int l, int t, int w, int h) : IRect<T>(), _left(l), _top(t), _width(w), _height(h) {};
		~BasicRect() {};

	public:
		bool Contain(const T &) const override {
			return false;
		};

		bool _Contain(const Vector2 &vec) const
		{
			return (vec.x > _left && vec.y > _top &&
			vec.x < _left + _width && vec.y < _top + _height);
		}

		virtual bool Intersect(IRect<T> * const rect) const
		{
			::SaltyEngine::BasicRect<T> *r = dynamic_cast<::SaltyEngine::BasicRect<T> *>(rect);
            if (!r)
                return false;
			Vector2 topleft(static_cast<float>(r->_left), static_cast<float>(r->_top));
			Vector2 topright(static_cast<float>(r->_left + r->_width), static_cast<float>(r->_top));
			Vector2 downleft(static_cast<float>(r->_left), static_cast<float>(r->_top + r->_height));
			Vector2 downright(static_cast<float>(r->_left + r->_width), static_cast<float>(r->_top + r->_height));

            bool ret = (_Contain(topleft) || _Contain(topright) ||
                        _Contain(downleft) || _Contain(downright));
            //Istd::cout << topleft << " " <<  _left << " " << _top << std::endl;
            if (ret)
            {
                std::cout << "==========================================================" << std::endl;
                std::cout << _left << ", " << _top << ", " << _width<< ", " << _height << std::endl;
                std::cout << r->_left << ", " << r->_top << ", " << r->_width<< ", " << r->_height << std::endl;
            }
			return ret;
		};

	public:
		int _left;
		int _top;
		int _width;
		int _height;
	};
}

#endif // !RECT_HPP_

