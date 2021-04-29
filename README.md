# 75.42 - Taller de Programación I

Grupo Vegetal:
  * Ignacio Iglesias (@ignamiguel)
  * Cristian Rubio (@cdrubio)
  * Juan Ignacio Díaz (@Nacho-Dz)
  * Kailásh Aquista (@Aquista)
  * Ailín Yelén Braccelarghe (@ailinyelen)


## Cómo correr el test
1. Instalar SDL
```
sudo apt-get install libsdl2-2.0 libsdl2-dev
```

2. Instalar GCC y GDB
```
sudo apt-get install build-essential gdb
```

3. Compilar el ejemplo
```
g++ main.cpp -o main -Wall -Wextra -std=c++17 -ggdb -D_REENTRANT -I/usr/include/SDL2 -lSDL2 -Iinclude -Llib
```
