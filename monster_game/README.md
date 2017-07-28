Design and Implementation by S Bandi
===================================

## How to build
GCC C++ compiler `g++` version 4.8.5 is used with option `-std=c++11`
If compiler supports switch `-std=c++14` - its better to use.

Execute below make commands for building and executing unit tests from directory where this `README.md` exists
* make -w -j 2

gtest (Google Unit Test) rpm is required for executing unit tests.
* make test

For playing the game with `100` monsters - follow below steps
```
cd bin
./mongame -map_file ../map.txt -num_mon 100
```

## Design

##### MonsterGame::MapData
Entity to represent map containing the names of cities in the non-existent world.
* Provides interface to user 
    * load the map from text file
    * get random location on map
    * make a random move from a location

##### MonsterGame::Monster
Each individual monster will have one instance of this class

##### MonsterGame::MonsterController
Entity representing Evil Overlord.
* must have a `MonsterGame::MapData`. Without it, it can't function.
* will setup asked number of Monster objects and initializes them on random locations of map.
* Main method of Play is provided

### Integration Testing
For debugging and testing purpose, unexposed arguments can be suppplied to the program.
By default, `10,000` iterations are performed.
* To alter the iterations, `-num_iter N` can be supplied
* For debugging or testing in depth, `-debug 1|2` can be supplied

## Scope for improvement
* more unit tests for good coverage
* Enabling parallel random move of monsters can be achieved by using thread pool

