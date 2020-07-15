//
// Created on 7/14/20.
//

#include "Level.h"
#include "Components/Position.h"
#include "Components/Solid.h"
#include "Components/Direction.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <fstream>
#include <iostream>

Level::Level( const std::filesystem::path& level_filename, entt::registry& registry )
: m_registry( registry )
{
    if (level_filename.extension() != ".json") {
        std::string err = "Level::Level(): level_filename (which is '";
        err += level_filename;
        err += "') is not a .json file (the extension is '";
        err += level_filename.extension();
        err += "')";
        throw std::runtime_error( err );
    }

    // Open the file
    std::ifstream file( level_filename );
    file.exceptions( std::ios_base::failbit );

    // Read the file
    json j;
    file >> j;

    // Load the level
    m_width = j["width"].get< int >();
    m_height = j["height"].get< int >();
    m_tiles.resize( m_width * m_height );
    for (auto x = 0; x < m_height; x += 1) {
        for (auto y = 0; y < m_width; y += 1) {
            auto pos = x * m_width + y;
            auto tile = j["tiles"][pos].get< int >();
            m_tiles[pos] = static_cast<Tile>(tile);

            if (tile == Tile::AIR) {
                // Air tile, skip
                continue;
            }

            if (tile == Tile::DOOR) {
                // Door tile, ignore for the moment
                // @TODO Implement this
                continue;
            }

            // If we are here the current tile has to be a wall
            m_tiles[pos] = Tile::WALL;
            auto entity = m_registry.create();
            m_registry.emplace< Position >( entity, glm::ivec2( x, y ) );
            m_registry.emplace< Solid >( entity, tile );
        }
    }

    // Load the entities
    auto entities = j["entities"];
    {
        auto pacpac = entities["PacPac"];
        auto entity = m_registry.create();
        m_registry.emplace< Position >( entity, glm::ivec2( pacpac["x"].get< int >(), pacpac["y"].get< int >() ) );
        m_registry.emplace< Direction >( entity );
    }

    {
        auto slimes = entities["Slimes"];
        for (const auto& slime : slimes) {
            auto entity = m_registry.create();
            m_registry.emplace< Position >( entity, glm::ivec2( slime["x"].get< int >(), slime["y"].get< int >() ) );
            m_registry.emplace< Direction >( entity );
        }
    }
}

const Level::Tile& Level::get( const glm::ivec2& position ) const {
    return m_tiles.at( position.x * m_width + position.y );
}

Level::Tile& Level::get( const glm::ivec2& position ) {
    return m_tiles.at( position.x *  m_width + position.y );
}

bool Level::isWall( const glm::ivec2& position, const glm::ivec2& direction ) const {
    try {
        return get( position + direction ) == Tile::WALL;
    } catch (std::out_of_range&) {
        // Position + direction is out of bounds, so it WILL collide
        return true;
    }
}

std::vector< glm::ivec2 > Level::getNeighbouringTiles( const glm::ivec2& position ) const {
    std::vector< glm::ivec2 > directions{};

    if (not isWall( position, glm::ivec2( -1, 0 ) )) {
        // Left is available
        directions.emplace_back( -1, 0 );
    }
    if (not isWall( position, glm::ivec2( 1, 0 ) )) {
        // Right is available
        directions.emplace_back( 1, 0 );
    }
    if (not isWall( position, glm::ivec2( 0, -1 ) )) {
        // Up is available
        directions.emplace_back( 0, -1 );
    }
    if (not isWall( position, glm::ivec2( 0, 1 ) )) {
        // Down is available
        directions.emplace_back( 0, 1 );
    }

    return directions;
}
