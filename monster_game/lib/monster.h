// monster.h
// vi:set ts=4 sw=4 nowrap:
// Author : S Bandi

#ifndef MIMECAST_EXERCISE_MONSTER_H_ALREADY_INCLUDED
#define MIMECAST_EXERCISE_MONSTER_H_ALREADY_INCLUDED

/// Color codes
#define COLOR_DEFAULT               "\033[0m"
#define COLOR_BLACK                 "\033[1;30m"
#define COLOR_RED                   "\033[1;31m"
#define COLOR_GREEN                 "\033[1;32m"
#define COLOR_BROWN                 "\033[1;33m"
#define COLOR_BLUE                  "\033[1;34m"
#define COLOR_MAGENTA               "\033[1;35m"
#define COLOR_CYAN                  "\033[1;36m"
#define COLOR_LIGHTGRAY             "\033[1;37m"
#define COLOR_TEXT(color, text)     color text COLOR_DEFAULT


#include <string>
#include <list>
#include <map>

namespace MonsterGame
{
    // T is Data Type by which monster can be indentified Numeric/String/etc
    template <class T>
    class Monster
    {
        public:
            Monster(T id)
                :
                m_id(id)
            {
            }
            Monster(T id, const std::string &start_location)
                :
                m_id(id), m_current_location(start_location)
            {
            }
            T GetId() const { return m_id; }
            void SetLocation(const std::string &current_location) { m_current_location = current_location; }
            const std::string & GetLocation() const { return m_current_location; }
        private:
            T                   m_id;
            std::string         m_current_location;
    };

    // Entity representing Evil Overlord
    class MonsterController
    {
        public:
            // FIXME if there is no need of sharing of MapData, better use composition
            // make map_data as member object instead of getting reference
            MonsterController(MapData & map_data, int num_monsters);

            // interface to the player
            void Play(const int max_iter = 10000, const int debug_level = 0);

        protected:
            /// Monster type indentified by Number
            using LocalMonster = Monster <int>;
            using MonsterListIter = std::list<LocalMonster>::iterator;

            // monster commander's unexposed controls

            // check how many of monsters in live action
            size_t GetLiveMonsterCount() const { return m_monsters_in_action.size(); }

            // Commander sends signal to move ahead
            // all monsters will make a random move
            int MoveAhead(const int debug_level=0);

            //Monsters eneded-up in same location after above random move will fight with each other
            void Fight();

            // helper functions for printing the status - mainly useful during testing/debugging
            void PrintCurrentPosition() const;
            void PrintEndSummary(const size_t num_start_places, const size_t num_start_monsters) const;
            void PrintSummary() const;
            void PrintIterSummary(const int debug_level, const int iter) const;

        private:
            //As a commander of monsters, need to have precious resources (MapData)
            MapData &                       m_map_data;
            // list so that we can store iterators for later use mainly to delete the monsters after fight
            std::list<LocalMonster>         m_monsters_in_action;
            // multimap for getting the count of monsters endedup in same place after random move
            std::multimap<std::string, MonsterListIter> m_destination_loc;
    };

} // end namespace MonsterGame
#endif
