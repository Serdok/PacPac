# PacPac

##### TL;DR
You are a slime, you hate the main protagonist, PacPac. Make it suffer as long as possible.

##### Description

WIP


### Get it on your PC

##### Requirements

- Your favorite GIT UI to pull and update git submodules
- [CMake](https://cmake.org/download/) version >= 3.16
- A compiler that supports C++20 as of July, 15th 2020 (I'm using [GCC-10.1](https://gcc.gnu.org/gcc-10/))

##### Steps

```shell script
git clone https://github.com/Serdok/PacPac
cd PacPac
git submodule update --init --recursive
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug   # Build in debug mode
cmake .. -DCMAKE_BUILD_TYPE=Release # Build in release mode
```

List of targets:

- PacPac - The game library. Take it and link it to your own project if you want to use different graphics
- Text - A text executable of the game. [(WIP)](https://github.com/Serdok/PacPac/projects/1)
- SFML - A 2D executable of the game. [(Very WIP)](https://github.com/Serdok/PacPac/projects/1)

Simply type `make <target_name>` to build the target.

-- temporary --

You'll have many executables depending on what graphics you want to use. They are located in your build directory under the Graphics/ directory.
The subdirectory (ie. Text/) indicates which graphics is used.

### Follow through

I'm trying to keep the [Kanban](https://github.com/Serdok/PacPac/projects/1) up to date on what I'm working on currently or what I'll be working on next.

### Credits

- [entt](https://github.com/skypjack/entt) for the Entity Component System
- [glm](https://github.com/g-truc/glm) for almost everything math-related 
- [JSON](https://github.com/nlohmann/json) for a C++ JSON parser