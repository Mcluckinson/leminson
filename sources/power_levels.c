//
// Created by Carleton Lothor on 8/23/20.
//

#include "lemin.h"

static void set_known_levels(t_main *map)
{
    map->start->level = START;
    map->end->level = END;
}

bool power_levels(t_main *map)
{
    set_known_levels(map);
    t_link *link = map->all_links_here;
    t_room *room = map->all_rooms_here;

//    link->first_room


    return false;
}


