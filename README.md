Frag Engine
===========

Frag Engine is a 3D game engine written in C++. It uses OpenGL for rendering.

Building
--------

Building this project requires CMake. Currently the only libraries used are
SDL2 and OpenGL.

After navigating to the root of this project, enter the following into your
terminal:

```sh
mkdir ../build-frag-engine &&
cd ../build-frag-engine &&
cmake ../frag-engine &&
make
```

A shared library will be created in the new build-frag-engine directory. You can
then use this in your projects.
