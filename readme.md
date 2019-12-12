# Eyos

Eyos is a student project to build a RTS that handles thousands of units.



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

or open our project in Visual Studio 19. For more information about this see [here](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019#installation).

4. run tests (This only works if the Option: `BUILD_TESTING` is set to ON)

```bash
$ ctest
```

You will see the tests.



### VS Settings

In Visual Studios you can modify the `CMakeSettings.json` file this will allow you to change rules in the `CMakeLists.txt` without changing it. (**This can be a source of error as well. Be aware!**)

## Dependencies

- [ENet](https://github.com/lsalzman/enet)
- [glm](https://github.com/g-truc/glm)
- [bgfx](https://github.com/bkaradzic/bgfx)
- [Catch2](https://github.com/catchorg/Catch2)



## Documentation

- [Overview](/docs)
- [Coding Convention](#)
- [clang format settings](#)