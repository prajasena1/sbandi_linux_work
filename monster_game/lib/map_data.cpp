// map_data.cpp
// vi:set ts=4 sw=4 nowrap:
// Author : S Bandi

#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <regex>

#include "map_data.h"

namespace MonsterGame
{
    std::string GetDirStr(Direction val)
    {
        switch (val)
        {
            case DIR_NORTH:
                return "DIR_NORTH";
            case DIR_SOUTH:
                return "DIR_SOUTH";
            case DIR_EAST:
                return "DIR_EAST";
            case DIR_WEST:
                return "DIR_WEST";
            default:
                return "UNHANDLED_DIRECTION";
        }
    }

    Direction GetDirEnum(const std::string &dir)
    {
        static std::unordered_map<std::string, Direction> dir_map
            = { { "north", DIR_NORTH },
                { "south", DIR_SOUTH },
                { "east", DIR_EAST },
                { "west", DIR_WEST}
            };
        auto itor = dir_map.find(dir);
        if (itor == dir_map.end())
        {
            return DIR_UNHANDLED;
        }

        return itor->second;
    }

    bool MapData::LoadData(const std::string &map_file)
    {
        std::ifstream infile(map_file);
        if (!infile)
        {
            std::cerr << "Failed to open file " << map_file <<  strerror(errno) << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(infile, line))
        {
            if (line.empty())
            {
                continue;
            }
            //FIXME regex issues with gcc compiler 4.8
            //if (!AddLocationRegex(line))
            if (!AddLocation(line))
            {
                return false;
            }
        }
        return true;
    }

    // expected line format PlaceName outward_direction=SurroundingPlaceName ...
    // Example : Denalmo north=Agixo-A south=Amolusnisnu east=Elolesme west=Migina
    // Return False if inputline is not in expected format
    bool MapData::AddLocation(const std::string &line, bool debug)
    {
        std::string copy_line(line);
        std::string place;
        location_outward_direction_t loc_info;

        size_t pos = 0;
        const std::string place_delim(" ");
        const std::string dir_delim("=");
        if (debug) std::cout << "processing line " << copy_line << std::endl;
        while ((pos = copy_line.find(place_delim)) != std::string::npos)
        {
            if (place.empty())
            {
                place = copy_line.substr(0, pos);
                if (debug) std::cout << "extracted place " << place << std::endl;
            }
            else
            {
                std::string outward_dir = copy_line.substr(0, pos);
                if (debug) std::cout << "extracted dir " << outward_dir << std::endl;

                size_t dir_delim_pos = outward_dir.find(dir_delim);
                if (dir_delim_pos == std::string::npos)
                {
                    std::cerr << "input data not in expected format line "  << copy_line << std::endl;
                    return false;
                }

                std::string dir_str = outward_dir.substr(0, dir_delim_pos);
                std::string dir_place = outward_dir.substr(dir_delim_pos+dir_delim.length());
                if (debug) std::cout << "extracted " << dir_str << " " << dir_place << std::endl;

                enum Direction dir = GetDirEnum(dir_str);
                if (dir == DIR_UNHANDLED)
                {
                    std::cerr << "Invalid direction " << dir_str  << " from line  " << copy_line << std::endl;
                    return false;
                }
                loc_info[dir] = dir_place;
            }
            copy_line.erase(0, pos + place_delim.length());
            if (debug) std::cout << "now copy_line " << copy_line << std::endl;
        }
        m_map_data.emplace(place, loc_info);
        return true;
    }

    /// Requires regex supporting compiler
    // FIXME not thoroughly tested
    bool MapData::AddLocationRegex(const std::string &line)
    {
        std::smatch matches;
        std::regex re_expr("(\\b\\S*\\b)");

        std::string copy_line(line);
        std::string place;
        location_outward_direction_t loc_info;

        while (regex_search(copy_line, matches, re_expr))
        {
            if (place.empty())
            {
                place = matches[0];
                copy_line = matches.suffix();
            }
            else
            {
                std::string out_dir_string = matches[0] ;
                copy_line = matches.suffix();

                std::regex re_dir("(.*)=(.*)");
                std::smatch dir_matches;
                if (std::regex_match (out_dir_string, dir_matches, re_dir))
                {
                    std::cout << dir_matches[1] <<  " dir " << dir_matches[2] << std::endl;
                    enum Direction dir = GetDirEnum(dir_matches[1]);
                    if (dir == DIR_UNHANDLED)
                    {
                        std::cerr << "Invalid direction " << out_dir_string  << " from line  " << copy_line << std::endl;
                        return false;
                    }
                    else
                    {
                        loc_info[dir] = dir_matches[2];
                    }
                }
            }
        }
        m_map_data.emplace(place, loc_info);
        return true;
    }

