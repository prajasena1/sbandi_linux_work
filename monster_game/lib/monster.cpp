// monster.cpp
// vi:set ts=4 sw=4 nowrap:
// Author : S Bandi

#include <iostream>
#include <sstream>
#include "map_data.h"
#include "monster.h"

namespace MonsterGame
{
    MonsterController::MonsterController(MapData & map_data, int num_monsters)
        :
            m_map_data(map_data)
    {
        for (int i=0; i < num_monsters; ++i)
        {
            // setup monster and set them on random place on map
            m_monsters_in_action.emplace_back(i, m_map_data.GetRandomLocation());
        }
    }

    void MonsterController::Play(const int max_iter, const int debug_level)
    {
        std::cout << COLOR_RED << "Start the play\n" << COLOR_DEFAULT;
        PrintSummary();
        PrintCurrentPosition();
        size_t num_start_places = m_map_data.GetNumPlaces(),
               num_start_monsters = GetLiveMonsterCount();

        int iter(0);
        // main work loop
        while (iter < max_iter && MoveAhead(debug_level))
        {
            Fight();
            ++iter;
            PrintIterSummary(debug_level, iter);
        }

        //show end positions
        PrintEndSummary(num_start_places, num_start_monsters);
        PrintSummary();
        PrintCurrentPosition();
    }

    void MonsterController::PrintIterSummary(const int debug_level, const int iter) const
    {
        // debug level 2 - print monster's position during each iter
        if (debug_level > 1)
        {
            PrintCurrentPosition();
        }

        //print summary only for every 100 iters
        if (debug_level && iter % 100 == 0)
        {
            std::cout << "Total iterations so far " << iter
                << " number of monsters in action " << GetLiveMonsterCount()
                << " Number of places "  << m_map_data.GetNumPlaces()
                << std::endl;
        }
    }

    void MonsterController::PrintEndSummary(const size_t num_start_places, const size_t num_start_monsters) const
    {
        std::cout << COLOR_GREEN << "\nEnd of the play\n" << COLOR_DEFAULT;
        std::cout << "Total number of places destroyed " << COLOR_RED << num_start_places-m_map_data.GetNumPlaces() << COLOR_DEFAULT
            << "\nTotal number of monsters unleashed at the start " << num_start_monsters
            << "\nnumber of monsters perished or stuck in places without any outroute " << COLOR_RED << num_start_monsters-GetLiveMonsterCount() << COLOR_DEFAULT
            << "\n";
    }

    void MonsterController::PrintSummary() const
    {
        std::cout << "Number of live monsters in action " << GetLiveMonsterCount() << "\n";
        std::cout << "Number of places in map "  << m_map_data.GetNumPlaces() << std::endl;
    }

    void MonsterController::PrintCurrentPosition() const
    {
        std::cout << COLOR_BLUE "Current places of Monsters\n" << COLOR_DEFAULT;
        for (auto &monster : m_monsters_in_action)
        {
            std::cout << monster.GetId() << " " << monster.GetLocation() << "\n";
        }
        std::cout << std::endl;
    }

    // Make random move of all active monsters
    int MonsterController::MoveAhead(int debug_level)
    {
        if (!m_map_data.IsDataExists())
        {
            return 0;
        }

        m_destination_loc.clear();
        int num_moved_ahead = 0;

        // Make random move of all active monsters
        for (auto itor = m_monsters_in_action.begin();
             itor != m_monsters_in_action.end();)
        {
            std::string from_loc = itor->GetLocation();
            std::string destination;
            if (m_map_data.MakeRandomMove(from_loc, destination))
            {
                if (debug_level) std::cout << itor->GetId() << " moved from " << from_loc << " to " << destination << "\n";
                itor->SetLocation(destination);
                m_destination_loc.emplace(destination, itor);
                ++itor;
                ++num_moved_ahead;
            }
            else
            {
                m_monsters_in_action.erase(itor++);
            }
        }
        return num_moved_ahead;
    }

    void MonsterController::Fight()
    {
        for (auto itor = m_destination_loc.begin(); itor != m_destination_loc.end(); )
        {
            // more than one monster in place
            if (m_destination_loc.count(itor->first) > 1)
            {
                auto monsters_in_sameplace = m_destination_loc.equal_range(itor->first);
                auto same_key_itor = monsters_in_sameplace.first;

                std::ostringstream msg_out;
                const std::string &fight_location = same_key_itor->first;
                msg_out << COLOR_BLUE << fight_location << COLOR_DEFAULT << " has been destroyed by monster";
                for (; same_key_itor != monsters_in_sameplace.second;
                     ++same_key_itor)
                {
                    msg_out << " " << same_key_itor->second->GetId();
                    // Monster die
                    m_monsters_in_action.erase(same_key_itor->second);
                }
                msg_out << "!";

                // location is destroyed so take it out from map and all inroutes to it
                m_map_data.DestroyLocation(fight_location);

                // print the message
                std::cout << msg_out.str() << std::endl;
                itor = same_key_itor;
            }
            else
            {
                ++itor;
            }
        }
    }
}
