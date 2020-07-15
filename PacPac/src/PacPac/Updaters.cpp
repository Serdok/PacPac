//
// Created on 7/15/20.
//

#include "Updaters.h"


namespace Updaters {
    direction_updater_return_type
    direction_updater( entt::registry& registry, const Level& level ) {
        return [&]( auto entity, const auto& position, [[maybe_unused]] const auto& direction ) {
            auto directions = level.getNeighbouringTiles( position );
            if (directions.empty()) {
                // No move is possible
                return;
            }

            // Choose a random direction
            auto generator = Random::generate< int >( 0, directions.size() - 1 );
            auto chosen_direction = directions.at( generator() );

            // Update the direction
            // By using patch(), we notify observers that a Direction component has been updated
            registry.patch< Direction >( entity, [chosen_direction]( auto& direction ) { direction = chosen_direction; } );
        };
    }

    timed_effect_updater_return_type
    timed_effect_updater( entt::registry& registry, const std::chrono::microseconds& dt ) {
        return [&]( auto entity, [[maybe_unused]] const auto& timed_effect ) {
            // Update the countdown
            // By using patch(), we notify observers that a TimedEffect component has been updated
            registry.patch< TimedEffect >( entity, [dt]( auto& timed_effect ) {
                timed_effect.time_remaining.count() >= dt.count()
                ? timed_effect -= dt
                : timed_effect.time_remaining = 0us;
            } );
        };
    }

    namespace Observers {
        updater_return_type position_updater( entt::registry& registry ) {
            return [&]( auto entity ) {
                // Get the updated direction
                const auto& direction = registry.get< Direction >( entity );

                // Update the position
                // By using patch(), we notify observers that a Position component has been updated
                registry.patch< Position >( entity, [=]( auto& position ) { position += direction; } );
            };
        }
    }
}
