//
// Created on 7/14/20.
//

#ifndef PACPAC_LEVEL_H
#define PACPAC_LEVEL_H

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include <filesystem>
#include <vector>

class Level
{
public:
    enum Tile {
        AIR = -1,           // Able to pass through without any problems
        WALL,               // Solid tile
        DOOR = 16,          // Solid tile where we can pass through for a set amount of time
        PACPAC,             // Tries to clear a level by collecting every pickup
        SLIME,              // Tries to kill Pacpac
        COIN,               // Gives score
        APPLE,              // Gives Pacpac the ability to kill slimes for a set amount of time
    };

public:
    /**
     * Load a level from a file
     * @param level_filename The path to a .json file containing the level data
     * @param registry A reference to an EnTT registry
     */
    explicit Level( const std::filesystem::path& level_filename, entt::registry& registry );

    /**
     * Get the tile from a position
     * @param position The position where the tile is
     * @return The tile at the provided position
     */
    [[nodiscard]] const Tile& get( const glm::ivec2& position ) const;

    /**
     * Get the tile from a position
     * @param position The position where the tile is
     * @return A reference to the tile at the provided position
     */
    Tile& get( const glm::ivec2& position );

private:
    entt::registry& m_registry;

    std::vector< Tile > m_tiles{};
    unsigned int m_width = 0;
    unsigned int m_height = 0;
};


#endif // PACPAC_LEVEL_H
