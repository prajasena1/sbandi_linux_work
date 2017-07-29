#include <gtest/gtest.h>
#include "../map_data.h"

namespace
{
    const std::string       g_map_file_for_test = "../../map.txt";
    const size_t            g_num_valid_places = 6763;
    const std::string       g_place1 = "Denalmo";
    std::set<std::string>   g_place1_surroundings = {"Agixo-A", "Amolusnisnu", "Elolesme", "Migina"};
    const std::string       g_place2 = "Elnilminigu";
}

namespace MonsterGame
{
    class MapDataTestCases : public ::testing::Test
    {
        public:
            MapDataTestCases() : m_setup(false) {}
        protected:
            virtual void SetUp()
            {
                m_setup = m_map_data.LoadData(g_map_file_for_test);
            }

            virtual void TearDown()
            {
            }

            void LoadDataTest()
            {
                EXPECT_EQ(1, m_setup);

                EXPECT_EQ(1, m_map_data.IsDataExists());
                EXPECT_EQ(g_num_valid_places, m_map_data.GetNumPlaces());
            }

            void GetRandomPlaceOnMap()
            {
                std::string place = m_map_data.GetRandomLocation();
                std::string place2 = m_map_data.GetRandomLocation();
                // verify if the place dont match
                // Depends on entropy of randomess on machine where tests are run
                std::cout << "\nUnit test of Get Random Location test: depends on entropy of randomess on machine where tests are run\n"
                          << "If running on machine with low entropy of randomness, rerun to verify if tests pass" << std::endl;
                EXPECT_EQ(0, (place == place2));
            }

            void DestroySurroundingAfterRandomMove()
            {
                EXPECT_EQ(4, m_map_data.GetNumberOfOutRoutes(g_place1));

                // random move from place should get one of 4 surrounding places
                std::string destination;
                EXPECT_EQ(1, m_map_data.MakeRandomMove(g_place1, destination));
                EXPECT_EQ(1, (g_place1_surroundings.find(destination) != g_place1_surroundings.end()));

                // Tricky test to verify if MakeRandomMove gives different destination in 4 iterations
                // Depends on entropy of randomess on machine where tests are run
                bool random_destination_produced(false);
                for  (int i = 0; i < 4;  ++i)
                {
                    std::string destination2;
                    EXPECT_EQ(1, m_map_data.MakeRandomMove(g_place1, destination2));
                    EXPECT_EQ(1, (g_place1_surroundings.find(destination2) != g_place1_surroundings.end()));
                    if (destination != destination2)
                    {
                        random_destination_produced = true;
                        break;
                    }
                }
                std::cout << "\nUnit test of Get surrounding place from random selected direction: depends on entropy of randomess on machine where tests are run\n"
                          << "If running on machine with low entropy of randomness, rerun to verify if tests pass" << std::endl;
                EXPECT_EQ(1, random_destination_produced);

                // destroy a surrounding place and verify if out routes are reduced
                // also total number of places in map are reduced
                m_map_data.DestroyLocation(destination);
                EXPECT_EQ(3, m_map_data.GetNumberOfOutRoutes(g_place1));
                EXPECT_EQ(g_num_valid_places-1, m_map_data.GetNumPlaces());
            }

            void DeleteAllSurroundingPlaces()
            {
                EXPECT_EQ(3, m_map_data.GetNumberOfOutRoutes(g_place2));

                std::string destination;
                EXPECT_EQ(1, m_map_data.MakeRandomMove(g_place2, destination));

                m_map_data.DestroyLocation(destination);
                EXPECT_EQ(2, m_map_data.GetNumberOfOutRoutes(g_place2));
                EXPECT_EQ(g_num_valid_places-1, m_map_data.GetNumPlaces());

                EXPECT_EQ(1, m_map_data.MakeRandomMove(g_place2, destination));
                m_map_data.DestroyLocation(destination);
                EXPECT_EQ(1, m_map_data.GetNumberOfOutRoutes(g_place2));
                EXPECT_EQ(g_num_valid_places-2, m_map_data.GetNumPlaces());

                EXPECT_EQ(1, m_map_data.MakeRandomMove(g_place2, destination));
                m_map_data.DestroyLocation(destination);
                EXPECT_EQ(0, m_map_data.GetNumberOfOutRoutes(g_place2));

                // All surrounding places og g_place2 are deleted
                // g_place2 will become isolated so it also gets deleted from map
                EXPECT_EQ(g_num_valid_places-4, m_map_data.GetNumPlaces());

                EXPECT_EQ(0, m_map_data.MakeRandomMove(g_place2, destination));
            }

        private:
            MapData m_map_data;
            bool        m_setup;
    };

    TEST_F(MapDataTestCases, MapLoadTest)
    {
        LoadDataTest();
    }

    TEST_F(MapDataTestCases, GetRandomPlaceOnMap)
    {
        GetRandomPlaceOnMap();
    }
    TEST_F(MapDataTestCases, RandomMoveDestroyPlace)
    {
        DestroySurroundingAfterRandomMove();
    }

    TEST_F(MapDataTestCases, DeleteAllSurroundingPlaces)
    {
        DeleteAllSurroundingPlaces();
    }
}
