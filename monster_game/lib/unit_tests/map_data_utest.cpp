#include <gtest/gtest.h>
#include "../map_data.h"

namespace
{
    const std::string       g_map_file_for_test = "../../map.txt";
    const size_t            g_num_valid_places = 6763;
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

                std::string place = m_map_data.GetRandomLocation();
                EXPECT_GE(m_map_data.GetNumberOfOutRoutes(place), 1);

                std::string destination;
                EXPECT_EQ(1, m_map_data.MakeRandomMove(place, destination));

                m_map_data.DestroyLocation(place);
                EXPECT_EQ(g_num_valid_places-1, m_map_data.GetNumPlaces());

                m_map_data.DestroyLocation(destination);
                EXPECT_EQ(g_num_valid_places-2, m_map_data.GetNumPlaces());
            }

        private:
            MapData m_map_data;
            bool        m_setup;
    };

    TEST_F(MapDataTestCases, MapLoadTest)
    {
        LoadDataTest();
    }
}
