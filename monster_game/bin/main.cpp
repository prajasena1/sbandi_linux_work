// Author : S Bandi
#include <iostream>
#include <sstream>
#include <cstring>
#include "../lib/map_data.h"
#include "../lib/monster.h"

void print_usage(char * name)
{
    std::cout << "Usage : " << name << " -map_file map_file_location -num_mon number_of_monsters \n";
    std::cout << "Please supply number of monsters to play the game" << std::endl;
}

static const char * MAP_FILE_ARG = "-map_file";
static const char * NUM_MONSTERS = "-num_mon";
static const char * DEBUG_LEVEL = "-debug";
static const char * NUM_ITERS = "-num_iter";
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage(argv[0]);
        return 1;
    }

    // Parse cmd line args
    int num_monsters = 0;
    int debug_level = 0;
    int num_iters = 10000;
    std::string map_file_loc;
    for ( int i = 1; i < argc; ++i )
    {
        if ( !strcasecmp(argv[i], MAP_FILE_ARG) )
        {
            ++i;
            map_file_loc = std::string(argv[i]);
        }
        else if (!strcasecmp(argv[i], NUM_MONSTERS))
        {
            ++i;
            std::istringstream cmdline_str(argv[i]);
            cmdline_str >> num_monsters;
        }
        ///useful for dev/test
        else if (!strcasecmp(argv[i], DEBUG_LEVEL))
        {
            ++i;
            std::istringstream cmdline_str(argv[i]);
            cmdline_str >> debug_level;
        }
        ///useful for dev/test
        else if (!strcasecmp(argv[i], NUM_ITERS))
        {
            ++i;
            std::istringstream cmdline_str(argv[i]);
            cmdline_str >> num_iters;
        }
    }

    // verify cmd line args
    if (num_monsters == 0 || map_file_loc.empty())
    {
        std::cerr << "map_file_loc " << map_file_loc << " num_monsters " << num_monsters << std::endl;
        print_usage(argv[0]);
        return 1;
    }

    if (num_iters <= 0)
    {
        num_iters = 10000;
    }

    std::cout << "Playing the game with " << num_monsters << " monsters" << std::endl;

    // get map data
    MonsterGame::MapData map_data;
    if (!map_data.LoadData(map_file_loc))
    {
        std::cout << "Failed to load map file" << std::endl;
        return 3;
    }

    // setup MonsterController and provide mapdata
    MonsterGame::MonsterController commander(map_data, num_monsters);

    //play
    commander.Play(10000, debug_level);

    return 0;
}
