OO Design and Implementation by S Bandi
======================================

## How to build and test
GCC C++ compiler `g++` version 4.8.5 is used with option `-std=c++11`
If compiler supports switch `-std=c++14` - its better to use.

Execute below make commands for building and executing unit tests from directory where this `README.md` exists
* make -w -j 2

gtest (Google Unit Test) rpm is required for executing unit tests.
* make test

Some of the tests depends on entropy of randomness of machine.
If the failed test related to randomnes, please re-run the tests.

##### Command line args

```
Usage : ./bin/mongame -map_file map_file_location -num_mon number_of_monsters [-out_map file_location]
-map_file : file location with expected map format
-num_mon : Please supply number of monsters you want to unleash to destroy the map
-out_map : file where left over map is written after the end of game. DEFAULT to /tmp/leftover_map.txt
```

For playing the game with `100` monsters - follow below steps
```
./bin/mongame -map_file map.txt -num_mon 100
```

**Note**: Play can resumed from left over map by providing the `-map_file /tmp/leftover_map.txt`

## Class Design

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

### Test time measurement (Performance)
Unit test MapSetup.MapSetup shows that its consistently came as 13 ms (On RHEL VM Intel(R) Xeon(R) CPU X5660 @2.80GHz) for loading the map and presetup.
Unit test MonsterControllerTestCases.PlayTest provides measurement of actual play.
Unit test program accepts cmd line args `-num_mon N` and `-num_iter N` so that we can measure play time for varying number of iterations and monsters.

For 10K iterations and 1000 monsters - play is rougly taking 110 ms (On RHEL VM).

Follow below steps to measure time for varying number of iterations and monsters.
```
cd monster_game/lib/unit_tests
./mongame_utest --gtest_filter=*MapSetup*:*PlayTest* -num_iter 10000 -num_mon 1000
```

## Scope for improvement
* Enabling parallel random move of monsters can be achieved by using thread pool

