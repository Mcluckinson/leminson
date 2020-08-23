//
// Created by Carleton Lothor on 8/23/20.
//

#include "lemin.h"

static void set_known_levels(t_main *map)
{
    map->start->level = START;
    map->end->level = END;
}

static void set_level(t_room *level, t_room *level2)
{
    if (level2 < level && level2 != 0)
    {
        level = level2;
    }
    else if (level == 0)
    {
        level = 1;
    }
}

bool power_levels(t_main *map)
{
    set_known_levels(map);
    t_room *room = map->all_rooms_here->next;
    while (room->next)
    {
        t_link *link = map->all_links_here;
        while (link->next)
        {
            if (room->name == link->first_room->name)
            {
//                room->level = room->level + 1;
                set_level(room, link->first_room);
            }
            else if (room->name == link->second_room->name)
            {
//                room->level = room->level + 1;
                set_level(&room->level, &link->second_room->level);
            }
            link = link->next;
        }
        room = room->next;
    }
    printf("Ok\n");

//    link->first_room


    return false;
}


