//
// Created by Carly Yuriko on 8/23/20.
//

#include "lemin.h"

static bool should_delete_output(t_room *room, t_main *map)
{

}



void delete_output(t_room *room, t_main *map)
{
	t_link *link_to_save;

	link_to_save = map->all_links_here;
	if (should_delete_output(room, map))
	{
		link_to_save = find_good_output(room, map->all_links_here);
		delete_other_inputs(room, map->all_links_here);
	}
	delete_worse_kids(map->all_links_here);
}