//
// Created by veyrie_f on 23/12/16.
//

#ifndef RTYPE_CUSTOMENUM_HPP
#define RTYPE_CUSTOMENUM_HPP

#include "ostream"

template< typename T>
class Enum
{
public:
    Enum() :
            m_value(T::E_FIRST),
            m_fist(T::E_FIRST),
            m_last(T::E_LAST + 1)
    {

    }

    T operator ++(void)
    {
        return T(this->m_value++);
    }

    T operator ++(int)
    {
        this->m_value = (this->m_value + 1) % m_last;
        return (T)(this->m_value);
    }

    bool operator==(const Enum<T> & other)
    {
        return m_value == other.m_value;
    }

    bool operator==(T other)
    {
        return m_value == other;
    }

    operator int()
    {
        return m_value;
    }

public:
    class Iterator
    {
    public:
        Iterator( int value ) :
                m_value( value )
        { }

        T operator*( void ) const
        {
            return (T)m_value;
        }

        int operator++( void )
        {
            return ++m_value;
        }

        int operator++(int )
        {
            return ++m_value;
        }

        bool operator!=( Iterator rhs )
        {
            return m_value != rhs.m_value;
        }

    private:
        int m_value;
    };

    template <class U>
    friend std::ostream &operator<<(std::ostream &stream, Enum<U> const& e);

private:
    int m_value;
    int m_fist;
    int m_last;
};

template< typename T >
typename Enum<T>::Iterator begin( Enum<T> )
{
    return typename Enum<T>::Iterator( (int)T::First );
}

template< typename T >
typename Enum<T>::Iterator end( Enum<T> )
{
    return typename Enum<T>::Iterator( ((int)T::Last) + 1 );
}

template <class U>
std::ostream &operator<<(std::ostream &stream, Enum<U> const& e)
{
    return stream << e.m_value;
}

#endif //RTYPE_CUSTOMENUM_HPP
