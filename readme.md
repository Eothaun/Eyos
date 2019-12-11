# Eyos

Eyos is a student project to build a RTS that handles thousands of units.



## How to build

1. clone the repository

```bash
git clone --recurse-submodules https://github.com/Eothaun/Eyos.git
```

As alternative you can run:
```bash
$ sh tools/gitsubmoduleinit.sh
```

2. run cmake

```bash
$ cmake .
```

3. run make

```bash
$ make & make install
```



## Dependencies



- [ENet](https://github.com/lsalzman/enet)
- [glm](https://github.com/g-truc/glm)
- [bgfx](https://github.com/bkaradzic/bgfx)



## Documentation

- [Overview](/docs)
- [Coding Convention](#)
- [clang format settings](#)