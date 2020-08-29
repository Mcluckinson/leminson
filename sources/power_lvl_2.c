//
// Created by Carly Yuriko on 8/29/20.
//

#include "lemin.h"

static bool set_start_end(t_room *start, t_room *end)
{
	if (!start || !end)
		return (false);
	start->level = START;
	end->level = END;
	return (true);
}

static int set_lvl_one(t_room *start, t_link *links)
{
	t_link *counter;
	int 	links_done;////checker; delete me when its done if its not needed, leave it this way otherwise

	links_done = 0;
	counter = links;
	while (counter)
	{
		if (counter->first_room == start)
		{
			counter->second_room->level++;
			links_done++;
		}
		if (counter->second_room == start)
		{
			links_done++;
			counter->first_room->level++;
		}
		counter = counter->next;
	}
	return (links_done);
}

static int set_other_lvls(t_link *links, t_main *map)
{
	int links_done;
	t_link *counter;

	counter = links;
	links_done = 0;
	while (counter)
	{
		if (counter->first_room->level && !counter->second_room->level && counter->first_room->level != END && counter->second_room != map->start)
		{
			counter->second_room->level = counter->first_room->level + 1;
			map->max_lvl = map->max_lvl < counter->second_room->level ? counter->second_room->level : map->max_lvl;
			links_done++;
		}
		if (counter->second_room->level && !counter->first_room->level && counter->second_room->level != END && counter->first_room != map->start)
		{
			counter->first_room->level = counter->second_room->level + 1;
			map->max_lvl = map->max_lvl < counter->first_room->level ? counter->first_room->level : map->max_lvl;
			links_done++;
		}
		counter = counter->next;
	}
	return (links_done);
}

static int set_bad_links(t_link *links, t_main *map)
{
	t_link *counter;
	int 	lvls_done;

	counter = links;
	lvls_done = 0;
	while (counter)
	{
		if (!counter->first_room->level && counter->first_room != map->start)
		{
			counter->first_room->level = -1;
			lvls_done++;
		}
		if (!counter->second_room->level && counter->second_room != map->start)
		{
			counter->second_room->level = -1;
			lvls_done++;
		}
		counter = counter->next;
	}
	return (lvls_done);
}

int	power_levels(t_main *map)
{
	bool done;
	int	lvls_done;
	int lvls_done_on_iteration;

	done = false;
	lvls_done_on_iteration = 0;
	lvls_done = 2;////2 for start and end rooms
	if (!set_start_end(map->start, map->end))
		ft_error("INVALID MAP KEK");
	lvls_done += set_lvl_one(map->start, map->all_links_here);
	if (lvls_done == 2)
		ft_error("INVALID MAP KEK");
	else
		map->max_lvl = 1;
	while (!done)
	{
		lvls_done_on_iteration = set_other_lvls(map->all_links_here, map);
		lvls_done += lvls_done_on_iteration;
		if (!lvls_done_on_iteration)
			done = true;
	}
	done = false;
	while (!done)
	{
		lvls_done_on_iteration = set_bad_links(map->all_links_here, map);
		lvls_done += lvls_done_on_iteration;
		if (!lvls_done_on_iteration)
			done = true;
	}
	return (lvls_done);
}