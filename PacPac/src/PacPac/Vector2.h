//
// Created on 7/12/20.
//

#ifndef PACPAC_VECTOR2_H
#define PACPAC_VECTOR2_H

#include <concepts>

/**
 * Representation of a 2D vector. Can hold any arithmetic type (integers and floating points)
 * @tparam T The type of the vector (default: int)
 */
template< typename T = int > requires std::is_arithmetic_v< T >
struct Vector2
{
    T x = 0;
    T y = 0;

    constexpr Vector2() = default;
    constexpr Vector2( T x, T y ) : x( x ), y( y ) {}

    /**
     * Default equality operator
     * @param rhs The vector at the right-hand side of the operator
     * @return true if both vectors represent the same position
     */
    bool operator ==( const Vector2< T >& rhs ) const = default;

    /**
     * Deleted spaceship operator as it is not logical to compare two vectors if one is less than another
     * @param rhs The vector at the right-hand side of the operator
     */
    auto operator <=>( const Vector2< T >& rhs ) const = delete;

    static constexpr const Vector2< T > Zero() {
        return Vector2< T >( 0, 0 );
    }

    static constexpr const Vector2< T > One() {
        return Vector2< T >( 1, 1 );
    }
};


#endif // PACPAC_VECTOR2_H
