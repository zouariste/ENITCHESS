## ENITCHESS
* Drag and drop C++ game.
* Implementation of some basics artificial intelligence algorithms : Alpha–beta pruning - Minmax Algorithm.

## Screenshot
<div>
<img src="./enitchess/images/EnitChess.gif?raw=true" width="448" height="524"/>
</div>

## Prerequisite: Install SFML
```
sudo apt-get install libsfml-dev
```
## Now let's compile it: 
```
g++ -c main.cpp
```
## Let's now link the compiled file to the SFML libraries in order to get the final executable.
```
g++ main.o -o EnitChess -lsfml-graphics -lsfml-window -lsfml-system
```
## We are now ready to execute the compiled program:
```
./EnitChess
```
