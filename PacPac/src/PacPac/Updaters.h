//
// Created on 7/15/20.
//

#ifndef PACPAC_UPDATERS_H
#define PACPAC_UPDATERS_H

#include "Events.h"
#include "Level.h"
#include "Random.h"
#include "Components/Position.h"
#include "Components/Direction.h"
#include "Components/TimedEffect.h"

#include <entt/entt.hpp>

#include <chrono>

/**
 * Contains all updater functions
 */
namespace Updaters {
    // Return type alias
    using direction_updater_return_type = std::function< void( entt::entity, const Position& , const Direction& ) >;

    /**
     * Generate a function to update directions of all entities relative to a level.
     * This interacts with the Position and Direction components
     * @param registry The EnTT registry containing all entities
     * @param level The level to move in
     * @return A function with the signature void (*func)( entt::entity, const Position&, const Direction& ) to use with EnTT
     */
    direction_updater_return_type direction_updater( entt::registry& registry, const Level& level );

    // Return type alias
    using timed_effect_updater_return_type = std::function< void( entt::entity, const TimedEffect& ) >;

    /**
     * Generate a function to update timed effect countdowns of all entities
     * This interacts with the TimedEffect component
     * @param registry The EnTT registry containing all entities
     * @param dt The time between the current tick and the previous tick
     * @return A function with the signature void (*func)( entt::entity, const TimedEffect& ) to use with EnTT
     */
    timed_effect_updater_return_type timed_effect_updater( entt::registry& registry, const std::chrono::microseconds& dt );

    /**
     * Contains all updater functions used in observers
     */
    namespace Observers {
        // Return type alias
        using updater_return_type = std::function< void( entt::entity ) >;

        /**
         * Generate a function to update the Position component of all entities when a Direction component was updated.
         * Best used in an EnTT observer. This interacts with the Position and Direction components
         * @param registry The EnTT registry containing all entities
         * @return A function with the signature void (*func)( entt::entity ) to use with EnTT
         */
        updater_return_type position_updater( entt::registry& registry );


        /**
         * Signal EnTT to update the Direction component of all entities when a TimedEffect component was updated
         * @tparam E The type of the EnTT emitter
         * @param registry The EnTT registry containing all entities
         * @param emitter The EnTT emitter used to signal the update
         */
         template< typename E >
        updater_return_type signal_direction_update( entt::registry& registry, entt::emitter< E >& emitter ) {
            return [&]( auto entity ) {
                // Get the updated timed effect
                auto& timed_effect = registry.get< TimedEffect >( entity );

                if (timed_effect.time_remaining.count() == 0 and timed_effect.effect == TimedEffect::Effect::CHANGE_DIRECTION) {
                    // Signal
                    emitter.template publish< UpdateDirection >();

                    // Restart the timed effect
                    registry.patch< TimedEffect >( entity, []( auto& timed_effect ) {
                        timed_effect.time_remaining = timed_effect.total_duration;
                    } );
                }
            };
        }
    }
}

#endif // PACPAC_UPDATERS_H
