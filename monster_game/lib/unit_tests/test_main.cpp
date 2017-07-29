#include <gtest/gtest.h>

namespace
{
    // file scope vars
    // cmd line args
    const char * NUM_MONSTERS = "-num_mon";
    const char * NUM_ITERS = "-num_iter";
}

int g_num_iter = 100;
int g_num_monsters = 100;

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    for ( int i = 1; i < argc; ++i )
    {
        if (!strcasecmp(argv[i], NUM_MONSTERS))
        {
            ++i;
            std::istringstream cmdline_str(argv[i]);
            cmdline_str >> g_num_monsters;
        }
        else if (!strcasecmp(argv[i], NUM_ITERS))
        {
            ++i;
            std::istringstream cmdline_str(argv[i]);
            cmdline_str >> g_num_iter;
        }
    }
    return RUN_ALL_TESTS();
}
