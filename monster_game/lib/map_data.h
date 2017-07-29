// map_data.h
// vi:set ts=4 sw=4 nowrap:
// Author : S Bandi

#ifndef MIMECAST_EXERCISE_MAP_DATA_H_ALREADY_INCLUDED
#define MIMECAST_EXERCISE_MAP_DATA_H_ALREADY_INCLUDED

#include <string>
#include <array>
#include <unordered_map>
#include <random>
#include <chrono>

namespace MonsterGame
{
    enum Direction
    {
        DIR_NORTH,
        DIR_SOUTH,
        DIR_EAST,
        DIR_WEST,
        DIR_MAX
    };

    std::string GetDirStr(Direction val);
    Direction GetDirEnum(const std::string &dir);

    // Entity to represent map containing the names of cities in the non-existent world
    class MapData
    {
        public:
            // value : array of 4 elements. 0th element indicates the name of place in DIR_NORTH,
            //          1st element indicates the name of place in DIR_SOUTH, etc. see enum Direction
            using location_outward_direction_t =  std::array<std::string, DIR_MAX>;

            MapData()
                : m_rand_gen_engine(std::chrono::system_clock::now().time_since_epoch().count())
            {
            }
            
            bool LoadData(const std::string &map_file);

            void DestroyLocation(const std::string &map_file_line);

            const std::string & GetRandomLocation() const;

            // get number of outgoing routes from a place
            int GetNumberOfOutRoutes(const std::string &location) const;

            //random move from_location to destination
            // if failed to move (because no outward routes) indicate by returning false
            bool MakeRandomMove(const std::string &from_location, std::string &destination) const;

            size_t  GetNumPlaces() const { return m_map_data.size(); }

            bool IsDataExists() const { return !m_map_data.empty(); }

            void PrintCurrentMap(const std::string &map_output_file) const;

        protected:
            bool AddLocationRegex(const std::string &map_file_line);
            bool AddLocation(const std::string &map_file_line, bool debug = false);

            void ClearInRoute(const std::string &location, const std::string &place_to_be_destroyed);

            //accessed during immutable methods
            //mutable std::default_random_engine      m_rand_gen_engine;
            mutable std::default_random_engine      m_rand_gen_engine {std::random_device{}()};
        private:
            // key location name
            // value: see location_outward_direction_t
            // hap table of fixed size arrays - no insertions after delete so works good
            // value type array for gaining performance with cache locality of reference
            // array of short strings containing places so SSO (Short String Optimization) ensures no seperate heap allocations.
            // value type map/hash array can be choice but they bring lot of overhead.
            // They always uses heap. array is best choice here based on theory
            // FIXME capture the performance measure in different runs
            std::unordered_map<std::string, location_outward_direction_t> m_map_data;
    };

} // end namespace MonsterGame
#endif
