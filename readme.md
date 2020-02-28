# Eyos

Eyos is a student project to build a RTS that handles thousands (or millions) of units.  [Game Concept and Overview](https://github.com/Eothaun/Eyos/wiki/)

## Current Status

### Build

![C/C++ Build Windows (MSVC)](https://github.com/Eothaun/Eyos/workflows/C/C++%20Build%20Windows%20(MSVC)/badge.svg)
![C/C++ Build Linux (gcc9)](https://github.com/Eothaun/Eyos/workflows/C/C++%20Build%20Linux%20(gcc9)/badge.svg)
![C/C++ Build Linux (clang9)](https://github.com/Eothaun/Eyos/workflows/C/C++%20Build%20Linux%20(clang9)/badge.svg)

### Testing

![C/C++ Tests Linux](https://github.com/Eothaun/Eyos/workflows/C/C++%20Tests%20Linux/badge.svg)
![C/C++ Tests Windows](https://github.com/Eothaun/Eyos/workflows/C/C++%20Tests%20Windows/badge.svg)

## How to build

1. clone the repository

```bash
git clone https://github.com/Eothaun/Eyos.git
```

2.  Run cmake

```bash
$ cmake .
```

3. run make

```bash
$ make & make install
```
(*more information ot the cmake useage in our project: [cmake configuration](https://github.com/Eothaun/Eyos/wiki/cmake-Configuration)*)

or open our project in Visual Studio 19. For more information about this see [here](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019#installation).

4. run tests (This only works if the Option: `BUILD_TESTING` is set to ON)

```bash
$ ctest
```

You will see the tests.



### VS Settings

In Visual Studios you can modify the `CMakeSettings.json` file this will allow you to change rules in the `CMakeLists.txt` without changing it. (**This can be a source of error as well. Be aware!**)

Please download the [Clang Format VS Extension](https://marketplace.visualstudio.com/items?itemName=LLVMExtensions.ClangFormat)

## Dependencies

- [ENet](https://github.com/lsalzman/enet)
- [glm](https://github.com/g-truc/glm)
- [bgfx](https://github.com/bkaradzic/bgfx)
- [Catch2](https://github.com/catchorg/Catch2)
- [VLD](https://github.com/KindDragon/vld) *Optional on Windows: USE_VLD=ON*



## Documentation

- [Overview](https://github.com/Eothaun/Eyos/wiki/)
- [cmake configuration](https://github.com/Eothaun/Eyos/wiki/cmake-Configuration)
- [Coding Convention](#)
- [clang format settings](#)

## Team

- [Maiko Steeman](https://maikosteeman.dev/) Production, Engine Core Architecture & Graphics Programming
- [Marjolein Kaal](http://www.marjoleinkaal.com/) AI,Level Generation & Gameplay Systems
- [Simon Renger](https://simonrenger.com/) Network Architecture, Engine Architecture & QA Engineer 
- [Hannes Vernooij](https://www.hannesvernooij.com/) Gameplay Systems & Graphics Programming

Supervisor and special thanks go to [Bojan Endrovski](https://www.linkedin.com/in/bojanendrovski/)
