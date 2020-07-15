//
// Created on 7/15/20.
//

#ifndef PACPAC_GAME_H
#define PACPAC_GAME_H

#include "Level.h"
#include "Events.h"

#include <entt/entt.hpp>

#include <chrono>
#include <filesystem>
using namespace std::chrono_literals;

class Game : public entt::emitter< Game >
{
public:
    Game( int argc, char* argv[] );

    /**
     * Load a level from a .json file
     * @param level_filename The path to a .json file
     */
    void loadLevel( const std::filesystem::path& level_filename );

    /**
     * Update the game
     * @param dt The time elapsed since the last update
     */
    void update( const std::chrono::microseconds& dt );

    /**
     * Check if the game has ended
     * @return true if the game has ended
     */
    bool isDone() const;

private:
    void searchAssetsDirectory( const std::filesystem::path& start, int lookup_depth = 5 );

    void onGameEnd( const GameEnd& event );

private:
    std::filesystem::path m_assets_path;

    entt::registry m_registry;
    entt::observer m_time_observer;
    entt::observer m_direction_observer;

    Level m_level;
    bool m_done = false;
};


#endif // PACPAC_GAME_H
