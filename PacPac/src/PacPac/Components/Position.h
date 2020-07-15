//
// Created on 7/15/20.
//

#ifndef PACPAC_POSITION_H
#define PACPAC_POSITION_H

#include <glm/vec2.hpp>

struct Position {
    int x = 0;
    int y = 0;

    Position() = default;
    Position( int x, int y ) : x( x ), y( y ) {}
    explicit Position( const glm::ivec2& position ) : x( position.x ), y( position.y ) {}

    Position( const Position& ) = default;
    Position& operator =( const Position& ) = default;
    Position& operator =( const glm::ivec2& rhs ) {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }

    Position& operator +=( const glm::ivec2& rhs ) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Position& operator -=( const glm::ivec2& rhs ) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    glm::ivec2 toIVec2() const {
        return glm::ivec2( x, y );
    }

    operator glm::ivec2() const {
        return toIVec2();
    }
};

#endif // PACPAC_POSITION_H
