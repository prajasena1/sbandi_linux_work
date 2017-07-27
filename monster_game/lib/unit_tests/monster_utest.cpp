#include <gtest/gtest.h>
#include <fstream>
#include "../map_data.h"
#include "../monster.h"

namespace
{
    const std::string           g_map_file_for_test = "../../map.txt";
    const std::string           g_map_out_file = "/tmp/left_over_map_utest.txt";
    const size_t                g_num_valid_places = 6763;
    const int                   g_num_monsters = 100;
    MonsterGame::MapData        g_map_data;
}

namespace MonsterGame
{
    class MonsterControllerTestCases;
    class MonsterControllerUTest : public MonsterController
    {
        public:
            MonsterControllerUTest(MapData & map_data, int num_monsters)
                :
                    MonsterController(map_data, num_monsters)
        {
        }

        friend class MonsterControllerTestCases;
    };

    class MonsterControllerTestCases : public ::testing::Test
    {
        public:
            MonsterControllerTestCases()
                :
                    m_monster_controller(MonsterControllerUTest(g_map_data, g_num_monsters)){}
        protected:
            virtual void SetUp()
            {
            }

            virtual void TearDown()
            {
            }

            void SetupTest()
            {
                EXPECT_EQ(1, g_map_data.IsDataExists());
                EXPECT_EQ(g_num_monsters, m_monster_controller.GetLiveMonsterCount());

                // start of play so all monsters should move in one of random direction
                EXPECT_EQ(g_num_monsters, m_monster_controller.MoveAhead());

                m_monster_controller.Fight();
            }

            void PlayTest()
            {
                size_t start_num_places = g_map_data.GetNumPlaces();
                // Check to see if at least one place is destroyed
                for (int i = 0; i < 100; ++i)
                {
                    m_monster_controller.MoveAhead();
                    m_monster_controller.Fight();
                }

                // verify if atleast one city is destroyed
                EXPECT_LT(m_monster_controller.GetLiveMonsterCount(), g_num_monsters);
                EXPECT_LT(g_map_data.GetNumPlaces(), start_num_places);
            }

        private:
            MonsterControllerUTest   m_monster_controller;
    };

    TEST(MapSetup, MapSetup)
    {
        EXPECT_EQ(1, g_map_data.LoadData(g_map_file_for_test));
    }

    TEST_F(MonsterControllerTestCases, SetupTest)
    {
        SetupTest();
    }

    TEST_F(MonsterControllerTestCases, PlayTest)
    {
        PlayTest();
    }

    TEST(ProduceLeftoverMap, ProduceLeftoverMap)
    {
        g_map_data.PrintCurrentMap(g_map_out_file);

        std::ifstream infile(g_map_out_file);
        EXPECT_EQ(1, infile.is_open());

        // get file_length of file:
        infile.seekg (0, std::ios::end);
        EXPECT_GT(infile.tellg(), 100);
    }
}
