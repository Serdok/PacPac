//
// Created on 7/12/20.
// The aim of this executable is to have a "playground" to test basic functionalities before going 2D (or more ? :p)
//

#include <PacPac/Cell.h>
#include <vector>
#include <iostream>
#include <stdexcept>


int main( [[maybe_unused]] int argc, [[maybe_unused]] char* argv[] ) {
    try {
        const unsigned int width = 3;
        const unsigned int height = 3;
        const unsigned char level[] = {
                '#', '#', '#',
                '#', '.', '#',
                '#', '#', '#',
        };

        // Read the level
        std::vector< Cell > cells{};
        for (const auto& cell : level) {
            switch (cell) {
                case Cell::Type::WALL:
                case Cell::Type::AIR:
                case Cell::Type::COIN:
                case Cell::Type::PACPAC:
                case Cell::Type::SLIME:
                case Cell::Type::APPLE:
                    cells.emplace_back();
                    cells.back().setType( static_cast<Cell::Type>(cell) );
                    cells.back().setPosition( Vector2< int >::One() );
                    break;
                default:
                    std::string err = "Unrecognized cell ";
                    err.push_back( cell );
                    err.push_back( '\n' );
                    throw std::runtime_error( err );
            }
        }

        return 0;
    } catch (std::runtime_error& e) {
        std::cerr << e.what();
    }
}