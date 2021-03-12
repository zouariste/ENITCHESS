## ENITCHESS
* Drag and drop C++ game, using the object-oriented programming approach.
* Practical realization and software simulation using SFML as the graphic interface library.
* Implementation of some basics artificial intelligence algorithms : Alpha–beta pruning - Minmax Algorithm.

## Screenshot

<div align="left">
  <img height="50%" width="50%" src="https://zouariste.github.io/mohamedzouari/img/portfolio/enitchess/2.png">
</div>

## Installing SFML
* sudo apt-get install libsfml-dev
## Now let's compile it: 
* g++ -c main.cpp
## You must then link the compiled file to the SFML libraries in order to get the final executable. SFML is made of 5 modules (system, window, graphics, network and audio), and there's one library for each of them. To link an SFML library, you must add "-lsfml-xxx" to your command line, for example "-lsfml-graphics" for the graphics module (the "lib" prefix and the ".so" extension of the library file name must be omitted). 
* g++ main.o -o EnitChess -lsfml-graphics -lsfml-window -lsfml-system
## We are now ready to execute the compiled program:
* ./EnitChess