    void MapData::DestroyLocation(const std::string &place_to_be_destroyed)
    {
        auto itor = m_map_data.find(place_to_be_destroyed);
        if (itor == m_map_data.end())
        {
            return;
        }

        const location_outward_direction_t & loc_info = itor->second;

        // clear all inroutes
        for (const auto & surrounding_location : loc_info)
        {
            ClearInRoute(surrounding_location, place_to_be_destroyed);
        }

        // delete the place from map
        m_map_data.erase(itor);
    }

    void MapData::ClearInRoute(const std::string &location, const std::string &place_to_be_destroyed)
    {
        auto itor = m_map_data.find(location);
        if (itor == m_map_data.end())
        {
            return;
        }

        location_outward_direction_t & loc_info = itor->second;
        int num_outroutes_from_this_place = max_num_out_routes;
        for (auto & surrounding_location : loc_info)
        {
            if (surrounding_location.empty())
            {
                --num_outroutes_from_this_place;
            }
            else if (surrounding_location == place_to_be_destroyed)
            {
                surrounding_location.clear();
                // Assumption - only one inroute exists from one place to other place
                break;
            }
        }

        // Assumption - a place without any outroute can be deleted from map because nobody can reach it
        // and anyone stuck on this place is perished
        if (num_outroutes_from_this_place == 0)
        {
            m_map_data.erase(itor);
        }
    }

    int MapData::GetNumberOfOutRoutes(const std::string &location) const
    {
        auto itor = m_map_data.find(location);
        if (itor == m_map_data.end())
        {
            return 0;
        }

        const location_outward_direction_t & loc_info = itor->second;
        int num_outroutes_from_this_place = max_num_out_routes;
        for (auto & surrounding_location : loc_info)
        {
            if (surrounding_location.empty())
            {
                --num_outroutes_from_this_place;
            }
        }

        return num_outroutes_from_this_place;
    }

    bool MapData::MakeRandomMove(const std::string &from_location, std::string &destination) const
    {
        auto itor = m_map_data.find(from_location);
        if (itor == m_map_data.end())
        {
            return false;
        }

        const location_outward_direction_t & loc_info = itor->second;
        int num_outroutes_from_this_place = max_num_out_routes;
        for (auto & surrounding_location : loc_info)
        {
            if (surrounding_location.empty())
            {
                --num_outroutes_from_this_place;
            }
        }

        if (!num_outroutes_from_this_place)
        {
            //Can't move forward because there is no outroute
            //all surrounding locations are destroyed
            return false;
        }

        std::uniform_int_distribution<int> dist(0, num_outroutes_from_this_place-1);
        // m_rand_gen_engine may changed but MapData state is unchanged
        int move_direction = dist(m_rand_gen_engine);
        //std::cout << "num_outroutes_from_this_place" << num_outroutes_from_this_place << " random direction " << move_direction << std::endl;
        int i = 0;
        for (auto & surrounding_location : loc_info)
        {
            if (!surrounding_location.empty())
            {
                if (move_direction == i)
                {
                    destination = surrounding_location;
                    return true;
                }
                ++i;
            }
        }

        // exception - should not reach unless any problems with above logic
        std::ostringstream msg;
        msg << "Failed to random move from location: "
            << from_location
            << " num_outroutes_from_this_place " << num_outroutes_from_this_place
            << " move_direction " << move_direction;

        throw std::runtime_error(msg.str());
    }

    const std::string & MapData::GetRandomLocation() const
    {
        std::uniform_int_distribution<size_t> dist(0, m_map_data.size()-1);
        // m_rand_gen_engine may changed but MapData state is unchanged
        size_t n = dist(m_rand_gen_engine);
        //std::cout << "position of random place " << n << std::endl;
        auto itor = std::next(m_map_data.begin(), n);
        return itor->first;
    }

} // end namespace MonsterGame
