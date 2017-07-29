#include <gtest/gtest.h>
#include <fstream>
#include <algorithm>
#include "../map_data.h"
#include "../monster.h"

extern int g_num_iter;
extern int g_num_monsters;

namespace
{
    const std::string           g_map_file_for_test = "../../map.txt";
    const std::string           g_map_out_file = "/tmp/left_over_map_utest.txt";
    const size_t                g_num_valid_places = 6763;
    MonsterGame::MapData        g_map_data;
    std::vector<std::string>    g_original_map_content;
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
                for (int i = 0; i < g_num_iter; ++i)
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

    void ReadFileContent(const std::string & file, std::vector<std::string> &content)
    {
        std::ifstream infile(file);
        std::string line;
        while (std::getline(infile, line))
        {
            if (!line.empty())
            {
                content.push_back(line);
            }
        }
    }

    TEST(MapSetup, MapSetup)
    {
        EXPECT_EQ(1, g_map_data.LoadData(g_map_file_for_test));
    }

    // Compare original map versus left over before any fight (destruction)
    // Purpose: test to verify map file read, preparation of data struct
    // and out file
    TEST(VerifyMapInOut, VerifyMapInOut)
    {
        std::vector<std::string>    written_map_content;

        g_map_data.PrintCurrentMap(g_map_out_file);

        ReadFileContent(g_map_file_for_test, g_original_map_content);
        ReadFileContent(g_map_out_file, written_map_content);

        // leftover map must have same number of places than original map
        EXPECT_EQ(g_original_map_content.size(), written_map_content.size());

        std::sort(g_original_map_content.begin(), g_original_map_content.end());
        std::sort(written_map_content.begin(), written_map_content.end());

        EXPECT_EQ(g_original_map_content.size(), written_map_content.size());

        // sorted leftover map must match with sorted original map
        EXPECT_EQ(1, (g_original_map_content == written_map_content));
    }

    TEST_F(MonsterControllerTestCases, SetupTest)
    {
        SetupTest();
    }

    TEST_F(MonsterControllerTestCases, PlayTest)
    {
        PlayTest();
    }

    // Compare original map versus left over
    TEST(ProduceLeftoverMap, ProduceLeftoverMap)
    {
        // save current leftover map
        g_map_data.PrintCurrentMap(g_map_out_file);

        std::vector<std::string>    written_map_content;
        ReadFileContent(g_map_out_file, written_map_content);

        // leftover map must have less number of places than original map
        EXPECT_LT(written_map_content.size(), g_original_map_content.size());

        std::sort(written_map_content.begin(), written_map_content.end());
        // sorted leftover map must not match with sorted original map
        EXPECT_EQ(0, (g_original_map_content == written_map_content));
    }

    // Verify leftovermap can reused
    TEST(ReuseLeftoverMap, ReuseLeftoverMap)
    {
        MonsterGame::MapData        map_data;
        EXPECT_EQ(1, map_data.LoadData(g_map_out_file));
    }
}
