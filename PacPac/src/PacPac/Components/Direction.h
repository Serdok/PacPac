//
// Created on 7/15/20.
//

#ifndef PACPAC_DIRECTION_H
#define PACPAC_DIRECTION_H

#include <glm/glm.hpp>

struct Direction {
    int x = 0;
    int y = 0;

    Direction() = default;
    Direction( int x, int y ) : x( x ), y( y ) {}
    explicit Direction( const glm::ivec2& direction ) : x( direction.x ), y( direction.y ) {}

    Direction( const Direction& ) = default;
    Direction& operator =( const Direction& ) = default;
    Direction& operator =( const glm::ivec2& rhs ) {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }

    Direction& operator +=( const glm::ivec2& rhs ) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Direction& operator -=( const glm::ivec2& rhs ) {
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

#endif // PACPAC_DIRECTION_H
