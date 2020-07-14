//
// Created on 7/12/20.
// The aim of this executable is to have a "playground" to test basic functionalities before going 2D (or more ? :p)
//

#include <PacPac/Level.h>
#include <iostream>
#include <stdexcept>

#include <vector>

int main( [[maybe_unused]] int argc, [[maybe_unused]] char* argv[] ) {
    try {
        std::filesystem::path assets_path = std::filesystem::path( argv[0] ).parent_path();
        assets_path /= "..";
        assets_path /= "..";
        assets_path /= "..";
        assets_path /= "assets";
        std::cout << std::filesystem::canonical( assets_path ) << '\n';

        entt::registry r;

        Level l( assets_path / "levels/level0.json", r );

        return 0;
    } catch (std::ios_base::failure& e) {
        std::cerr << "Code " << e.code() << " - " << e.what() << '\n';
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}