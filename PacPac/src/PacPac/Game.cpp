//
// Created on 7/15/20.
//

#include "Game.h"
#include "Updaters.h"
#include "Components/Position.h"
#include "Components/Direction.h"
#include "Components/TimedEffect.h"
#include "Components/Script.h"

#include <iostream>
#include <regex>
namespace fs = std::filesystem;

Game::Game( [[maybe_unused]] int argc, char** argv )
: m_level( m_registry )
{
    // Find the assets directory location
    searchAssetsDirectory( std::filesystem::path( argv[0] ).parent_path() );

    // Spawn a 'timer' entity that will change directions every 3 seconds
    auto entity = m_registry.create();
    std::chrono::microseconds t = 3s;
    m_registry.emplace< Script >( entity );
    m_registry.emplace< TimedEffect >( entity, t );

    // Register observers
    m_time_observer.connect( m_registry, entt::collector.update< TimedEffect >() );
    m_direction_observer.connect( m_registry, entt::collector.update< Direction >().where< Position >() );

    // Register internal event listeners
    once< GameEnd >( []( const GameEnd& event, Game& game ) { game.onGameEnd( event ); } );
    on< UpdateDirection >( []( const UpdateDirection&, Game& game ) {
        std::cout << "\t== updating directions... ==\n";
        auto update_directions = Updaters::direction_updater( game.m_registry, game.m_level );
        game.m_registry.view< Position, Direction >().each( update_directions );
    } );
}

void Game::searchAssetsDirectory( const std::filesystem::path& start, int lookup_depth ) {
    m_assets_path = start;

    // Match against 'assets' or 'Assets' directory names
    const std::regex assets_regex( R"(^[Aa]ssets$)", std::regex::ECMAScript );

    for (auto depth = 0; depth < lookup_depth; depth += 1) {
        for (const auto& entry : fs::directory_iterator( m_assets_path, fs::directory_options::skip_permission_denied )) {
            if (not entry.is_directory()) {
                continue;
            }

            const auto& directory_name = entry.path().stem();
            if (std::regex_match( directory_name.string(), assets_regex )) {
                // Match in the directory name
                m_assets_path = entry;

                // Cleanup the path
                fs::canonical( m_assets_path );
                return;
            }
        }

        // Directory not found, go up a directory
        m_assets_path /= "..";
    }

    // Directory not found
    throw std::runtime_error( "assets/ directory not found with a lookup depth of " + std::to_string( lookup_depth ) );
}

void Game::loadLevel( const std::filesystem::path& level_filename ) {
    m_level.load( m_assets_path / level_filename );
}

void Game::update( const std::chrono::microseconds& dt ) {
    if (m_done) {
        return;
    }

    // Update any timed scripts
    m_registry.view< Script, TimedEffect >().each( Updaters::timed_effect_updater( m_registry, dt ) );

    // Process observers
    m_time_observer.each( Updaters::Observers::signal_direction_update( m_registry, *this ) );
    m_direction_observer.each( Updaters::Observers::position_updater( m_registry ) );
}

void Game::onGameEnd( const GameEnd& event ) {
    m_done = true;
}

bool Game::isDone() const {
    return m_done;
}
