# NovaPx
A pixel art creation and animation tool written in C++ and OpenGL 4.5+

To build from source on Windows:
- Install MSYS2
- In the MSYS2 terminal:

pacman -S mingw-w64-x86_64-qt5

pacman -S mingw-w64-x86_64-jasper

pacman -S mingw-w64-x86_64-libpng

pacman -S mingw-w64-x86_64-zlib

pacman -S mingw-w64-x86_64-giflib

- Set up your IDE to use the MSYS2 mingw64 toolchain
- If you want to use the packaging script, change the paths inside package/assemble.sh, and in the MSYS2 terminal:

pacman -S zip
- Run package/assemble.sh with the mingw64 terminal
