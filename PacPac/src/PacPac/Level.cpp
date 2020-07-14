//
// Created on 7/14/20.
//

#include "Level.h"

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

    std::ifstream file( level_filename );
    file.exceptions( std::ios_base::failbit );

    json j;
    file >> j;
}

const Level::Tile& Level::get( const glm::ivec2& position ) const {
    return m_tiles.at( position.x * m_height + position.y );
}

Level::Tile& Level::get( const glm::ivec2& position ) {
    return m_tiles.at( position.x * m_height + position.y );
}