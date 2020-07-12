//
// Created on 7/12/20.
//

#include "Cell.h"

Cell::Cell( Type type, const Vector2< int >& position, bool is_active )
: m_type( type ), m_position( position ), m_is_active( is_active )
{

}

void Cell::setType( Type type ) {
    m_type = type;
}

Cell::Type Cell::getType() const {
    return m_type;
}

void Cell::setPosition( const Vector2< int >& position ) {
    m_position = position;
}

const Vector2< int >& Cell::getPosition() const {
    return m_position;
}

void Cell::setActive( bool active ) {
    m_is_active = active;
}

bool Cell::isActive() const {
    return m_is_active;
}
