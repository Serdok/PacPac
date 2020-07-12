//
// Created on 7/12/20.
//

#ifndef PACPAC_CELL_H
#define PACPAC_CELL_H

#include "Vector2.h"

#include <iostream>

/**
 * Representation of a cell in the game.
 */
class Cell
{
public:
    // All possible cell types (max 256 distinct cells)
    enum Type : unsigned char {
        AIR = ' ',          // Cell without any special properties
        WALL = '#',         // Solid cell, entities cannot pass through
        COIN = '.',         // Gives 25 points when collected by PacPac
        PACPAC = 'p',       // MUST HAVE 1 PER LEVEL (spawn point)
        SLIME = 's',        // MUST HAVE 4 PER LEVEL (spawn point)
        APPLE = 'a',        // PacPac is able to eat Slimes for 15 (wip) seconds
    };

public:
    /**
     * Default constructor.
     */
    Cell() = default;

    /**
     * Constructor
     * @param type The type of the cell
     * @param position The position of the cell
     * @param is_active Set to true if the cell starts being active (default: yes)
     */
    Cell( Type type, const Vector2< int >& position, bool is_active = true );

    /**
     * Assign a new type to the cell
     * @param type The new type of the cell
     */
    void setType( Type type );

    /**
     * Get the current type of the cell
     * @return The current type of the cell
     */
    Type getType() const;

    /**
     * Assign a new position to the cell
     * @param position The new position of the cell
     */
    void setPosition( const Vector2< int >& position );

    /**
     * Get the current position of the cell
     * @return The current position of the cell
     */
    const Vector2< int >& getPosition() const;

    /**
     * Switch the active state of the cell
     * @param active true to set the cell to an active state, false otherwise
     */
    void setActive( bool active );

    /**
     * Get the active state of the cell
     * @return true if the cell is currently active
     */
    bool isActive() const;

private:
    Type m_type = Cell::Type::AIR;

    Vector2< int > m_position = Vector2< int >::Zero();
    bool m_is_active = true;
};


#endif // PACPAC_CELL_H
