//
// Created on 7/12/20.
// The aim of this executable is to have a "playground" to test basic functionalities before going 2D (or more ? :p)
//

#include <PacPac/Game.h>

#include <iostream>
#include <stdexcept>


int main( [[maybe_unused]] int argc, [[maybe_unused]] char* argv[] ) {
    try {
        Game game( argc, argv );
        game.loadLevel( "levels/level0.json" );

        auto start = std::chrono::steady_clock::now();
        auto total_time = 0us;
        constexpr std::chrono::microseconds end = 15s;
        while (not game.isDone()) {
            // Update clock
            auto now = std::chrono::steady_clock::now();
            auto dt = std::chrono::duration_cast< std::chrono::microseconds >(now - start);
            total_time += dt;
            start = now;

            if (total_time.count() >= end.count()) {
                // End the game
                game.publish< GameEnd >();
            }

            // Update game
            game.update( dt );

        }

        return 0;
    } catch (std::ios_base::failure& e) {
        std::cerr << "Code " << e.code() << " - " << e.what() << '\n';
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}