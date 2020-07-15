//
// Created on 7/15/20.
//

#ifndef PACPAC_RANDOM_H
#define PACPAC_RANDOM_H

#include <concepts>
#include <random>

namespace Random {
    /**
     * Generate a random integer number
     * @tparam T The type of the integer (unsigned short, int, ..., long long)
     * @param low The lowest possible value that can be generated
     * @param high The highest possible value that can be generated
     */
    template< typename T > requires std::is_integral_v< T >
    auto generate = []( T low, T high ) {
        auto generator = [
                distribution = std::uniform_int_distribution< T >( low, std::nextafter( high, std::numeric_limits< T >::max() ) ),
                random_engine = std::mt19937_64( std::random_device()() )
        ]() mutable {
            return static_cast<T>(distribution( random_engine ));
        };

        return generator;
    };
}

#endif // PACPAC_RANDOM_H
